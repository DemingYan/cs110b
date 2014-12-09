

#ifndef Conway_StoneCell_H
#define Conway_StoneCell_H

#include <iostream>
#include "AbstractCell.h"

class NeverAliveCell : public AbstractCell {

  public:
    NeverAliveCell(ConwayWorld *w, int r, int c, bool alive);
    NeverAliveCell() {}
    bool isAlive() {return false;}
    bool willBeAliveInNextGeneration();
    char displayChar();
};

#endif
