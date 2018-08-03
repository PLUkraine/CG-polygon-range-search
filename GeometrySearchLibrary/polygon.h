#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "geometrysearchlibrary_global.h"
#include "point.h"

class GEOMETRYSEARCHLIBRARYSHARED_EXPORT Polygon
{
private:
    std::vector<Point> m_points;
public:

    Polygon(const std::vector<Point> &points);
    Polygon(const std::vector<double> &x, const std::vector<double> &y);

    std::vector<Point> getPoints()const;
    Point getPoint(int pos)const;
    Point getNextPoint(int pos)const;
    int getSize() const;
};

#endif // POLYGON_H
