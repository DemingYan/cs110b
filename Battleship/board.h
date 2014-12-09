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

class Player;

class PlayerShip : public Ship
{
private:
    Player *p;

    int co_x, co_y, length;
    direction d;

public:
    PlayerShip(const point&, direction, int, Player *);

    const int x() const { return co_x; }
    const int y() const { return co_y; }
    const direction dir() const { return d; }
    const int size() const { return length; }

    const Player* parent() { return p; }

};

typedef std::vector<PlayerShip*> ShipVec;

class Player
{
private:
    ShipVec ships;
    Player *opp;

public:
    virtual ~Player() {}

    Player& insert(PlayerShip *);
    bool collides(const PlayerShip&);
    virtual const char* color() const { return "\033[1;32m"; }
    virtual const char* name() const { return "Player"; }

    virtual void hit(const point& p);

    Player* opponent();
    void opponent(Player *opp);

    ShipVec::iterator begin() { return ships.begin(); }
    ShipVec::iterator end() { return ships.end(); }
};

typedef std::vector<Player*> PlayerVec;

class CPU : public Player
{
private:
    point *lastHit;

public:
    CPU() : lastHit(NULL) {}
    const char* color() const { return "\033[1;31m"; }
    const char* name() const { return "CPU"; }

    void hit(const point& p);
    point *last() const { return lastHit; }

};

class Board
{
private:
    int width, length;

    std::vector<ShipVec> matrix;
    std::map<int, std::map<int, bool> > miss;

    PlayerVec pv;
    Player *p;
    CPU *cpu;

public:
    Board(int w, int l);
    ~Board();
    void print(std::ostream&);

    Player* sunk();
    void playRound();

private:
    PlayerShip* generateShip(Player *player);
    point randomPoint(direction = VERTICAL, int = 0);

};

#endif

