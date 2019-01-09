/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <time.h>

#include "Account.h"

using namespace std;

class bankAccount :public account
{
public:
	bankAccount();						//bankAccount constructor
	~bankAccount();						//bankAccount destructor	
	void showBalance();					//this function displays the balance
	void depositMoney();				//this function helps user to deposit money into account
	void withdrawMoney();				//this function helps user to withdraw money into account
	virtual void displayHistory();		//this function helps user to see all past transactions
	void storeBalance();				//this function updates balance in the CashBalance file
private:
	double depositCash;					//stores deposited money value
	double withdrawCash;				//stores withdrawn cash value
	ofstream bankTransactionHistory;	//file pointer to update transaction history
	ifstream read;						//file pointer to read file

};

#endif

