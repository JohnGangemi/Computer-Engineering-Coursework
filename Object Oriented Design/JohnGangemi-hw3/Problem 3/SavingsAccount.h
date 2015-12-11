#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

class SavingsAccount
{
public:
	SavingsAccount(); // default constructor
	SavingsAccount(const double &); // overloaded constructor
	// optional default constructor with default argument:
	// SavingsAccount(const double & = 0.0);
	const void calculateMonthlyInterest(); // calculates the monthly interest
	const void printBalance(); // Access function that prints the balance

	static void modifyInterestRate(const double &); // modify the annual interest rate

private:
	static double annualInterestRate; // store the annual interest rate
	double savingsBalance; // store the balance
};

#endif