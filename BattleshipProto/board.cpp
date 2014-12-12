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

Node::Node(const point& p, direction d, int s, Player *pl)
    : Ship(p, d, s)
{
    cout << "Node constructor called with ({"
         << p.getX() << ", " << p.getY() << "}, "
         << d << ", " << s << ")\n";

    length = s;
    origin_p = p;
    orientation = d;
    player = pl;
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

Player*
Node::parent() const
{
    return player;
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

void
Player::add(const Node& node)
{
    nodes.push_back(node);
}

bool
Player::shoot(const point& p)
{
    return false;
}

bool
Player::sunk()
{
    std::size_t count = 0;

    std::vector<Node>::iterator it;
    for(it = nodes.begin(); it != nodes.end(); ++it)
    {
        if((*it).isSunk())
            count += 1;
    }

    return count == nodes.size();
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

Board::Board() : Matrix(10, 10)
{
    /* Game board, 10x10; 100 cells */
    Player *player = new Player;
    Computer *cpu = new Computer;

    players[0] = player;
    players[1] = cpu;
}

Board::~Board()
{
    delete cpu;
    delete player;
}

Player*
Board::playRound()
{
    return player;
}

Player*
Board::sunk()
{
    for(int i = 0; i < 2; ++i)
        if(players[i]->sunk())
            return players[i];
    return NULL;
}

Game::Game()
{
}

Game::~Game()
{
}



