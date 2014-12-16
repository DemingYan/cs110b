/*
Author: Kevin Morris
File: board.cpp
This file is a collection of small data structures
that make up an implementation of the Battleship board game
Copyright (C) 2014 Kevin Morris
*/
#include "board.h"
#include <cstdlib>
#include <iostream>
using namespace std;

/* BShip definitions */
BShip::BShip(const point& p, direction d, int sz, Player *parent)
    : Ship(p, d, sz)
{
    p_origin = p;
    p_orientation = d;
    p_length = sz;
    p_parent = parent;
}

const point& BShip::origin() const
{
    return p_origin;
}

const direction BShip::orientation() const
{
    return p_orientation;
}

const int BShip::size() const
{
    return p_length;
}

const Player* BShip::parent() const
{
    return p_parent;
}

/* Player definitions */
Player::Player(Player **opponent) : opp(opponent)
{ }

Player::~Player()
{
    vector<BShip*>::iterator it;
    for(it = ps.begin(); it != ps.end(); ++it)
        delete *it;
}

const Player* Player::opponent() const
{
    return *opp;
}

void Player::add(BShip *ship)
{
    ps.push_back(ship);
}

bool Player::collides(BShip *ship)
{
    vector<BShip*>::iterator it;
    for(it = ps.begin(); it != ps.end(); ++it)
    {
        if((*it)->collidesWith(*ship))
            return true;
    }

    return false;
}

bool Player::sunk()
{
    size_t count = 0;
    vector<BShip*>::iterator it;
    for(it = ps.begin(); it != ps.end(); ++it)
    {
        if((*it)->isSunk())
            count += 1;
    }

    return count == ps.size();
}

const char* Player::name() const
{
    return "Player";
}

/* CPU definitions */
CPU::CPU(Player **opponent) : Player(opponent)
{
    prevHit = NULL;
}

const char* CPU::name() const
{
    return "CPU";
}

/* Node definitions */
Node::Node(const point& p, const string& col, char ch, BShip *ship)
{
    isHit = false;
    bship = ship;
    this->p = p;
    cellColor = col;
    cellChar = ch;
}

Node::~Node()
{
}

const BShip* Node::ship()
{
    return bship;
}

const bool Node::hit() const
{
    return isHit;
}

bool Node::hit(bool h)
{
    isHit = h;
    return isHit;
}

const point& Node::origin() const
{
    return p;
}

/* WaterNode definitions */
WaterNode::WaterNode(const point& p) : Node(p, BLUE, '~', NULL) { }

bool WaterNode::hit(bool h)
{
    if(Node::hit())
        return false;

    cellChar = 'O';
    return Node::hit(h);
}

/* PNode definitions */
PNode::PNode(const point& p, BShip *parent)
    : Node(p, GREEN, '%', parent)
{
}

bool PNode::hit(bool h)
{
    if(Node::hit())
        return false;

    BShip *ship = const_cast<BShip*>(Node::ship());
    ship->shotFiredAtPoint(origin());

    cellChar = 'X';
    return Node::hit(h);
}

CNode::CNode(const point& p, BShip *parent)
    : Node(p, BLUE, '~', parent)
{
}

bool CNode::hit(bool h)
{
    if(Node::hit())
        return false;

    BShip *ship = const_cast<BShip*>(Node::ship());
    ship->shotFiredAtPoint(origin());

    cellColor = RED;
    cellChar = 'X';
    return Node::hit(h);
}

/* Board definitions */
Board::Board(int x, int y) : width(y), height(y)
{
    setup();
}

Board::~Board()
{
    delete cpu;
    delete player;

    for(int i = 0; i < width; ++i)
    {
        for(int j = 0; j < height; ++j)
        {
            if(table[i][j])
                delete table[i][j];
        }
    }

}

void Board::print()
{
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            cout << ' ' << table[x][y]->color()
                 << table[x][y]->cell() << DEF;
        }
        cout << endl;
    }
}

void Board::playerShot()
{
    int x, y;
    cout << player->name() << ", enter a point sep. by spaces: ";
    cin >> x >> y;
    
    point target(x, y);
    if(table[x][y]->hit())
    {
        cout << "That point was already hit, try again\n";
        return playerShot();
    }

    table[x][y]->hit(true);
}

void Board::cpuShot()
{
}

Player* Board::sunk()
{
    for(int i = 0; i < 2; ++i)
    {
        if(p[i]->sunk())
            return p[i];
    }

    return NULL;
}

void Board::setup()
{
    player = new Player(&cpu);
    cpu = new CPU(&player);

    p[0] = player;
    p[1] = cpu;

    for(int i = 0; i < 2; ++i)
    {
        BShip *ship = newShip(player);
        player->add(ship);
        distributeNodes<PNode>(ship);
    }

    for(int i = 0; i < 2; ++i)
    {
        BShip *ship = newShip(cpu);
        cpu->add(ship);
        distributeNodes<CNode>(ship);
    }

    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            if(!table[x][y])
                table[x][y] = new WaterNode(point(x, y));
        }
    }

}

BShip* Board::newShip(Player *parent)
{
    direction dir = direction(rand() % 2);
    int shipLen = rand() % (3 + 1) + 2;

    point rp(randomPoint(dir, shipLen));
    BShip *ship = new BShip(rp, dir, shipLen, parent);
    while(player->collides(ship) || cpu->collides(ship))
    {
        rp = randomPoint(dir, shipLen);
        delete ship;
        ship = new BShip(rp, dir, shipLen, parent);
    }

    return ship;
}

point Board::randomPoint(direction shipDir, int shipLen)
{
    return point(rand() % (width - (shipDir ? 0 : shipLen)),
                 rand() % (height - (shipDir ? shipLen : 0)));
}


