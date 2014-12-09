#include "NeverAliveCell.h"

char NeverAliveCell::displayChar() {
    return 'N';
}

bool NeverAliveCell::willBeAliveInNextGeneration() {
    return true;
}
