/* Author: Kevin Morris <kevr@nixcode.us>
 * File: CircleProgram.cpp
 * The main execution file for this circle program */
#include "Circle.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

static char *PNAME;

double stod(const char *str);
void printArea(Circle *c);
void printPoint(Circle *c, double x, double y);
int usage();

int main(int argc, char *argv[])
{
    PNAME = argv[0];
    if(argc != 4)
        return usage();

    double x, y, r;

    try // Try to convert double arguments via stringstream, catch otherwise
    {
        x = stod(argv[1]), y = stod(argv[2]), r = stod(argv[3]);
    }
    catch(invalid_argument& e)
    {
        cerr << "Error: " << e.what() << endl;
        return usage();
    }

    Circle circle = Circle(x, y, r);
    printArea(&circle);

    x *= x;
    y *= y;
    r *= r;

    Circle *ptr = &circle;
    *ptr = Circle(x, y, r);
    printArea(&circle);

    printPoint(&circle, x + r + 1, y);
    printPoint(ptr, x, (y - r + 1));

    return 0;
}

double stod(const char *str)
{
    double value;
    istringstream is(str);

    if(!(is >> value))
        throw invalid_argument(string(str) + " not convertible to double");

    return value;
}

void printArea(Circle *c)
{
    if(!c)
        return;

    cout << "Area of Circle(r=" << c->radius() << "): "
         << c->getArea() << " u^2\n";
}

void printPoint(Circle *c, double x, double y)
{
    cout << "(" << x << ", " << y << ") in Circle(r="
         << c->radius() << ", x=" << c->x() << ", y="
         << c->y() << "): "
         << (c->containsPoint(x, y) ? "True\n" : "False\n");
}

int usage()
{
    cout << "usage: " << PNAME << " x y r\n";
    return 1;
}
