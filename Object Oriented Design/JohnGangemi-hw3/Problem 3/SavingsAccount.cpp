#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "SavingsAccount.h"
using namespace std;

double SavingsAccount::annualInterestRate = 0.0;

SavingsAccount::SavingsAccount() // default constructor
:SavingsAccount( 0.0 ) // delegate to SavingsAccount(const double&)
{
}

SavingsAccount::SavingsAccount(const double &balance) // overloaded constructor
{
	// check if user entered value is negative
	if (balance < 0.0)
		throw invalid_argument("Savings account balance must be greater than or equal to 0");
	else
		savingsBalance = balance;
}

const void SavingsAccount::calculateMonthlyInterest()
{
	// calculate the monthly interest
	double monthly_interest = savingsBalance * (annualInterestRate / 12);
	// add monthly interest to current balance
	savingsBalance += monthly_interest;
	// check if the balance is negative after computations
	if (savingsBalance < 0)
		throw invalid_argument("Error with calculating the monthly interest");
}

const void SavingsAccount::printBalance()
{
	// use fixed and setprecision to display amount correctly
	cout << "The amount currently on deposit: $" << fixed << setprecision(2) <<savingsBalance << endl;
}

void SavingsAccount::modifyInterestRate(const double &interest)
{
	// check if user entered value is negative
	if (interest < 0.0 || interest > 1.0)
		throw invalid_argument("Interest rate must be in the range of 0.0 - 1.0");
	else
		annualInterestRate = interest;
}
