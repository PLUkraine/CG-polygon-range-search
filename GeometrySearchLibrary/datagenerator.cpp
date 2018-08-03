#include "datagenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

DataGenerator::DataGenerator()
    : rd(),
      mt(rd())
{}

void DataGenerator::generate(RangeSearchData &scene, int n, int k)
{
    const double MAGIC = 1e4;
    scene.clear();

    std::uniform_real_distribution<double> dist(-MAGIC, MAGIC);
    std::uniform_real_distribution<double> angleDist(-M_PI, M_PI);
    for (int i=0; i<n; ++i) {
        scene.points.push_back({dist(mt), dist(mt)});
    }


    double x0 = 0, y0 = 0, r = 1e4/2;
    std::vector<double> angles(k, 0);
    for (int i=0; i<k; ++i)
        angles[i] = angleDist(mt);
    std::sort(angles.begin(), angles.end());

    std::vector<Point> polygonPoints;
    for (int i = 0; i < k; i++)
    {
        double x = x0 + r*cos(angles[i]);
        double y = y0 + r*sin(angles[i]);
        polygonPoints.push_back({x,y});
    }

    scene.polygons.push_back(Polygon(polygonPoints));
}
