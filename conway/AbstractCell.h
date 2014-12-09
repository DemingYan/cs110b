
#ifndef __Conway__AbstractCell__
#define __Conway__AbstractCell__

#include <iostream>

class ConwayWorld;

using namespace std;

class AbstractCell {
    
  protected:
    ConwayWorld *world;
    bool alive;
    int row;
    int column;
    
    int neighborCount();
    
  public:
    AbstractCell(ConwayWorld *w, int r, int c);
    AbstractCell();
	virtual ~AbstractCell() {}
	
    void setWorld(ConwayWorld *w, int r, int c);
    void setIsAlive(bool value);

    virtual bool isAlive() = 0;
    virtual bool willBeAliveInNextGeneration() = 0;
    virtual char displayChar() = 0;
};


#endif
