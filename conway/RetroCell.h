#ifndef RETROCELL_H
#define RETROCELL_H

#include "AbstractCell.h"

class RetroCell : public AbstractCell
{
public:
    bool isAlive();
    bool willBeAliveInNextGeneration();
    char displayChar();
};

#endif

