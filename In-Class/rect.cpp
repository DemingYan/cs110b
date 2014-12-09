#include <cstring>
#include <iostream>
using namespace std;

class Rectangle
{
    double width, length;
    char *name;

public:
    Rectangle() : name(NULL) {}

    Rectangle(double w, double l, const char *n)
        : name(new char[strlen(n) + 1])
    {
        width = w;
        length = l;
        strcpy(name, n);
    }

    ~Rectangle()
    {
        if(name)
            delete [] name;
    }

    void setWidth(double w)
    {
        width = w;
    }

    void setLength(double l)
    {
        length = l;
    }

    double getWidth()
    {
        return width;
    }

    double getLength()
    {
        return length;
    }

    double getArea()
    {
        return width * length;
    }

    double getPerimeter()
    {
        return (2 * width) + (2 * length);
    }

    bool isSquare()
    {
        return width == length;
    }

    Rectangle& operator=(const Rectangle& other)
    {
        length = other.length;
        width = other.width;
        if(name)
        {
            delete [] name;
            name = NULL;
        }

        name = new char[strlen(other.name) + 1];
        strncpy(name, other.name, strlen(other.name));

        return *this;
    }

    bool operator<(const Rectangle& other)
    {
        return (length * width) < (other.length * other.width);
    }

    bool operator>(const Rectangle& other)
    {
        return (length * width) > (other.length * other.width);
    }

};

int main()
{
    Rectangle rect(69.3, 74.6, "Rectangle");
    cout << "Rectangle: " << rect.getWidth() << " by " << rect.getLength()
         << endl;

    cout << "Rectangle area: " << rect.getArea() << endl
         << "Rectangle perimeter: " << rect.getPerimeter() << endl
         << "Is this rectangle a square? "
         << (rect.isSquare() ? "Yes\n" : "No\n");

    Rectangle square(50, 50, "Square");
    cout << "Rectangle: " << square.getWidth() << " by " << square.getLength()
         << endl;

    cout << "Rectangle area: " << square.getArea() << endl
         << "Rectangle perimeter: " << square.getPerimeter() << endl
         << "Is this rectangle a square? "
         << (square.isSquare() ? "Yes\n" : "No\n");

    cout << (rect > square) << endl
         << (rect < square) << endl;

    rect = square;

    cout << (rect > square) << endl;

    cout << rect.getLength() << 'x' << rect.getWidth() << endl;

    return 0;
}

