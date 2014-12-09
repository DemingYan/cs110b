/* Author: Kevin Morris
 * File: ship.h
 * This is a class interface representing
 * a ship in the Battleship game */
#include "point.h"
#include "point_collection.h"

PointCollection::PointCollection()
{
    size = 0;
    capacity = 4;
    data = new point[4];
}

PointCollection::PointCollection(const PointCollection &c)
{
    *this = c;
}

PointCollection::~PointCollection()
{
    delete [] data;
}

void
PointCollection::add(const point &p)
{
    // Check to see if we need more space
    if (size == capacity)
    {
        doubleArraySize();
    }
    
    // Add the new value
    data[size] = p;
    size++;
}

point&
PointCollection::get(int index) const
{
    return data[index];
}

int
PointCollection::getSize() const
{
    return size;
}

bool
PointCollection::contains(const point &p) const
{
    
    for (int i = 0; i < getSize(); i++) {
        if (get(i) == p) {
            return true;
        }
    }
    
    return false;
}

PointCollection&
PointCollection::operator<<(const point &p)
{
    this->add(p);
    return *this;
}

point&
PointCollection::operator[](int index) const
{
    return this->get(index);
}

const PointCollection&
PointCollection::operator=(const PointCollection &c)
{
    // deallocate the existing data
    delete [] data;
    
    // copy the primitive values
    size = c.size;
    capacity = c.capacity;
    
    // create a new data array with capacity to match c
    data = new point[c.capacity];
    
    // copy the points.
    for (int i = 0; i < size; i++)
    {
        data[i] = c.data[i];
    }
    
    // return the argument, to allow chaining of assignments
    return c;
}

void PointCollection::doubleArraySize()
{
    // Allocate a new array, twice as big
    point *newArray = new point[capacity * 2];
    
    // Copy values from data to new array
    for (int i = 0; i < size; i++)
    {
        newArray[i] = data[i];
    }

    // delete old array
    delete [] data;
    
    // point data at the new array
    data = newArray;
    
    // double capacity value
    capacity *= 2;
}



