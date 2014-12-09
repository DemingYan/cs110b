
#include "ConwayWorld.h"
#include "AbstractCell.h"
#include "ConwayCell.h"

ConwayWorld::ConwayWorld(int r, int c) {
    rows = r;
    cols = c;
    
    // Create the cell grid
    cellGrid = createEmptyGrid();
}

/**
 * Destructor
 */

ConwayWorld::~ConwayWorld() {
    deleteGrid(cellGrid);
}

/**
 * This private helper generates a grid of Conway Cells using 
 * the member variables 'rows' and 'cols' to determine the size
 */

AbstractCell*** ConwayWorld::createEmptyGrid() {
    AbstractCell ***grid = new AbstractCell**[rows];
    
    for (int r = 0; r < rows; r++) {
        grid[r] = new AbstractCell*[cols];
        
        for (int c = 0; c < cols; c++) {
            grid[r][c] = new ConwayCell(this, r, c);
        }
    }
    
    return grid;
}

/**
 * This private helper method deallocates a grid
 */

void ConwayWorld::deleteGrid(AbstractCell*** g) {
    
    // Delete each row
    for (int r = 0; r < rows; r++) {
        
        // Delete each cell in the row
        for (int c = 0; c < cols; c++) {
            delete g[r][c];
        }
        
        delete [] g[r];
    }
    
    // Delete the row pointers
    delete [] g;
}


/**
 * Displays a ASCII version of the grid using cout.
 */
void ConwayWorld::display() {

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << cellGrid[r][c]->displayChar() << " ";
        }
        
        cout << endl;
    }
}

// Generates the next generation grid and stores it in cellGrid

void ConwayWorld::nextGeneration() {
    // Create a boolean grid with the same size
    bool** boolGrid = new bool*[rows];
    
    for (int r = 0; r < rows; r++) {
        boolGrid[r] = new bool[cols];
    }
    
    // Loop through the grid to initialize the boolean grid.
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            boolGrid[r][c] = cellGrid[r][c]->willBeAliveInNextGeneration();
        }
        
        cout << endl;
    }
    
    // Loop through again setting the cells to the next generation
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cellGrid[r][c]->setIsAlive(boolGrid[r][c]);
        }
        
        cout << endl;
    }

    // Delete the bool grid
    for (int r = 0; r < rows; r++) {
        delete [] boolGrid[r];
    }
    
    delete [] boolGrid;
}

/**
 * Sets the life status of the cell at r, c
 */

void ConwayWorld::setIsAlive(int r, int c, bool isAlive) {
    cellGrid[r][c]->setIsAlive(isAlive);
}


/**
 * This member function checks to see if the coordinates are in the grid. 
 * if they are then it checks to see if the cell at the coordinates is alive
 */

bool ConwayWorld::cellIsAlive(int r, int c) {
    
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        return false;
    } else {
        return cellGrid[r][c]->isAlive();
    }
}

/**
 * replaces the cell at r, c with this new cell
 */

void ConwayWorld::replaceCell(AbstractCell* cell, int r, int c, bool isAlive) {
    // delete the old cell
    delete cellGrid[r][c];
    
    // Set up the new cell
    cell->setWorld(this, r, c);
    cell->setIsAlive(isAlive);
    
    // add the address of the new cell
    cellGrid[r][c] = cell;
}


