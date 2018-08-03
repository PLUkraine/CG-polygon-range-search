#include "point.h"

#include <math.h>

#include "utils.h"

bool Point::compareByY(Point a, Point b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

bool Point::compareByX(Point a, Point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

Point::Point(): x(0), y(0) {}

Point::Point(double x, double y): x(x), y(y) {}

Point Point::operator+(const Point &p) const
{
    return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point &p) const
{
    return Point(x - p.x, y - p.y);
}

Point Point::operator-() const
{
    return Point(-x, -y);
}

Point Point::operator*(double k) const
{
    return Point(x * k, y * k);
}

Point Point::operator/(double k) const
{
    return Point(x / k, y / k);
}


bool Point::operator==(const Point & p) const
{
    return doubleEqual(x, p.x) && doubleEqual(y, p.y);
}

bool Point::operator!=(const Point & p) const
{
    return !((*this) == p);
}

bool Point::operator<(const Point &p) const
{
    return Point::compareByX(*this, p);
}

double Point::operator%(const Point &p) const
{
    return x * p.x + y * p.y;
}

double Point::operator*(const Point &p) const
{
    return x * p.y - y * p.x;
}

double Point::length() const
{
    return mySqrt(*this % *this);
}

double Point::distTo(const Point &p) const
{
    return (*this - p).length();
}

double Point::distTo(const Point &A, const Point &B) const
{
    double d = A.distTo(B);
    if(doubleEqual(d, 0) )
    {
        throw "A = B";
    }
    double s = (*this - A) * (*this - B);
    return fabs(s) / d;
}

Point Point::normalize(double k) const
{
    double len = length();
    if(doubleEqual(len, 0) )
    {
        if(doubleEqual(k, 0) )
        {
            return Point();
        }
        throw "zero-size vector";
    }
    return *this * (k / len);
}

Point Point::getH(const Point &A, const Point &B) const
{
    Point C = *this;
    Point v = B - A;
    Point u = C - A;
    double k = v % u / v.length();
    v = v.normalize(k);
    Point H = A + v;
    return H;
}

Point Point::rotate() const
{
    return Point(-y, x);
}

Point Point::rotate(double alpha) const

{
    return rotate(cos(alpha), sin(alpha) );
}

Point Point::rotate(double cosa, double sina) const
{
    Point v = *this;
    Point u = v.rotate();
    Point w = v * cosa + u * sina;
    return w;
}

bool Point::isZero() const
{
    return doubleEqual(x, 0) && doubleEqual(y, 0);
}

bool Point::isOnLine(const Point &A, const Point &B) const
{
    return doubleEqual( (A - *this) * (B - *this), 0);
}

bool Point::isInSegment(const Point &A, const Point &B) const
{
    return isOnLine(A, B) && doubleLessOrEqual( (A - *this) % (B - *this), 0 );
}

bool Point::isInSegmentStrictly(const Point &A, const Point &B) const
{
    return isOnLine(A, B) && doubleLess( (A - *this) % (B - *this), 0 );
}

double Point::getAngle() const
{
    return atan2(y, x);
}

double Point::getAngle(Point u) const
{
    Point v = *this;
    return atan2(v * u, v % u);
}

int getIntersection(const Point &A, const Point &B, const Point &C, const Point &D, Point &O)
{
    Point v = B - A;
    double s1 = (C - A) * (D - A);
    double s2 = (D - B) * (C - B);
    double s = s1 + s2;
    if(doubleEqual(s, 0) )
    {
        if(!A.isOnLine(C, D) )
        {
            return 0;
        }
        return 2;
    }
    v = v / s;
    v = v * s1;
    O = A + v;
    return 1;
}

double square(const Point &A, const Point &B, const Point &C) {
    return (B - A) * (C - A);
}
