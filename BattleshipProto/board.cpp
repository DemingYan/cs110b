//
//  Board.cpp
//  Battleship
//
#include "board.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Node::Node(const point& p, direction d, int s)
    : Ship(p, d, s)
{
    cout << "Node constructor called with ({"
         << p.getX() << ", " << p.getY() << "}, "
         << d << ", " << s << ")\n";

    length = s;
    origin_p = p;
    orientation = d;
}

Node::~Node()
{
    cout << "Node destructor called\n";
}

const point&
Node::origin() const
{
    return origin_p;
}

const direction
Node::dir() const
{
    return orientation;
}

const int
Node::size() const
{
    return length;
}

// Player Definitions
// ship_count default = 2
Player::Player(int ship_count)
{
    cout << "Player constructor called with ("
         << ship_count << ")\n";
}

Player::~Player()
{
    cout << "Player destructor called\n";
}

// Computer Definitions
// ship_count default = 2
Computer::Computer(int ship_count)
{
    cout << "Computer constructor called with ("
         << ship_count << ")\n";
}

Computer::~Computer()
{
    cout << "Computer destructor called\n";
}

// A matrix of nodes. This will represent our grid of water
// and ships for Battleship
Matrix::Matrix(int x, int y)
    : NestedVector<Node*>(y)
{
    cout << "Matrix constructor called with ("
         << x << ", " << y << ")\n";

    for(int i = 0; i < y; ++i)
        this->push_back(vector<Node*>(x));
}

Matrix::~Matrix()
{
    cout << "Matrix destructor called\n";
}


