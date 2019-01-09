/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H

class account
{
public:
	virtual void displayHistory() = 0;  //this function displays the history of all transactions/ portfolio value	
	double getCashBalance();   //this function returns current cash balance
	void setCashBalance();		//this function sets the current cash balance

protected:
	double cashBalance;		//stores the value of cash and can be accessed from both stock and bank account

};



#endif
