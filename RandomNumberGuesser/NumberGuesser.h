//
//  NumberGuesser.h
//  CS110B Max Luttrell
//
#ifndef NUMBERGUESSER_H
#define NUMBERGUESSER_H

#include <iostream>

class NumberGuesser
{
protected:
    int low;
    int originalLow;
    int high;
    int originalHigh;
    
public:
    NumberGuesser(int l, int h)
    {
        low = originalLow = l;
        high = originalHigh = h;
    }
    
    virtual ~NumberGuesser() { /* So we can use this if we want */ }

    virtual int getCurrentGuess()
    {
        return (high + low) / 2;
    }
    
    void higher()
    {
        low = getCurrentGuess() + 1;
    }
    
    void lower()
    {
        high = getCurrentGuess() - 1;
    }
    
    void reset()
    {
        low = originalLow;
        high = originalHigh;
    }
};

#endif

