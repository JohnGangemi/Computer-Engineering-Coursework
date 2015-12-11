/*
* Name.
* John A. Gangemi U6871-4612
* Description.
* Implementation for Life class
*/

#include <iostream>

#include "Life.h"

using namespace std;

// Constructor
Life::Life(int nrows, int ncols) :
max_row(nrows), max_col(ncols)
{
	this->grid = this->build_grid();
}

// Destructor
Life::~Life()
{
	this->destroy_grid(this->grid);
}

// Initialize the game (reading from the user)
void 
Life::initialize()
{
	int row, col;
	int tmp;

	// TODO: Initialize next_state to all 0 values (all cells die by default).
	// iterate through the rows and columns of the next_state 2D array 
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			next_state[i][j] = 0;
		}
	}
	// ENDDO
		
	cout << "Enter the live neighbor counts (between 0 and 8)\n"
	 << "that will cause a dead cell\n"
	 << "to become alive in the next generation,\n"
	 << "terminating input with -1" << endl << endl;

	// TODO: Read counts from the user and update next_state.
	cin >> tmp;
	while (tmp != -1)
	{
		if (tmp >= 0 || tmp <= 8)
			next_state[0][tmp] = 1;
		else 
			// handle invalid user input with prompt
			cout << "Value can only range from 0 to 8 inclusive, try again.\n";

		cin >> tmp;
	}
	tmp = 0; // reset the tmp variable
	// ENDDO

	cout << "\nEnter the live neighbor counts (between 0 and 8)\n"
	 << "that will cause a live cell\n"
	 << "to continue living in the next generation,\n"
	 << "terminating input with -1" << endl << endl;

	// TODO: Read counts from the user and update next_state.
	cin >> tmp;
	while (tmp != -1)
	{
		if (tmp >= 0 || tmp <= 8)
			next_state[1][tmp] = 1;
		else 
			// handle invalid user input with prompt
			cout << "Value can only range from 0 to 8 inclusive, try again.\n";

		cin >> tmp;
	}
	// ENDDO

	cout << "\nList the coordinates for living cells.\n"
	 << "Terminate the list with the special pair -1 -1" << endl;

	// TODO: Read coordinates from the user, verify their validity,
	// and update the grid.
	cin >> row >> col;
	while (row != -1 || col != -1)
	{
		if (row >= 1 && row <= max_row)
		{
			if (col >= 1 && col <= max_col)
				grid[row][col] = 1;
			else
				// handle invalid user input with prompt
				cout << "Column " << col << " is out of range.\n";
		}
		else
			// handle invalid user input with prompt
			cout << "Row " << row << " is out of range.\n";

		cin >> row >> col;
	}
	// ENDDO
}

// Print the grid to cout.
void 
Life::print()
{
	cout << "\nCurrent Life configuration:\n\n";
	for (int row = 1; row < max_row + 1; ++row)
	{
		for (int col = 1; col < max_col + 1; ++col)
		{
			cout << (grid[row][col] ? '*' : ' ');
		}
		cout << endl;
	}
	cout << endl;
}

// Update the contents of the grid to the next generation.
void 
Life::update()
{
	// TODO: Create a new grid.
	// store hedge plus grid sizes as const terms
	const int row_size = max_row + 2;
	const int col_size = max_col + 2;
	
	// initialize pointer-to-pointer variable using new operator
	int **tmp_grid = new int*[row_size]; // create int array of pointers (rows)
	for (int i = 0; i < row_size; ++i)
	{
		tmp_grid[i] = new int[col_size]; // create int array (columns)
	}

	// initialize all elements of multidimensional array to zero
	for (int i = 0; i < row_size; ++i)
	{
		for (int j = 0; j < col_size; ++j)
		{
			tmp_grid[i][j] = 0;
		}
	}
	// ENDO

	// TODO: Populate the new grid according to the rules.
	// iterate through multidimensional array not including the hedge
	for (int i = 1; i <= max_row; ++i)
	{
		for (int j = 1; j <= max_col; ++j)
		{
			// using next_state array determine cell's next generation
			// function call to neighborCount() as array index eliminates the need for a separate variable
			if (grid[i][j] == 0)
				tmp_grid[i][j] = next_state[0][neighborCount(i, j)];
			else
				tmp_grid[i][j] = next_state[1][neighborCount(i, j)];
		}
	}
	// ENDDO

	// TODO: Update the game with the new configuration.
	// (You can either copy the data back or replace the original grid,
	// but be sure to destroy the grid you no longer need.)
	for (int i = 0; i < row_size; ++i)
	{
		for (int j = 0; j < col_size; ++j)
		{
			// update original grid with temporary grid's contents
			grid[i][j] = tmp_grid[i][j];
		}
	}

	// delete the temporary grid declared using dynamic memory allocation
	for (int i = 0; i < row_size; ++i)
	{
		delete[] tmp_grid[i]; // delete columns
	}

	delete[] tmp_grid; // delete rows
	// ENDDO
}

// Build a new empty grid.
int **
Life::build_grid()
{
	int **new_grid;

	// TODO: Create and initialize the new grid.
	// store hedge plus grid sizes as const terms
	const int row_size = max_row + 2;
	const int col_size = max_col + 2;

	// initialize pointer-to-pointer variable using new operator
	new_grid = new int*[row_size];
	for (int i = 0; i < row_size; ++i)
	{
		new_grid[i] = new int[col_size];
	}

	// initialize all elements of multidimensional array to zero
	for (int i = 0; i < row_size; ++i)
	{
		for (int j = 0; j < col_size; ++j)
		{
			new_grid[i][j] = 0;
		}
	}

	// return pointer-to-pointers of type int
	return new_grid;
	// ENDDO
}

// Destroy the specified grid.
void 
Life::destroy_grid(int ** grid)
{
	// TODO: Implement the method.
	for (int i = 0; i < max_row + 2; ++i)
	{
		delete[] grid[i]; // delete columns of grid
	}

	delete[] grid; // delete rows of grid
	// ENDDO
}

// Count the neighbors of the specified cell.
int 
Life::neighborCount(int row, int col)
{
	int count = 0;

	for (int i = row - 1; i <= row + 1; ++i)
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			count += grid[i][j];
		}
	}

	count -= grid[row][col];
	return count;
}

/* vim: set et sw=4 ts=4: */
