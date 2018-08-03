#include "graphicalmodel.h"
#include "polygonmodel.h"
#include "pointsmodel.h"


std::vector<GraphicalModel *> ModelFactory::createModels(RangeSearchData &scene, QOpenGLShaderProgram *program)
{
    std::vector<GraphicalModel *> result;
    for (Polygon& poly : scene.polygons) {
        auto copy = poly.getPoints();
        result.push_back(new PolygonModel(program, copy));
    }
    result.push_back(new PointsModel(program, scene.points));
    result.push_back(new PointsModel(program, scene.insidePoints, QVector3D(1.0f, 0.0f, 1.0f)));

    return result;
}

void ModelFactory::deleteModels(std::vector<GraphicalModel *> &models)
{
    for (GraphicalModel * model : models) {
        delete model;
        model = nullptr;
    }
    models.clear();
}
