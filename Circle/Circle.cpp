/* Author: Kevin Morris <kevr@nixcode.us>
 * File: Circle.cpp
 * A class representing a circle and some geometric features */
#include "Circle.h"
#include <cmath>

double distance(double x, double y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

Circle::Circle(double x, double y, double radius)
    : r(radius)
{
    core.x = x;
    core.y = y;
}

const double Circle::radius() const
{
    return r;
}

const double Circle::x() const
{
    return core.x;
}

const double Circle::y() const
{
    return core.y;
}

double Circle::getArea() const
{
    return M_PI * pow(r, 2);
}

bool Circle::containsPoint(double x, double y)
{
    return distance(x - core.x, y - core.y) <= r;
}

