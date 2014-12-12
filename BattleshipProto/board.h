//
//  Board.h
//  Battleship
//
#ifndef BOARD_H
#define BOARD_H

#include "ship.h"
#include <ostream>
#include <map>
#include <vector>

template<typename T>
struct NestedVector : public std::vector<std::vector<T> >
{
    NestedVector(std::size_t sz) : std::vector<std::vector<T> >(sz) {}
};

class Node : public Ship
{
private:
    int length;
    point origin_p;
    direction orientation;

public:
    Node(const point& p, direction d, int s);
    ~Node();

    const point& origin() const;
    const direction dir() const;
    const int size() const;

};

class Player
{
public:
    Player(int ship_count = 2);
    virtual ~Player();
};

class Computer : public Player
{
public:
    Computer(int ship_count = 2);
    ~Computer();
};

class Matrix : public NestedVector<Node*>
{
public:
    Matrix(int x, int y);
    ~Matrix();
};


#endif

