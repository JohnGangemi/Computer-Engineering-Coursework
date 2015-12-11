// Account class definitions
class Account
{
public:
	Account(int); // constructor
	void credit(int); // function that adds to the account balance
	void debit(int); // function that subtracts from the account balance
	int getBalance(); // function that gets the account balance
private:
	int accountBalance; // stores the account balance
};