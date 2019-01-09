/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include "Account.h"
#include "bankAccount.h"
#include "stockAccount.h"
#include "stockNode.h"

using namespace std;

int main()
{
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	bankAccount B;															//calling bankAccount object
	stockaccount A;															//calling stockAccount object
	stocknode *node = NULL;													//creating stocknode pointer

	cout << " Welcome to the Account Management System! \n";				//Welcome Message

	while (choice1 != 3)													// 3 is EXIT
	{
		cout << "\n1. Stock Portfolio Account"
			<< "\n2. Bank Account"
			<< "\n3. Exit";
		cout << "\nPlease Select Account to Access : ";						//Request choice1
		cin >> choice1;

		switch (choice1)
		{
		case 1:
			while (choice2 != 7)											// Go to Stock options
			{
				cout << "\n        Stock Portfolio account";
				cout << "\n1. Display the price for a Stock Symbol"
					<< "\n2. Display Current Portfolio"
					<< "\n3. Buy Shares"
					<< "\n4. Sell Shares"
					<< "\n5. View a Graph for the Portfolio Value"
					<< "\n6. View Transaction History"
					<< "\n7. Return to the Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> choice2;
				switch (choice2)											//call related function
				{
				case 1:
					A.displaystock();
					break;
				case 2:
					A.disp_portfolio();
					break;
				case 3:
					A.buyingshares();
					break;
				case 4:
					A.sellingshares();
					break;
				case 5:
					A.view_graph();
					break;
				case 6:
					A.displayHistory();
					break;
				
				case 7:
					break;
				default:
					cout << "\nEnter Valid Option!";
				}
			}
			choice2 = 0;
			break;
		case 2:
			
			while (choice3 != 5)											// Go to Bank Options
			{
				cout << "\n        Bank Account";
				cout << "\n1. View Account Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. Return to Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> choice3;
				switch (choice3)											//call related function
				{
				case 1:
					B.showBalance();
					break;
				case 2:
					B.depositMoney();										
					A.savePortfolioValue();
					break;
				case 3:
					B.withdrawMoney();
					A.savePortfolioValue();
					break;
				case 4:
					B.displayHistory();
					break;
				case 5:
					break;
				default:
					cout << "\nEnter Valid Option!";
				}
			}
			choice3 = 0;
			break;

		case 3:
			A.savePortfolio();															// saving portfolio before exiting			 
			break;
		default:
			cout << "\nEnter Valid Option!";
		}
	}
}