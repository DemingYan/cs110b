/* Author: Kevin Morris
 * File: RandomCell.h
 * This file permutes a random cell in the Game of Life. */
#ifndef RANDOMCELL_H
#define RANDOMCELL_H

#include "AbstractCell.h"

// A function used to pop srand() for the program; needs to be used
// at least once for RandomCell
void init_rand();

class RandomCell : public AbstractCell
{
public:
    bool isAlive();
    bool willBeAliveInNextGeneration();
    char displayChar();
};

#endif

