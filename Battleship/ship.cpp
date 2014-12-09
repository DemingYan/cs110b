/* Author: Kevin Morris
 * File: ship.cpp
 * This is a class implementation representing
 * a ship in the Battleship game */
#include "ship.h"

Ship::Ship(point originPoint, direction o, int l)
   : length(l)
   , orientation(o)
   , origin(originPoint)
{
    if(orientation == HORIZONTAL)
    {
        for(int x = origin.getX(); x < origin.getX() + length; ++x)
            points.add(point(x, origin.getY()));
    }
    else
    {
        for(int y = origin.getY(); y < origin.getY() + length; ++y)
            points.add(point(origin.getX(), y));
    }
}

Ship::Ship(const Ship& s)
    : length(s.length)
    , orientation(s.orientation)
    , origin(s.origin)
{
    points = s.points;
    hits = s.hits;
}

bool
Ship::containsPoint(const point& p) const
{
    return points.contains(p);
}

bool
Ship::collidesWith(const Ship& s) const
{
    if(orientation == HORIZONTAL)
    {
        for(int x = origin.getX(); x <= origin.getX() + length; ++x)
            if(s.containsPoint(point(x, origin.getY())))
                return true;
    }
    else
    {
        for(int y = origin.getY(); y <= origin.getY() + length; ++y)
            if(s.containsPoint(point(origin.getX(), y)))
                return true;
    }

    return false;
}

void
Ship::shotFiredAtPoint(const point& p)
{
    if(containsPoint(p))
        hits.add(p);
}

bool
Ship::isHitAtPoint(const point& p)
{
    return hits.contains(p);
}

int
Ship::hitCount() const
{
    return hits.getSize();
}

const
Ship& Ship::operator=(const Ship& s)
{
    length = s.length;
    orientation = s.orientation;
    origin = s.origin;

    points = s.points;
    hits = s.hits;

    return *this;
}

bool
Ship::isSunk() 
{
    return hits.getSize() == length;
}



