//
//  Board.cpp
//  Battleship
//
#include "board.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Player&
Player::insert(PlayerShip *ship)
{
    ships.push_back(ship);
    return *this;
}

bool
Player::collides(const PlayerShip& ship)
{
    for(ShipVec::iterator i = ships.begin(); i != ships.end(); ++i)
    {
        if((*i)->collidesWith(ship))
            return true;
    }

    return false;
}

void
Player::hit(const point& p)
{
    // Fake stub for virtualness
}

Player*
Player::opponent()
{
    return opp;
}

void
Player::opponent(Player *opp)
{
    this->opp = opp;
}

void
CPU::hit(const point& p)
{
    *lastHit = p;
}

PlayerShip::PlayerShip(const point& origin, direction dir,
                       int len, Player *parent)
    : Ship(origin, dir, len)
{
    p = parent;

    co_x = origin.getX();
    co_y = origin.getY();
    length = len;
    d = dir;
}

Board::Board(int w, int l) : width(w), length(l)
{
    // Everything will be set to NULL by default
    matrix.reserve(l);
    for(int i = 0; i < l; ++i)
        matrix.push_back(ShipVec(w));

    p = new Player;
    pv.push_back(p);

    cpu = new CPU;
    pv.push_back(cpu);

    p->opponent(cpu);
    cpu->opponent(p);

    for(int i = 0; i < 2; ++i)
    {
        p->insert(generateShip(p));
        cpu->insert(generateShip(cpu));
    }
}

Board::~Board()
{
    for(PlayerVec::iterator it = pv.begin(); it != pv.end(); ++it)
        delete (*it);
}

void
Board::print(ostream& os)
{

    for(int y = 0; y < length; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if(matrix[x][y])
            {
                os << matrix[x][y]->parent()->color() << ' ';
                
                if(matrix[x][y]->isHitAtPoint(point(x, y)))
                    os << 'X';
                else
                    os << '%';

                os << "\033[0m";
            }
            else
            {
                os << " \033[1;34m";
                
                if(miss.find(x) != miss.end() &&
                   miss[x].find(y) != miss[x].end())
                {
                    os << 'O';
                }
                else
                {
                    os << '~';
                }

                os << "\033[0m";
            }
        }
        os << endl;
    }
}

// This function stops as soon as one of the players are sunk,
// since one person's turn will cause this, it's okay not to check
// the others.
Player*
Board::sunk()
{
    int count;
    for(PlayerVec::iterator it = pv.begin(); it != pv.end(); ++it)
    {
        count = 0;

        for(ShipVec::iterator i = (*it)->begin(); i != (*it)->end(); ++i)
        {
            if((*i)->isSunk())
                count += 1;
        }

        if(count == 2)
            return (*it);
    }

    return NULL;
}

void
Board::playRound()
{
    print(cout);

    cout << "Player, choose two points (separated by spaces): ";

    int x, y;
    cin >> x >> y;

    while(x >= width || y >= length)
    {
        cout << "You have to choose points in the grid, from "
             << "(0, 0) to (" << width - 1 << ", " << length - 1
             << ")\n";
        cout << "Player, choose two points separated by spaces): ";
        cin >> x >> y;
    }

    // Target point
    point tp(x, y);

    if(!matrix[x][y])
    {
        if(miss.find(x) != miss.end() && miss[x].find(y) != miss[x].end())
        {
            cout << "You have already fired at this point, noob\n";
        }
        else
        {
            miss[x][y] = true;
            cout << "Agh! You miss\n";
        }
    }
    else
    {
        PlayerShip *ship = matrix[x][y];
        if(ship->isHitAtPoint(tp))
            cout << "You fired on a point that was already hit!\n";
        else
        {
            ship->shotFiredAtPoint(tp);
            cout << "Nice! You hit him at (" << tp.getX() << ", "
                 << tp.getY() << ")\n";
        }
    }

    cout << "\nCPU's turn, taking a shot at... ";
    if(!cpu->last())
    {
        tp = randomPoint();
        cout << "(" << tp.getX() << ", " << tp.getY() << ")\n";
    }
    else
    {
        int mod = 2;

        point *lp = cpu->last();
        cout << "(" << lp->getX() << ", " << lp->getY() << ")\n";

        tp = point(lp->getX() + rand() % mod, lp->getY() - rand() % mod);

        if(!matrix[tp.getX()][tp.getY()])
        {
            if(miss.find(x) != miss.end() && miss[x].find(y) != miss[x].end())
            {
                tp = point(lp->getX() + rand() % mod,
                            lp->getY() - rand() % mod);
            }
        }

    }
}

PlayerShip*
Board::generateShip(Player *player)
{
    PlayerShip *ship;

    int len = rand() % (3 + 1) + 2;
    direction dir = direction(rand() % 2);

    point origin = randomPoint(dir, len);

    ship = new PlayerShip(origin, dir, len, player);
    while(p->collides(*ship) || cpu->collides(*ship))
    {
        delete ship;
        origin = randomPoint(dir, len);
        ship = new PlayerShip(origin, dir, len, player);
    }

    cout << "Created ship: " << ship->x() << ", " << ship->y()
         << ", " << ship->dir() << ", " << ship->size() << endl;

    // Now distribute our points.
    if(ship->dir() == HORIZONTAL)
    {
        for(int x = ship->x(); x < ship->x() + ship->size(); ++x)
            matrix[x][ship->y()] = ship;
    }
    else
    {
        for(int y = ship->y(); y < ship->y() + ship->size(); ++y)
            matrix[ship->x()][y] = ship;
    }

    return ship;
}

point
Board::randomPoint(direction dir, int len)
{
    return point(rand() % (width - (dir ? 0 : len)),
                 rand() % (length - (dir ? len : 0)));
}


