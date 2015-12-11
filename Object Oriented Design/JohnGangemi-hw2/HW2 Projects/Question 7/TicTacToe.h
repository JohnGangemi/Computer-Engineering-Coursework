#ifndef TICTACTOE_H
#define TICTACTOE_H

const unsigned int arraySize = 3; // global variable to specify array dimensions

class TicTacToe
{
public:
	TicTacToe(); // constructor 

	// set functions
	void setBoard(); // initialize the game board to all zeros
	void setPlayer(const int &); // define the current user
	void setGameStatus(const int[][arraySize]); // check the game state for win or draw
	void setInput(const int[][arraySize]); //validate input for row and column
	void setRow(const int &); // set the private data member row
	void setColumn(const int &); // set the private data member column

	// get functions
	int getPlayer(); // get the current user
	int getGameStatus(); // get the current game state
	int getRow(); // get row selection from user
	int getColumn(); // get column selection from user

	// utility functions
	void makeMove(); // begin play
	void updateBoard(int[][arraySize]); // update game board with user selection
	void displayBoard(const int[][arraySize]); // display the state of game board
	bool isWon(const int[][arraySize]); // check if user has won
	bool isDraw(const int[][arraySize]); // check if game has ended in a draw
	bool isDiagonal(const int &, const int[][arraySize]); // subset of isWon()
	bool isVertical(const int &, const int[][arraySize]); // subset of isWon()
	bool isHorizontal(const int &, const int[][arraySize]); // subset of isWon()

private:
	int board[arraySize][arraySize]; // multidimensional array that represents a game board
	int row; // store the user selected row
	int column; // store the user selected column
	int playerIdentification; // store the player identification
	int gameState; // store the game state
};

#endif