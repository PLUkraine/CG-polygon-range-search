#ifndef POLYGONHITDETECTOR_H
#define POLYGONHITDETECTOR_H

#include <vector>

#include "point.h"

class GEOMETRYSEARCHLIBRARYSHARED_EXPORT PolygonHitDetector
{
public:
    PolygonHitDetector(std::vector<Point> points);
    bool hit(Point point);

private:
    void buildWedges();
    std::pair<int,int> searchWedge(Point point);

    Point m_center;
    std::vector<Point> m_points;
    std::vector<double> m_wedges;
};

#endif // POLYGONHITDETECTOR_H
