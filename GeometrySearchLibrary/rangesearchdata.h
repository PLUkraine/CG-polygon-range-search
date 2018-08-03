#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QtGui/QVector3D>

#include "polygon.h"

struct GEOMETRYSEARCHLIBRARYSHARED_EXPORT RangeSearchData
{
    RangeSearchData();

    std::vector<Polygon> polygons;
    std::vector<Point> points;
    std::vector<Point> insidePoints;

    void clear();
};

#endif // SCENE_H
