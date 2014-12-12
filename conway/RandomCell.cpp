/* Author: Kevin Morris
 * File: RandomCell.h
 * This file permutes a random cell in the Game of Life. */
#include "RandomCell.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

// Init srand with high entropic filesystem component /dev/urandom
// P.S. I would like to use this_style, but overridden functions are
// in camelCase, so that's why they're different.
void init_rand()
{
    int seed = time(NULL); // Get current time

    ifstream ifs("/dev/urandom", ios::binary);
    
    if(ifs)
    {
        // Read sizeof(int) [should be 4 bytes] from /dev/urandom for our seed
        char b[sizeof(int)];
        ifs.read(b, sizeof(int));
        seed |= *reinterpret_cast<int*>(b); // Cast to int* and dereference
    }

    srand(seed);
}

// I did not init_rand() here, since its only really needed once
// per program; constructing with init_rand() doesn't make sense
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

