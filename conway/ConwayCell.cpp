
#include "ConwayCell.h"
#include "ConwayWorld.h"

ConwayCell::ConwayCell(ConwayWorld *w, int &r, int &c) {
    world = w;
    row = r;
    column = c;
}

bool ConwayCell::willBeAliveInNextGeneration() {
    int count = neighborCount();

    if (isAlive()) {
    	return count == 2 || count == 3;
    } else {
    	return count == 3;
    }
}

bool ConwayCell::isAlive() {
    return alive;
}

char ConwayCell::displayChar() {
    return isAlive() ? 'O' : '.';
}

