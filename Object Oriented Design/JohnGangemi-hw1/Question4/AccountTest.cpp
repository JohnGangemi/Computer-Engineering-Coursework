// HW 1 Question 4
// John Gangemi U6871-4612
// Program that creates two Account objects and test the member functions
#include <iostream>
#include "Account.h"
using namespace std;

int main()
{
	Account account1(50); // create an Account object
	Account account2(25); // create an Account object

	// display initial balance of each object
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;

	int withdrawalAmount; // stores withdrawal amount from user

	// withdrawal from account1
	cout << "\nEnter withdrawal amount for account1: "; // prompt
	cin >> withdrawalAmount; // obtain user input
	cout << "\n...attempting to subtract " << withdrawalAmount
		<< " from account1 balance\n\n";
	account1.debit(withdrawalAmount); // try to subtract from account1

	//display balances
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;

	// withdrawal from account2
	cout << "\nEnter withdrawal amount for account2: "; // prompt
	cin >> withdrawalAmount; // obtain user input
	cout << "\n...attempting to subtract " << withdrawalAmount
		<< " from account2 balance\n\n";
	account2.debit(withdrawalAmount); // try to subtract from account1

	//display balances
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;

	cout << endl;
	system("PAUSE");
	return 0;
}