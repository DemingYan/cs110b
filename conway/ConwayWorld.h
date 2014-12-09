
#ifndef __Conway__ConwayWorld__
#define __Conway__ConwayWorld__

#include <iostream>
#include "AbstractCell.h"

class ConwayWorld {

 private:
    int rows;
    int cols;
    AbstractCell*** cellGrid;
    
    AbstractCell*** createEmptyGrid();
    void deleteGrid(AbstractCell*** g);
    
 public:
    ConwayWorld(int r, int c);
    ~ConwayWorld();
    
    void display();
    void nextGeneration();
    
    void setIsAlive(int r, int c, bool isAlive);
    bool cellIsAlive(int r, int c);
    
    void replaceCell(AbstractCell* cell, int r, int c, bool isAlive);
};

#endif
