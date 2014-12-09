
#ifndef __Conway__ConwayCell__
#define __Conway__ConwayCell__

#include <iostream>
#include "AbstractCell.h"

class ConwayWorld;

using namespace std;

class ConwayCell : public AbstractCell {
    
  public:
    ConwayCell(ConwayWorld* const, int&, int&);
    virtual bool isAlive();
    virtual bool willBeAliveInNextGeneration();
    virtual char displayChar();
};


#endif
