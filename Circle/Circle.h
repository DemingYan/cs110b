/* Author: Kevin Morris <kevr@nixcode.us>
 * File: Circle.h
 * A class representing a circle and some geometric features */
#ifndef CIRCLE_H
#define CIRCLE_H

// Include C Standard Library M_PI constant
#include <cmath>

double distance(double x, double y);

struct Coordinates
{
    double x, y; // (x, y) point
};

class Circle
{
    double r; // radius
    double d; // distance
    Coordinates core;

public:
    Circle();
    Circle(double x, double y, double radius);

    const double radius() const;
    const double x() const;
    const double y() const;
    double getArea() const;

    bool containsPoint(double x, double y);

};

#endif /* CIRCLE_H */


