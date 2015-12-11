#include <iostream>
#include <iomanip>
#include <string>
#include "TicTacToe.h"
using namespace std;

TicTacToe::TicTacToe() 
{
	setBoard(); // prepare the game board
}

void TicTacToe::setBoard()
{
	// iterate through the array and initialize all values to zero
	for (unsigned int i = 0; i < arraySize; i++)
	{
		for (unsigned int j = 0; j < arraySize; j++)
			board[i][j] = 0;
	}
}

void TicTacToe::setPlayer(const int &playerId)
{
	playerIdentification = playerId;
}

void TicTacToe::setGameStatus(const int gameBoard[][arraySize])
{
	bool won = isWon(gameBoard); // store value of isWon()
	bool draw = isDraw(gameBoard); // store value of isDraw()

	// set the game state
	if (won)
		gameState = 1;
	else if (draw)
		gameState = 2;
	else if (!won && !draw)
		gameState = 0;
}

void TicTacToe::setInput(const int gameBoard[][arraySize])
{
	while (true)
	{
		string rowStr, columnStr;
		bool valid = true;

		// prompt for input
		cout << "Choose a row and column (ex. 1 2, 0 1, 2 0): ";
		cin >> rowStr >> columnStr;
		string temp = rowStr + columnStr; // hold contents of rowStr and columnStr

		if (temp.size() == 2) // check if size of string is correct
		{
			for (unsigned int ch = 0; ch < temp.size(); ch++)
			{
				if (!isdigit(temp[ch]) || (temp[ch] < '0' || temp[ch] > '2')) // check if character values in string are allowed
				{
					cout << "*Invalid Input*\n";
					valid = false;
					break;
				}
			}
		}
		else
		{
			cout << "*Invalid Input*\n";
			valid = false;
		}

		if (valid) // process only if valid is true
		{
			if (gameBoard[stoi(rowStr)][stoi(columnStr)] != 0) // check if slot on board is open
			{
				cout << "*Already Selected*\n";
				valid = false;
			}
		}

		if (valid)
		{
			setRow(stoi(rowStr));
			setColumn(stoi(columnStr));
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
		}
	}
}

void TicTacToe::setRow(const int &selectedRow)
{
	row = selectedRow;
}

void TicTacToe::setColumn(const int &selectedColumn)
{
	column = selectedColumn;
}

int TicTacToe::getPlayer()
{
	return playerIdentification;
}

int TicTacToe::getGameStatus()
{
	return gameState;
}

int TicTacToe::getRow()
{
	return row;
}

int TicTacToe::getColumn()
{
	return column;
}

void TicTacToe::makeMove()
{
	setInput(board); 
	updateBoard(board);
	setGameStatus(board);
	displayBoard(board);
}

void TicTacToe::updateBoard(int gameBoard[][arraySize])
{
	// change array by reference
	gameBoard[getRow()][getColumn()] = getPlayer();
}

void TicTacToe::displayBoard(const int gameBoard[][arraySize])
{
	cout << endl;

	// iterate through array to display correct data
	for (unsigned int i = 0; i < arraySize; i++)
	{
		for (unsigned int j = 0; j < arraySize; j++)
		{
			if (gameBoard[i][j] == 0)
				cout << setw(4) << "-";
			else if (gameBoard[i][j] == 1)
				cout << setw(4) << "1";
			else 
				cout << setw(4) << "2";
		}
		cout << endl << endl;
	}
}

bool TicTacToe::isDiagonal(const int &player, const int gameBoard[][arraySize])
{
	bool selection = false;

	if (gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player)
		selection = true;
	if (!selection)
	{
		if (gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player)
			selection = true;
	}

	if (selection)
		return true;
	else
		return false;
}

bool TicTacToe::isHorizontal(const int &player, const int gameBoard[][arraySize])
{
	bool selection = false;

	if (gameBoard[0][0] == player && gameBoard[0][1] == player && gameBoard[0][2] == player)
		selection = true;
	if (!selection)
	{
		if (gameBoard[1][0] == player && gameBoard[1][1] == player && gameBoard[1][2] == player)
			selection = true;
		if (!selection)
		{
			if (gameBoard[2][0] == player && gameBoard[2][1] == player && gameBoard[2][2] == player)
				selection = true;
		}
	}

	if (selection)
		return true;
	else
		return false;
}

bool TicTacToe::isVertical(const int &player, const int gameBoard[][arraySize])
{
	bool selection = false;

	if (gameBoard[0][0] == player && gameBoard[1][0] == player && gameBoard[2][0] == player)
		selection = true;
	if (!selection)
	{
		if (gameBoard[0][1] == player && gameBoard[1][1] == player && gameBoard[2][1] == player)
			selection = true;
		if (!selection)
		{
			if (gameBoard[0][2] == player && gameBoard[1][2] == player && gameBoard[2][2] == player)
				selection = true;
		}
	}

	if (selection)
		return true;
	else
		return false;
}

bool TicTacToe::isWon(const int gameBoard[][arraySize])
{
	if (isDiagonal(getPlayer(), gameBoard) || isHorizontal(getPlayer(), gameBoard) || isVertical(getPlayer(),gameBoard))
		return true;
	else
		return false;
}

bool TicTacToe::isDraw(const int gameBoard[][arraySize])
{
	int count = 0;

	// iterate through array and tally the number of changed game board slots
	for (unsigned int i = 0; i < arraySize; i++)
	{
		for (unsigned int j = 0; j < arraySize; j++)
		{
			if (gameBoard[i][j] != 0)
				count++;
		}
	}

	// check if all game board slots have changed
	if (count == 9)
		return true;
	else
		return false;
}
