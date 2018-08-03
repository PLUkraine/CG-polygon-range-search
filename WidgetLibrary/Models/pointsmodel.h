#ifndef SINGLETONPOINTSMODEL_H
#define SINGLETONPOINTSMODEL_H

#include "pointbasedmodel.h"

class PointsModel : public PointBasedModel
{
public:
    PointsModel(QOpenGLShaderProgram *program, std::vector<Point>& pointz,
                         QVector3D pointsColor=QVector3D(0.0f, 1.0f, 1.0f));

    void drawModel(QOpenGLShaderProgram *program);
private:
    const QVector3D C_COLOR;
    const GLfloat C_POINT_SIZE;
};

#endif // SINGLETONPOINTSMODEL_H
