#include "polygonmodel.h"

PolygonModel::PolygonModel(QOpenGLShaderProgram *program, std::vector<Point> &pointz)
    : C_COLOR(0.0f,0.0f,0.0f)
{
    // assign the same color to all lines
    std::vector<QVector3D> colorz(pointz.size(), C_COLOR);

    initializeVAO(program, pointz, colorz);
}

void PolygonModel::drawModel(QOpenGLShaderProgram *program)
{
    // activate shaders and model
    program->bind();
    m_modelVao.bind();
    // draw
    glDrawArrays(GL_LINE_LOOP, 0, m_pointsCount);
    // deactivate model and shaders
    m_modelVao.release();
    program->release();
}
