/* Author: Kevin Morris
 * File: RandomCell.h
 * This file permutes a random cell in the Game of Life. */
#ifndef RANDOMCELL_H
#define RANDOMCELL_H

#include "AbstractCell.h"

void init_rand();

class RandomCell : public AbstractCell
{
public:
    RandomCell();
    bool isAlive();
    bool willBeAliveInNextGeneration();
    char displayChar();
};

#endif

