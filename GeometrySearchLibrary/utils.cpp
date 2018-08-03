#include <math.h>
#include <map>
#include <algorithm>
#include <iostream>

#include "utils.h"

double sqr(double a) // квадрат числа
{
    return a * a;
}

bool doubleEqual(double a, double b) // сравниваем на равенство с eps, константой 1е-9 используется только здесь
{
    return fabs(a - b) < 1e-9;
}

bool doubleLessOrEqual(double a, double b) // <= с eps
{
    return a < b || doubleEqual(a, b);
}

bool doubleLess(double a, double b) // < с eps
{
    return a < b && !doubleEqual(a, b);
}

bool doubleGreaterOrEqual(double a, double b) // >= с eps
{
    return a > b || doubleEqual(a, b);
}

bool doubleGreater(double a, double b) // > с eps
{
    return a > b && !doubleEqual(a, b);
}

bool isClockwise(const Point &A, const Point &B, const Point &C) {
    return doubleLess(square(A, B, C), 0);
}

bool isCounterClockwise(const Point &A, const Point &B, const Point &C) {
    return doubleGreater(square(A, B, C), 0);
}

bool isCollinear(const Point &A, const Point &B, const Point &C) {
    return doubleEqual(abs(square(A, B, C)), 0);
}

double mySqrt(double a) // mySqrt с проверкой, что корректен аргумент
{
    if(doubleLess(a, 0) ) //некорректный вызов
    {
        throw "sqrt(-1)";
    }
    if(a < 0) return 0; //отрицательное ввиду небольшой погрешности
    return sqrt(a);
}

int pointXCompare(const Point &a, const Point &b)
{
    if      (doubleLess(a.x, b.x)) return -1;
    else if (doubleEqual(a.x, b.x)) return 0;
    else    return 1;
}

int pointYCompare(const Point &a, const Point &b)
{
    if      (doubleLess(a.y, b.y)) return -1;
    else if (doubleEqual(a.y, b.y)) return 0;
    else    return 1;
}

bool isClockwisePolygon(std::vector<Point> points)
{
    // iterate over all points and sum (x2-x1)(y2+y1).
    // if sum is positive, points are clockwise ordered
    // this is basically finding integral of our polygon
    double sum = 0;
    const size_t n = points.size();
    for (size_t i=0; i<n; ++i) {
        Point cur = points[i];
        Point next = points[(i+1)%n];
        sum += (next.x-cur.x) * (next.y+cur.y);
    }
    return doubleGreaterOrEqual(sum, 0);
}

// a is center, b and c are ends of vectors
double counterclockwiseAngle(const Point &a, const Point &b, const Point &c)
{
    double x1 = b.x - a.x;
    double y1 = b.y - a.y;
    double x2 = c.x - a.x;
    double y2 = c.y - a.y;

    double dot = x1*x2 + y1*y2;      // dot product between [x1, y1] and [x2, y2]
    double det = x1*y2 - y1*x2;      // determinant
    double angle = atan2(-det, -dot) + M_PI;  // atan2(y, x) or atan2(sin, cos)

    return angle;
}
