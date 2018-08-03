#include "polygon.h"
#include "utils.h"

Polygon::Polygon(const std::vector<double> &x, const std::vector<double> &y)
{
    int sizeX = x.size(), sizeY = y.size();

    if (sizeX != sizeY) {
        throw "Different number of coordinates";
    }

    m_points.resize(sizeX);
    for(int i = 0; i < sizeX; i++) {
        m_points[i] = Point(x[i], y[i]);
    }
}

Polygon::Polygon(const std::vector<Point> &points)
{
    m_points.insert(m_points.begin(), points.begin(), points.end());
}

std::vector<Point> Polygon::getPoints()const
{
    return (*this).m_points;
}

Point Polygon::getPoint(int pos)const
{
    if (pos >= (int)m_points.size()) {
        throw "Index out of range";
    } else {
        return m_points[pos];
    }
}

Point Polygon::getNextPoint(int pos)const
{
    if (pos >= (int)m_points.size()) {
        throw "Index out of range";
    } else {
        pos++;
        if (pos == (int)m_points.size())pos = 0;
        return m_points[pos];
    }
}

int Polygon::getSize()const
{
    return (int)m_points.size();
}
