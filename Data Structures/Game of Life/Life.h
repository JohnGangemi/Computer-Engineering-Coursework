/*
 * Name.
 * 
 * Description.
 */

#pragma once

#ifndef LIFE_H
#define LIFE_H

using namespace std;

class Life
{
    public:
        // Constructor
        Life(int nrows,int ncols);

        // Destructor
        ~Life();

        // Input the rules of the game and the list of live cells.
        void initialize();

        // Print the grid to the given stream.
        void print(ostream& out);

        // Print the grid to cout.
        void print();

        // Update the contents of the grid to the next generation.
        void update();

    private:
        // The grid itself.
        // Constructor must create a dynamic array of dynamic arrays of int.
        // (I'll explain why in class.)
        int **grid;
        int max_row;
        int max_col;

        // next_state[0][j] is the new state for a dead cell with j live neighbors
        // next_state[1][j] is the new state for a live cell with j live neighbors
        // Constructor should initialize next_state[i][j] to i (no change)
        int next_state[2][9];

        // Count the neighbors of the specified cell.
        int neighborCount(int row, int col);

        // Create a new empty grid.
        int ** build_grid();

        // Destroy the provided grid.
        void destroy_grid(int ** grid);
};

#endif

/* vim: set et sw=4 ts=4: */
