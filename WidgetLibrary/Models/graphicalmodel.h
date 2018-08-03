#ifndef DRAWABLEMODEL_H
#define DRAWABLEMODEL_H

#include <QOpenGLShaderProgram>

#include "widgetlibrary_global.h"
#include "polygon.h"
#include "rangesearchdata.h"

class WIDGETLIBRARYSHARED_EXPORT GraphicalModel
{
public:
    virtual void drawModel(QOpenGLShaderProgram *program)=0;
    virtual ~GraphicalModel() {}
};


class WIDGETLIBRARYSHARED_EXPORT ModelFactory
{
public:
    std::vector<GraphicalModel *> createModels(RangeSearchData& scene, QOpenGLShaderProgram *program);
    void deleteModels(std::vector<GraphicalModel *>& models);
};

#endif // DRAWABLEMODEL_H
