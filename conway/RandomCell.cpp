/* Author: Kevin Morris
 * File: RandomCell.h
 * This file permutes a random cell in the Game of Life. */
#include "RandomCell.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

// Init srand with high entropic filesystem component /dev/urandom
void init_rand()
{
    int seed = time(NULL);

    ifstream ifs("/dev/urandom", ios::binary);
    
    if(ifs)
    {
        char b[sizeof(int)];
        ifs.read(b, sizeof(int));
        seed |= *reinterpret_cast<int*>(b);
    }

    srand(seed);
}

RandomCell::RandomCell()
{
}

bool
RandomCell::isAlive()
{
    return alive;
}

bool
RandomCell::willBeAliveInNextGeneration()
{
    alive = rand() % 2;
    return alive;
}

char
RandomCell::displayChar()
{
    return alive ? 'O' : '.';
}

