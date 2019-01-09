/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#include "Account.h"
#include "bankAccount.h"

bankAccount::bankAccount()					// defining constructor
{	
	setCashBalance();						// update CashBalance or create CashBalance = 10000
	cashBalance = getCashBalance();			// read latest CashBalance
	depositCash = 0;						//init variable
	withdrawCash = 0;						//init variable
}

bankAccount::~bankAccount()					//destructor
{

}

void bankAccount::storeBalance()		
{
	ofstream writeIntoFile;
	writeIntoFile.open("CashBalance.txt", std::ios_base::out);	//update CashBalance.txt
	writeIntoFile << endl << cashBalance;
	writeIntoFile.close();
}

void bankAccount::showBalance()				
{
	setCashBalance();
	cashBalance = getCashBalance();			//get recent cash balance
	cout << "\n Current Account Balance: $" << cashBalance << ".\n";	//display message and balance
}

void bankAccount::depositMoney()		
{
	cout << "\n Amount you want to deposit : $";
	cin >> depositCash;
	setCashBalance();
	cashBalance = getCashBalance();
	cashBalance = cashBalance + depositCash;	//add deposited cash to current cash value
	storeBalance();								//update cash balance
	cout << "\n Amount $" << depositCash << " is deposited to your account\n";
	
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);	//get time in dd-mm-yyyy hh:mm:ss format
	std::string str(buffer);
	
	bankTransactionHistory.open("bankTransactionHistory.txt", ios::app); //creating an entry in transaction history
	bankTransactionHistory << left << setw(20) << " DEPOSIT ";
	bankTransactionHistory << left << setw(15) << depositCash;
	bankTransactionHistory << left << setw(25) << str;
	bankTransactionHistory << left << setw(5) <<  cashBalance << endl;
	bankTransactionHistory.close();

}

void bankAccount::withdrawMoney()	
{
	cout << "\n Amount you want to withdraw : $";
	cin >> withdrawCash;
	setCashBalance();
	cashBalance = getCashBalance();
	if (cashBalance > 0)								//check for sufficient funds
	{
		if (withdrawCash <= cashBalance)				//if amount requested is lesser than funds
		{

			cashBalance = cashBalance - withdrawCash;	//update cash balance
			storeBalance();								//store cash balance
			cout << "\n Amount $" << withdrawCash << " is withdrawn from your account\n";
														
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);	//get time in dd-mm-yyyy hh:mm:ss format
			std::string str(buffer);
	
			bankTransactionHistory.open("bankTransactionHistory.txt", ios::app);	//creating an entry in transaction history
			bankTransactionHistory << left << setw(20) << " WITHDRAW ";
			bankTransactionHistory << left << setw(15) << withdrawCash;
			bankTransactionHistory << left << setw(25) << str;
			bankTransactionHistory << left << setw(10) << cashBalance << endl;
			bankTransactionHistory.close();
		}
		else
		{
			cout << "\n Error! Balance insufficient!\n";			//withdrawn request exceeds the funds
			return;
		}
	}
	else
	{
		cout << "\n Balance is zero\n";								//if Account Balance is zero
	}
}

void bankAccount::displayHistory()	
{
	string line;
	read.open("bankTransactionHistory.txt", ios::app);
	cout << left << setw(20) <<" Event ";
	cout << left << setw(15) << "Amount $";
	cout << left << setw(25) << "Date & Time";
	cout << left << setw(10) << "Balance $" << endl;
	if (read.is_open())
	{
		while (!read.eof())					//traverse till end of the file print all lines
		{
			while (getline(read, line))
				cout << line << "\n";		//print file line by line 
		}
	}
	read.close();
}