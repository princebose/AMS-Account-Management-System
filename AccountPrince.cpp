/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "Account.h"

double account::getCashBalance()					//returns current cashBalance value
{
	return cashBalance;		
}

void account::setCashBalance()						//if called for the first time, sets value to $10000; otherwise, reads from CashBalance.txt file and updates cahBalance
{
	int flag=0;										//flag to check if this is the first call		
	ifstream cashFile;
	cashFile.open("CashBalance.txt",ios_base::in);	//open cashbalance text file
	if (cashFile.is_open())							//check if any previous entry of cash balance is der or not
	{
		while (!cashFile.eof())						//traverse to the end of file
		{
			char ch = (char)cashFile.get();			//extract each character
			flag++;									//if data available in text file, that means this is not the first call
			break;
		}
	}
	cashFile.close();

	if (flag==0)									// if previous cash entry not found, create the file and put 10,000 cash balance into it.
	{
		double initBalance = 10000.00;				//starting balance for an account is $10000

		ofstream cashFile;
		cashFile.open("CashBalance.txt", ios_base::out);	// open the file in WRITE mode
		cashFile << initBalance;					// write value to file
		cashFile.close();							//close the file


													// read balance of $10000 from file
		ifstream updateCashBal("CashBalance.txt", ios_base::in);
		updateCashBal >> cashBalance;				//update current cash balance in CashBalance 
		updateCashBal.close();						//close file
	}
	else
	{
													//  set balance from existing cash balance file if previous cash entry found.
		ifstream readCashBal("CashBalance.txt", ios_base::in);
		readCashBal >> cashBalance;					//update current cash balance 
		readCashBal.close();						//close file
	}
}


