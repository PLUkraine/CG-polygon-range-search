#ifndef HELPERS_H
#define HELPERS_H

#include "geometrysearchlibrary_global.h"

#include <vector>

#include "point.h"
#include "polygon.h"

double sqr(double a);

bool doubleEqual(double a, double b);

bool doubleLessOrEqual(double a, double b);

bool doubleLess(double a, double b);

bool doubleGreaterOrEqual(double a, double b);

bool doubleGreater(double a, double b);

bool isClockwise(const Point &A, const Point &B, const Point &C);

bool isCounterClockwise(const Point &A, const Point &B, const Point &C);

bool isCollinear(const Point &A, const Point &B, const Point &C);

bool isClockwisePolygon(std::vector<Point> points);

double counterclockwiseAngle(const Point &a, const Point &b, const Point &c);

double mySqrt(double a);

int pointXCompare(const Point &a, const Point &b);

int pointYCompare(const Point &a, const Point &b);

#endif // HELPERS_H
