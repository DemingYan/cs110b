
#include <iostream>

#include "ConwayCell.h"
#include "ConwayWorld.h"
#include "AlwaysAliveCell.h"
#include "NeverAliveCell.h"
#include "RandomCell.h"
#include <unistd.h>

using namespace std;

bool userWantsAnotherGeneration() {
    char response;
    
    cout << "Another? (y/n): ";
    cin >> response;
    
    return response == 'y';
}

int main () {
    ConwayWorld world(15, 15);
    
    world.setIsAlive(1, 1, true);
    world.setIsAlive(1, 2, true);
    world.setIsAlive(2, 2, true);
    world.setIsAlive(2, 3, true);
    world.setIsAlive(3, 3, true);
    world.setIsAlive(3, 4, true);
    
    world.replaceCell(new AlwaysAliveCell(), 5, 5, false);
    world.replaceCell(new NeverAliveCell(), 9, 9, false);

    world.replaceCell(new RandomCell(), 9, 7, false);
    world.replaceCell(new RandomCell(), 8, 6, false);
    world.replaceCell(new RandomCell(), 10, 12, false);
    world.display();
    
    while(true) {
    //while (userWantsAnotherGeneration()) {
        world.nextGeneration();
        world.display();
        usleep(200 * 1000);
    }
}

