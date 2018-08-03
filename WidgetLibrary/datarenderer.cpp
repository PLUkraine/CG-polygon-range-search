#include "datarenderer.h"

#define DELETE_PTR(ptr) if ((ptr)) { delete (ptr); (ptr) = nullptr; }


DataRenderer::DataRenderer(QObject *parent)
    : QObject(parent),
    m_program(nullptr),
    m_window(nullptr),
    m_canvas(new Canvas(this))
{
    connect(m_canvas, &Canvas::canvasChanged, this, &DataRenderer::updateProjectionMatrix, Qt::DirectConnection);

    initializeOpenGLFunctions();
    printVersionInformation();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

}

DataRenderer::~DataRenderer()
{
    cleanupResources();
}

void DataRenderer::setViewportSize(const QSize &size) {
    // update viewport size
    m_viewportSize = size;

    // resize viewport
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    m_canvas->setCanvasSize(QSizeF(size));

}

void DataRenderer::setWindow(QQuickWindow *window) { m_window = window; }

void DataRenderer::setShaderProgram(QString shadersUrl)
{
    cleanupResources();
    initializeResources(shadersUrl);
}

void DataRenderer::setScene(RangeSearchData &scene)
{
    if (m_program) {
        ModelFactory factory;
        factory.deleteModels(m_models);
        m_models = factory.createModels(scene, m_program);
    }
    if (m_window) {
        m_window->update();
    }
}

Canvas *DataRenderer::canvas()
{
    return m_canvas;
}

void DataRenderer::paint()
{
    if (!m_program) {
        qWarning() << "Shaders weren't initialized";
    }

    glClearColor(1.0, 1.0, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // paint scene here
    for (GraphicalModel *model : m_models) {
        model->drawModel(m_program);
    }

    m_window->resetOpenGLState();
}

void DataRenderer::updateProjectionMatrix()
{
    // set projection matrix
    m_program->bind();
    m_program->setUniformValue("projection", m_canvas->getProjectionMatrix());
    m_program->release();

    if (m_window) {
        m_window->update();
    }
}

void DataRenderer::initializeResources(QString shadersUrl)
{
    // get the filenames
    QString vertexShaderPath = shadersUrl + ".vert";
    QString fragmentShaderPath = shadersUrl + ".frag";

    // create program
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPath);
    m_program->link();
}

void DataRenderer::cleanupResources()
{
    // delete program
    DELETE_PTR(m_program);
    // delete models
    ModelFactory factory;
    factory.deleteModels(m_models);
}

void DataRenderer::printVersionInformation()
{
    QString glType;
    QString glVersion;

    // Get Version Information
    glType = "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion);
}
