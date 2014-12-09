

#ifndef __ALIVE_CELL_H__ 
#define __ALIVE_CELL_H__

#include "AbstractCell.h"

class AlwaysAliveCell : public AbstractCell {

    public:
	bool isAlive() {return true;}
	bool willBeAliveInNextGeneration() {return true;}
	char displayChar() {return 'A';}
};

#endif
