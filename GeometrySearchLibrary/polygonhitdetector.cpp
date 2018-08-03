#include "polygonhitdetector.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include "utils.h"


PolygonHitDetector::PolygonHitDetector(std::vector<Point> points)
    : m_points(points)
{
    // make sure points are CCW ordered!
    if (isClockwisePolygon(m_points)) {
        std::reverse(m_points.begin(), m_points.end());
    }

    // get angles counting from line (m_center, first point)
    buildWedges();
}

bool PolygonHitDetector::hit(Point point)
{
    std::pair<int,int> indices = searchWedge(point);
    return isCounterClockwise(m_points[indices.first], m_points[indices.second], point)
            || isCollinear(m_points[indices.first], m_points[indices.second], point);
}

void PolygonHitDetector::buildWedges()
{
    int n = m_points.size();

    // find some point inside polygon
    m_center.x = (m_points[0].x + m_points[1].x + m_points[2].x) / 3.0;
    m_center.y = (m_points[0].y + m_points[1].y + m_points[2].y) / 3.0;

    // create array of angles
    m_wedges.assign(n+1, 0);
    // first and the last are 0 and 2*PI respectively
    m_wedges[0] = 0;
    m_wedges[n] = 2*M_PI;

    // fill for intermediate points
    for (int i=1; i<n; ++i) {
        m_wedges[i] = counterclockwiseAngle(m_center, m_points[0], m_points[i]);
    }
}

std::pair<int, int> PolygonHitDetector::searchWedge(Point point)
{
    double angle = counterclockwiseAngle(m_center, m_points[0], point);
    auto it = std::upper_bound(m_wedges.begin(), m_wedges.end(), angle, doubleLess)-1;
    int i = std::distance(m_wedges.begin(), it);
    return {i, (i+1)%m_points.size()};
}
