/* Author: Kevin Morris
 * File: RandomNumberGuesser.cpp
 * This file defines an interface of the derived class
 * RandomNumberGuesser */
#ifndef RANDOM_NUMBER_GUESSER_H
#define RANDOM_NUMBER_GUESSER_H

#include "NumberGuesser.h"

class RandomNumberGuesser : public NumberGuesser
{
private:
    int guess;

public:
    RandomNumberGuesser(int l, int h);
    virtual int getCurrentGuess();

private:
    bool fixHigher();
    bool fixLower();
};

#endif

