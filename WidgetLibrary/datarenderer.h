#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <QtQuick/QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

#include "canvas.h"
#include "Models/graphicalmodel.h"
#include "widgetlibrary_global.h"

/* Rendrer, uses OpenGL */
class WIDGETLIBRARYSHARED_EXPORT DataRenderer : public QObject, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    DataRenderer(QObject *parent=nullptr);
    ~DataRenderer();

    // set opengl viewport
    void setViewportSize(const QSize &size);
    // set qt window
    void setWindow(QQuickWindow *window);
    // reset shader program. Will delete shader and models
    void setShaderProgram(QString shadersUrl);
    // set the scene to render. Will delete models
    void setScene(RangeSearchData &scene);

    // getter for canvas
    Canvas *canvas();

public slots:
    // paints scene
    void paint();

private slots:
    // takes projection matrix from canvas and sets it in shader program
    void updateProjectionMatrix();

private:
    // initialize any resources needed for rendering...
    void initializeResources(QString shadersUrl);
    // dispose of any resources created for rendering...
    void cleanupResources();

    // print version of OpenGL
    void printVersionInformation();


    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;
    QQuickWindow *m_window;
    Canvas *m_canvas;

    std::vector<GraphicalModel *> m_models;
};

#endif // SCENERENDERER_H
