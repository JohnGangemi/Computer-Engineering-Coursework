// John A. Gangemi U6871-4612
// Exercise 9.15 Solution: Ex09_15.cpp
#include <iostream>
#include <string>
#include "TicTacToe.h" // include definition of class TicTacToe
using namespace std;

inline void displayHeader()
{
	string header = "Tic Tac Toe";
	cout << header << endl;
	for (unsigned int i = 0; i < header.size(); i++)
		cout << "-";
	cout << endl << endl;
}

int main()
{
	TicTacToe g; // creates object g of class TicTacToe 

	displayHeader();

	// loop game
	while (true)
	{
		cout << "Player One..." << endl;
		g.setPlayer(1); // sets player identification
		g.makeMove(); // invokes function makeMove
		if (g.getGameStatus() != 0) // check if game state has changed
			break;

		cout << "Player Two..." << endl;
		g.setPlayer(2);
		g.makeMove();
		if (g.getGameStatus() != 0)
			break;
	} 

	// conditionals based upon altered game state
	if (g.getGameStatus() == 1)
		cout << "Congratulations," << " player " << g.getPlayer() << " has won!"
		<< endl << "\n-program by John A. Gangemi\n" << endl;
	else 
		cout << "Game ended in a draw." << endl << "\n-program by John A. Gangemi\n" << endl;

	system("PAUSE");
	return 0;
} // end main


/**************************************************************************
* (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
* Pearson Education, Inc. All Rights Reserved.                           *
*                                                                        *
* DISCLAIMER: The authors and publisher of this book have used their     *
* best efforts in preparing the book. These efforts include the          *
* development, research, and testing of the theories and programs        *
* to determine their effectiveness. The authors and publisher make       *
* no warranty of any kind, expressed or implied, with regard to these    *
* programs or to the documentation contained in these books. The authors *
* and publisher shall not be liable in any event for incidental or       *
* consequential damages in connection with, or arising out of, the       *
* furnishing, performance, or use of these programs.                     *
**************************************************************************/
