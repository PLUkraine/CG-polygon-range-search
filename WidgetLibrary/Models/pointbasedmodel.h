#ifndef POINTBASEDMODEL_H
#define POINTBASEDMODEL_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>

#include <vector>

#include "graphicalmodel.h"
#include "point.h"

class PointBasedModel : public GraphicalModel, protected QOpenGLFunctions_3_3_Core
{
public:
    PointBasedModel();
    virtual ~PointBasedModel();

    void drawModel(QOpenGLShaderProgram *program)=0;

protected:
    void initializeVAO(QOpenGLShaderProgram *program, std::vector<Point>& pointz, std::vector<QVector3D>& colorz);
    void dispose();

    QOpenGLVertexArrayObject m_modelVao;
    QOpenGLBuffer m_locationsVbo;
    QOpenGLBuffer m_colorsVbo;
    GLuint m_pointsCount;
};

#endif // POINTBASEDMODEL_H
