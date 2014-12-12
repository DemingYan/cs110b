/*
Author: Kevin Morris
File: board.cpp
This file is a collection of small data structures
that make up an implementation of the Battleship board game
Copyright (C) 2014 Kevin Morris
*/
#ifndef BOARD_H
#define BOARD_H

#include "ship.h"
#include <ostream>
#include <map>
#include <vector>

class Player;

template<typename T>
struct NestedVector : public std::vector<std::vector<T> >
{
    NestedVector(std::size_t sz) : std::vector<std::vector<T> >(sz) {}
};

class Node : public Ship
{
private:
    // Creating copies of our input variables so we can
    // use functions with them in this class; with access to
    // Ship's prototype, I would be able to pass vars through
    int length;
    point origin_p;
    direction orientation;
    Player *player;

public:
    Node(const point& p, direction d, int s, Player *pl);
    ~Node();

    // Returns our local copies of info
    const point& origin() const;
    const direction dir() const;
    const int size() const;
    Player* parent() const;

};

class Matrix : public NestedVector<Node*>
{
public:
    Matrix(int x, int y);
    ~Matrix();
};

class Player
{
protected:
    std::vector<point> shots;
    std::vector<point> hits;

    std::vector<Node> nodes;

public:
    Player(int ship_count = 2);
    virtual ~Player();

    virtual void add(const Node& node);

    virtual bool shoot(const point& p);
    virtual bool sunk();
};

class Computer : public Player
{
public:
    Computer(int ship_count = 2);
    ~Computer();
};

class Board : public Matrix
{
private:
    Player *player;
    Computer *cpu;

    Player *players[2];

public:
    Board();
    ~Board();

    Player* playRound();
    Player* sunk();
};

class Game
{
private:
    Board board;

public:
    Game();
    ~Game();
};

#endif



