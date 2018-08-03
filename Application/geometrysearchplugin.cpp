#include "geometrysearchplugin.h"

#include "polygon.h"
#include "point.h"
#include "utils.h"
#include "fileprocessor.h"
#include "polygonhitdetector.h"
#include "datagenerator.h"

#include <vector>
#include <random>


#define DELETE_PTR(ptr) if ((ptr)) { delete (ptr); (ptr) = nullptr; }

GeometrySearchPlugin::GeometrySearchPlugin()
    : m_renderer()
{
    connect(this, &QQuickItem::windowChanged, this, &GeometrySearchPlugin::handleWindowChanged);
    connect(this, &QQuickItem::scaleChanged, this, &GeometrySearchPlugin::onScaleChanged);
}

QString GeometrySearchPlugin::shaders() const
{
    return this->m_shadersPath;
}

void GeometrySearchPlugin::setShaders(QString shader)
{
    this->m_shadersPath = shader;
    if (m_renderer) {
        m_renderer->setShaderProgram(shader);
        resetScene();
    }
}

void GeometrySearchPlugin::setCanvasCenter(QPoint newCenter)
{
    if (m_renderer) {
        m_renderer->canvas()->centerIn(QVector2D(newCenter.x(),
                                                 newCenter.y()));
        emit canvasCenterChanged();
    }
}

QPoint GeometrySearchPlugin::canvasCenter()
{
    if (m_renderer) {
        return m_renderer->canvas()->getCenter();
    }
    return QPoint(0, 0);
}

int GeometrySearchPlugin::pointCount() const
{
    return m_scene.points.size();
}

int GeometrySearchPlugin::polygonSize() const
{
    if (m_scene.polygons.empty()) return 0;
    return m_scene.polygons[0].getSize();
}

void GeometrySearchPlugin::moveCanvas(qreal dx, qreal dy)
{
    if (m_renderer) {
        m_renderer->canvas()->moveCanvas(QVector2D(dx, dy));
        emit canvasCenterChanged();
    }
}

QString GeometrySearchPlugin::readSceneFromFile(QString filename)
{
    // read scene from file
    FileProcessor scenefile;
    // check if read was successfull
    if (!scenefile.read(m_scene, filename.toStdString().c_str())) {
        resetScene();
        emit polygonSizeChanged();
        emit pointCountChanged();

        return scenefile.getError();
    }

    resetScene();
    emit polygonSizeChanged();
    emit pointCountChanged();
    return QString();
}

void GeometrySearchPlugin::generateRandomScene(int n, int k)
{
    DataGenerator gen;
    gen.generate(m_scene, n, k);

    resetScene();
    emit polygonSizeChanged();
    emit pointCountChanged();
}

void GeometrySearchPlugin::sync()
{
    if (!m_renderer) {
        m_renderer = new DataRenderer();
        m_renderer->setShaderProgram(m_shadersPath);
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &DataRenderer::paint, Qt::DirectConnection);
        resetScene();
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void GeometrySearchPlugin::cleanup()
{
    DELETE_PTR(m_renderer);
}

void GeometrySearchPlugin::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &GeometrySearchPlugin::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &GeometrySearchPlugin::cleanup, Qt::DirectConnection);
        // don't allow Qt to clear window and erase my painting
        win->setClearBeforeRendering(false);
    }
}

void GeometrySearchPlugin::onScaleChanged()
{
    if (m_renderer) {
        m_renderer->canvas()->setScale(scale());
    }
}

void GeometrySearchPlugin::findInnerPoints()
{
    if (!m_scene.polygons.empty()) {
        PolygonHitDetector hitman(m_scene.polygons[0].getPoints());
        m_scene.insidePoints.clear();
        for (Point point : m_scene.points)
        {
            if (hitman.hit(point)) {
                m_scene.insidePoints.push_back(point);
            }
        }
    }
}

void GeometrySearchPlugin::resetScene()
{
    findInnerPoints();
    if (m_renderer) {
        m_renderer->setScene(m_scene);
    }
}
