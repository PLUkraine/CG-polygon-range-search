#ifndef POLYGONMODEL_H
#define POLYGONMODEL_H

#include "pointbasedmodel.h"

class PolygonModel : public PointBasedModel
{
public:
    PolygonModel(QOpenGLShaderProgram *program, std::vector<Point>& pointz);

    void drawModel(QOpenGLShaderProgram *program);
private:
    const QVector3D C_COLOR;
};

#endif // POLYGONMODEL_H
