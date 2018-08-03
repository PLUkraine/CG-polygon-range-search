#ifndef SCENEFACADE_H
#define SCENEFACADE_H

#include <QtQuick/QQuickItem>

#include "datarenderer.h"

class GeometrySearchPlugin : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString shaders READ shaders WRITE setShaders)
    Q_PROPERTY(QPoint canvasCenter READ canvasCenter WRITE setCanvasCenter NOTIFY canvasCenterChanged)
    Q_PROPERTY(int pointCount READ pointCount NOTIFY pointCountChanged)
    Q_PROPERTY(int polygonSize READ polygonSize NOTIFY polygonSizeChanged)

public:
    GeometrySearchPlugin();

    // way to initialize shaders
    QString shaders() const;
    void setShaders(QString shader);

    // way to interract with canvas center
    void setCanvasCenter(QPoint newCenter);
    QPoint canvasCenter();

    // getters for count properties
    int pointCount() const;
    int polygonSize() const;

    // way to move canvas
    Q_INVOKABLE void moveCanvas(qreal dx, qreal dy);
    // read scene from file. return error string (empty if no error)
    Q_INVOKABLE QString readSceneFromFile(QString filename);
    // generate random scene
    Q_INVOKABLE void generateRandomScene(int n, int k);

signals:
    void canvasCenterChanged();
    void pointCountChanged();
    void polygonSizeChanged();

public slots:
    // used any time we need to render
    void sync();
    // probably is invoked in the end
    void cleanup();

private slots:
    // is called when window is resized?
    void handleWindowChanged(QQuickWindow *win);
    // hack to control scale factor
    void onScaleChanged();

private:
    void findInnerPoints();
    void resetScene();

    DataRenderer *m_renderer;
    QString m_shadersPath;

    RangeSearchData m_scene;
};

#endif // SCENEFACADE_H
