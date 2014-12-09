
#include "AbstractCell.h"
#include "ConwayWorld.h"

AbstractCell::AbstractCell(ConwayWorld *w, int r, int c) {
    world = w;
    row = r;
    column = c;
}

AbstractCell::AbstractCell() {
    alive = false;
    world = NULL;
}

void AbstractCell::setWorld(ConwayWorld *w, int r, int c) {
    world = w;
    row = r;
    column = c;
}

void AbstractCell::setIsAlive(bool value) {
    alive = value;
}

int AbstractCell::neighborCount() {
    int count = 0;

    // Count All nine cells in ajacent rows and columns
    
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = column - 1; c <= column + 1; c++) {
            if (world->cellIsAlive(r,c)) {
                count++;
            }
        }
    }

    if (isAlive()) count--;

    return count;
}

