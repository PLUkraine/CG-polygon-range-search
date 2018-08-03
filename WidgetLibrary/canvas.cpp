#include "canvas.h"

Canvas::Canvas(QObject *parent)
    : QObject(parent),
    m_scale(1.0f)
{}

QMatrix4x4 Canvas::getProjectionMatrix()
{
    QMatrix4x4 matrix;

    std::pair<QVector2D, QVector2D> box = getBox();

    matrix.ortho(box.first.x(), box.second.x(),
                 box.first.y(), box.second.y(),
                 1.f, -1.f);

    return matrix;
}

void Canvas::moveCanvas(QVector2D delta)
{
    m_center += QVector3D(delta) / m_scale;
    emit canvasChanged();
}

void Canvas::centerIn(QVector2D point)
{
    if (m_center != point) {
        m_center = QVector3D(point);
        emit canvasChanged();
    }
}

void Canvas::setCanvasSize(QSizeF newSize)
{
    if (m_canvasSize != newSize) {
        m_canvasSize = newSize;
        emit canvasChanged();
    }
}

void Canvas::setScale(qreal factor)
{
    if (m_scale != factor) {
        m_scale = factor;
        emit canvasChanged();
    }
}

QPoint Canvas::getCenter() const
{
    return QPoint(m_center.x(), m_center.y());
}

QVector2D Canvas::screenToCanvas(QVector2D point)
{
    std::pair<QVector2D, QVector2D> box = getBox();
    point /= m_scale;
    QVector2D res(box.first.x() + point.x(), box.second.y() - point.y());
    return res;
}

std::pair<QVector2D, QVector2D> Canvas::getBox()
{
    qreal scaled_halfwidth = m_canvasSize.width()/2/m_scale;
    qreal scaled_halfheight = m_canvasSize.height()/2/m_scale;

    QVector2D leftLowerCorner(m_center.x() - scaled_halfwidth,
                              m_center.y() - scaled_halfheight);
    QVector2D rightUpperCorner(m_center.x() + scaled_halfwidth,
                               m_center.y() + scaled_halfheight);

    return {leftLowerCorner, rightUpperCorner};
}
