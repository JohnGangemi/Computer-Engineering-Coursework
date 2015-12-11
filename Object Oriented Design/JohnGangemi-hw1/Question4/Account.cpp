// Account class method-function implementations
#include <iostream>
#include "Account.h"
using namespace std;

// constructor initializes accountBalance with supplied int argument
Account::Account(int balance)
{
	if (balance >= 0) // validate the balance being passed to the constructor
		accountBalance = balance;
	else
	{
		cout << "Initial account balance provided was invalid, "
			<< "the account balance now set to zero.\n";
		accountBalance = 0;
	}
}

// function that adds to the account balance
void Account::credit(int amount)
{
	accountBalance += amount; // increment the account balance by the value of amount variable
}

// function that subtracts from the account blance
void Account::debit(int amount)
{
	if (amount <= accountBalance) // validate the withdrawal amount is less than or equal to the account balance
		accountBalance = accountBalance - amount;
	else
		cout << "Debit amount exceeding account balance.\n\n";
}

// returns the current account balance
int Account::getBalance()
{
	return accountBalance; // return the current account balance value
}
