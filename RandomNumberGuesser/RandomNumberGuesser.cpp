/* Author: Kevin Morris
 * File: RandomNumberGuesser.cpp
 * This file defines an implementation of the derived class
 * RandomNumberGuesser */
#include "RandomNumberGuesser.h"
#include <cmath>
#include <cstdlib>
#include <cstdio>

// Delegating constructor to base class which also inits guess
RandomNumberGuesser::RandomNumberGuesser(int l, int h)
    : NumberGuesser(l, h)
{
    guess = (rand() % (high - low + 1)) + low;
}

int
RandomNumberGuesser::getCurrentGuess()
{
    // If a new higher or lower was found
    if(fixHigher() || fixLower())
    {
        // if mod == 0, return the last guess
        if(!(high - low + 1))
            return guess;
        guess = (rand() % (high - low + 1)) + low;
    }

    return guess;
}

bool
RandomNumberGuesser::fixHigher()
{
    if(high != originalHigh)
    {
        originalHigh = high;
        return true;
    }
    return false;
}

bool
RandomNumberGuesser::fixLower()
{
    if(low != originalLow)
    {
        originalLow = low;
        return true;
    }
    return false;
}

