#include "pointbasedmodel.h"


PointBasedModel::PointBasedModel()
{
    initializeOpenGLFunctions();
}

PointBasedModel::~PointBasedModel()
{
    dispose();
}

void PointBasedModel::initializeVAO(QOpenGLShaderProgram *program, std::vector<Point> &pointz, std::vector<QVector3D> &colorz)
{
    m_pointsCount = pointz.size();

    // bind program, otherwise won't work :(
    program->bind();

    // create VAO
    m_modelVao.create();
    m_modelVao.bind();

    // create positions VBO
    m_locationsVbo.create();
    m_locationsVbo.bind();
    m_locationsVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_locationsVbo.allocate(&pointz[0], sizeof(pointz[0]) * m_pointsCount);
    program->enableAttributeArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(Point), (GLvoid*)0);
    m_locationsVbo.release();

    // create colors VBO
    m_colorsVbo.create();
    m_colorsVbo.bind();
    m_colorsVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_colorsVbo.allocate(&colorz[0], sizeof(colorz[0]) * m_pointsCount);
    program->enableAttributeArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (GLvoid*)0);
    m_colorsVbo.release();

    // unbind VAO
    m_modelVao.release();

    // and release program in the end
    program->release();
}

void PointBasedModel::dispose()
{
    m_modelVao.destroy();
    m_locationsVbo.destroy();
    m_colorsVbo.destroy();
    m_pointsCount = 0;
}
