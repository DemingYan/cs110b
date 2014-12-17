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

// sh/bash/zsh color escape codes
const char DEF[]   = "\033[0m";
const char RED[]   = "\033[1;31m";
const char GREEN[] = "\033[1;32m";
const char YELLO[] = "\033[1;33m";
const char BLUE[]  = "\033[1;34m";

template<typename T1, typename T2>
struct NestedMap : public std::map<T1, std::map<T1, T2> >
{ /* Just aliasing a nested map container */ };

class Player;

// B[attle]Ship class
// This class is basically overriding Ship completely in
// order to give the user access to Ship's information
// This is doubling the amount of memory used by the Ship
// class, but is necessary for constant node access
class BShip : public Ship
{
private:
    point p_origin;
    direction p_orientation;
    int p_length;
    Player *p_parent;

public:
    BShip(const point& p, direction d, int sz, Player *player);

    const point& origin() const;
    const direction orientation() const;
    const int size() const;
    const Player* parent() const;

};

class Player
{
private:
    // Player's collection of ships
    std::vector<BShip*> ps;

    // Store a pointer to the opponent's pointer
    Player **opp;

public:
    Player(Player **opponent);
    virtual ~Player();

    const Player* opponent() const;
    void add(BShip *ship);
    bool contains(const point& p);
    bool collides(BShip *ship);
    bool sunk();

    virtual point shoot(int, int);
    virtual const char* name() const;
};

class Node;

class CPU : public Player
{
private:
    Node *prevHit;

public:
    CPU(Player **opponent);
    const char* name() const;

    point shoot(int, int);
    Node *& last() { return prevHit; }
};

class Node
{
private:
    // Stuff
    bool isHit;
    BShip *bship;
    point p;

protected:
    std::string cellColor;
    char cellChar;

public:
    Node(const point& p, const std::string& col, char ch, BShip *ship);
    virtual ~Node();

    const BShip* ship();

    const bool hit() const;
    virtual bool hit(bool h);

    const point& origin() const;

    const std::string& color() const { return cellColor; }
    char cell() const { return cellChar; }


};

class WaterNode : public Node
{
public:
    WaterNode(const point& p);
    bool hit(bool h); // Override
};

class PNode : public Node
{
public:
    PNode(const point& p, BShip *parent);
    bool hit(bool h); // Override
};

class CNode : public Node
{
public:
    CNode(const point& p, BShip *parent);
    bool hit(bool h); // Override
};

/* Board class declaration, used to play one Battleship game
 * against the computer */
class Board
{
private:
    NestedMap<int, Node*> table;

    int width;
    int height;

    Player *player;
    Player *cpu;

    Player *p[2];

public:
    Board(int x = 10, int y = 10);
    ~Board();

    void print();
    void playerShot();
    void cpuShot();

    Player* sunk();

private:
    void setup();

    BShip* newShip(Player *parent);
    point randomPoint(direction shipDir, int shipLen);

    template<typename NodeT>
    void distributeNodes(BShip *ship)
    {
        if(ship->orientation() == HORIZONTAL)
        {
            int cx = ship->origin().getX();
            for(int x = cx; x < cx + ship->size(); ++x)
            {
                point newPoint(x, ship->origin().getY());
                table[x][ship->origin().getY()] = new NodeT(newPoint, ship);
            }
        }
        else
        {
            int cy = ship->origin().getY();
            for(int y = cy; y < cy + ship->size(); ++y)
            {
                point newPoint(ship->origin().getX(), y);
                table[ship->origin().getX()][y] = new NodeT(newPoint, ship);
            }
        }
    }

};

#endif



