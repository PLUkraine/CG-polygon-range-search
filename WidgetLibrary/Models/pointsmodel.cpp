#include "pointsmodel.h"

PointsModel::PointsModel(QOpenGLShaderProgram *program, std::vector<Point> &pointz,
                                           QVector3D pointsColor)
    : C_COLOR(pointsColor),
      C_POINT_SIZE(6.0f)
{
    // assign the same color to all points
    std::vector<QVector3D> colorz(pointz.size(), C_COLOR);

    initializeVAO(program, pointz, colorz);
}

void PointsModel::drawModel(QOpenGLShaderProgram *program)
{
    // activate shaders and model
    program->bind();
    glPointSize(C_POINT_SIZE);
    m_modelVao.bind();
    // draw
    glDrawArrays(GL_POINTS, 0, m_pointsCount);
    // deactivate model and shaders
    m_modelVao.release();
    program->release();
}
