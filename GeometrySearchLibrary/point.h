#ifndef POINT_H
#define POINT_H

#include "geometrysearchlibrary_global.h"

struct GEOMETRYSEARCHLIBRARYSHARED_EXPORT Point
{
public:
    double x, y;
public:
    static bool compareByY(Point a, Point b);

    static bool compareByX(Point a, Point b);

    Point();

    Point(double x, double y);

    Point operator+(const Point & p) const;

    Point operator-(const Point & p) const;

    Point operator-() const;

    Point operator*(double k) const;

    Point operator/(double k) const;

    bool operator==(const Point & p) const;

    bool operator!=(const Point & p) const;

    bool operator<(const Point & p) const;

    double operator%(const Point & p) const;

    double operator*(const Point & p) const;

    double length() const;

    double distTo(const Point & p) const;

    double distTo(const Point & A, const Point & B) const;

    Point normalize(double k = 1) const;

    Point getH(const Point & A, const Point & B) const;

    Point rotate() const;

    Point rotate(double alpha) const;

    Point rotate(double cosa, double sina) const;

    bool isZero() const;

    bool isOnLine(const Point & A, const Point & B) const;

    bool isInSegment(const Point & A, const Point & B) const;

    bool isInSegmentStrictly(const Point & A, const Point & B) const;

    double getAngle() const;

    double getAngle(Point u) const;
};


int getIntersection
        (
                const Point & A,
                const Point & B,
                const Point & C,
                const Point & D,
                Point & O
        );


double square(const Point &A, const Point &B, const Point &C);

#endif // POINT_H
