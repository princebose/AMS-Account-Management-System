/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//for matlab
#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )  
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include "engine.h"
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
#include"stockNode.h"
#include"stockAccount.h"

stockaccount::stockaccount()	//constructor
{
	d = 0;						
	g = 0;
	size = 0;
	setCashBalance();
	cashBalance = getCashBalance();
	
	r1.open("Result_1.txt");
	r2.open("Result_2.txt");
	if (r1.is_open() && r2.is_open())								//store the data from textfile into STL map data structure
	{
		while (!r1.eof() && !r2.eof())
		{
			getline(r1, line);
			A << line;
			A >> symbol1 >> price1;
			result1.insert(pair<string, double>(symbol1, price1));
			A.str("");
			A.clear();

			getline(r2, line);
			A << line;
			A >> symbol1 >> price1;
			result2.insert(pair<string, double>(symbol1, price1));
			A.str("");
			A.clear();
		}
	}
	r1.close();
	r2.close();
	this->read_port();									//retrieve the portfolio if exist
	this->read_port_val();								//retrieve the portfolio value
}

stockaccount::~stockaccount()							//destructor
{

}

type stockaccount::select(type file1, type file2)		//function to select data randomly from 2 files
{
	srand(time(NULL));
	int x = rand() % 2;									// Random number between two choices

														//return based on the random number generator
	if (x == 1)
	{

		return file1;
	}
	else
	{

		return file2;
	}

}




void stockaccount::displaystock()						//function to display specific stock price
{
	int flag = 0;
	cout << "\n Enter Stock Symbol : ";
	cin >> stocksymb;
	duplicate = select(result1, result2);				//random file choosing
	for (type::iterator iter = duplicate.begin(); iter != duplicate.end(); iter++)
	{
		if (stocksymb == iter->first)					//print when symbol found
		{
			cout << " Symbol";
			cout << setw(15) << " Price/Share" << endl;
			cout << " " << iter->first;
			cout << setw(7) << iter->second << endl;
			flag = 1;
		}
	}
	if (flag == 0)
		cout << "\n Symbol not found\n";
}

bool stockaccount::isEmpty() const					//determines if list is empty
{

	 return (headptr == 0 && tailptr == 0);
	

}


stocknode * stockaccount::search(string s)			//search the symbol if exists in a linklist i.e exist in portfolio
{

	stocknode *current = headptr;
													//Going thru the linked list map
	while (current != NULL)
	{
													//Condition to check for a match
		if (current->symbol == s)
			return current;
													//Going thru the list by incrementing pointer
		current = current->next;

	}
													//returun null, if not found
	return NULL;

}

void stockaccount::buy_update(string s, int n)		//function to update linklist
{
	stocknode *temp;					
	temp = new stocknode(s, n);

	stocknode * f = search(s);						//searches if symbol there in linklist already
	if (f == NULL)									//if symbol not found
	{
		//if the list is empty
		if (tailptr == NULL&&headptr == NULL)
		{
			temp->prev = NULL;
			temp->next = NULL;
			headptr = temp;
			tailptr = temp;

		}
														//adding the new node to the end of the list if list not empty
		else
		{
			stocknode *copy = tailptr;
			tailptr->next = temp;
			tailptr = temp;
			tailptr->prev = copy;
		}
		size++;											//increasing the size of list
	}
	else												//if symbol already exists
	{
		f->nos = temp->nos + f->nos;					//increasing share nos.
	}
	sort();		//sort the list
}

void stockaccount::sell_update(stocknode *f, int n)		//update the list after selling share
{
														//Subtracting						
	f->nos = f->nos - n;

														//If subtracting results in zero shares, delete the node
	if (f->nos == 0)
	{
		if (f == headptr)
		{
			if (f == tailptr)
			{
				headptr = NULL;
				tailptr = NULL;
				delete f;
				size--;
				return;
			}
			stocknode *temp = f->next;
			headptr = f->next;
			temp->prev = NULL;
			delete f;										// delete the node.
			size--;											// reduce the size.
			return;
		}
															//if current node is tail
		else if (f == tailptr)
		{
			if (f == headptr)
			{
				headptr = NULL;
				tailptr = NULL;
				delete f;
				size--;
				return;
			}
			stocknode *temp2 = f->prev;
			tailptr = f->prev;
			temp2->next = NULL;
			delete f;													// delete the node
			size--;														// reduce the size.
			return;
		}
																		//else is the current node is middle node
		else
		{
			stocknode *temp3 = f->prev;
			stocknode *temp4 = f->next;
			temp3->next = f->next;										// prev node's next pointer becomes current node's next pointer.
			temp4->prev = f->prev;										// current node's next node prev pointer becomes current node's prev. pointer
			delete f;													// delete current node.
			size--;														// reduce the size.
			return;
		}
	}
}


void stockaccount::sort()												//sorting using bubble sort
{

	double in, nn;

	if (headptr != NULL)
	{
		int Flag = 0;

		stocknode *curr = headptr;
		stocknode *pre = 0;
		stocknode *temp = NULL;
		type T;

		for (int i = 0; i < size; i++)
		{
			while (curr->next != 0)
			{
				temp = curr->next;
				T = select(result1, result2);
				for (type::iterator iter = T.begin(); iter != T.end(); iter++)
				{
					if (curr->symbol == iter->first)
					{
						in = iter->second;
					}
					if (temp->symbol == iter->first)
					{
						nn = iter->second;
					}
				}
				
																		//Comparing, if lesser,
				if ((curr->nos)*in < (temp->nos)*nn)
				{
					temp->prev = curr->prev;
					curr->prev = temp;
					Flag = 1;
					curr->next = temp->next;
					if (curr->next != NULL)								// checking for tail pointer
						curr->next->prev = curr;
					temp->next = curr;									// after swapping temp's next pointer should be current.
					if (pre != 0)										// if previous pointer to the current is not NULL
						pre->next = temp;								// then previous's next pointer should be temp after swapping.
					pre = temp;											// and for next iteration previous should be temp.
					if (headptr == curr)								// if headptr is current, then after swapping, headptr should be temp.
						headptr = temp;
					if (curr->next == 0)								// if current's next pointer is tail then after swapping, tail should be current.
						tailptr = curr;
				}
																		//if it is not less
				else
				{
					pre = curr;
					curr = curr->next;
				}
			}
																		//If sorted
			if (Flag == 0)
				break;
			else
			{
				pre = 0;
				curr = headptr;
				Flag = 0;
			}
		}

	}

}





void stockaccount::buyingshares()										//funcion to buy shares
{
	int flag = 0;
	cout << "\nEnter Stock Symbol you want to buy : ";
	cin >> stocksymb;
	duplicate = select(result1, result2);								//random file selection
	for (type::iterator iter = duplicate.begin(); iter != duplicate.end(); iter++)
	{
		if (stocksymb == iter->first)
		{
			flag = 1;
			s_price = iter->second;											//getting stock price
	
		}
	}
	if (flag == 0)															//if symbol not found
	{
		cout << "\nSymbol not found\n";
		return;
	}
	
	cout << "\nEnter Number of shares you want to buy : ";
	cin >> NOS;
	cout << "\nEnter Maximum Amount willing to pay for per share : ";
	cin >> max_amt;

	if (max_amt >= s_price)													//check if person willing to buy is ready to give enough amt
	{
		total_amt = NOS * s_price;
		
	}
	else
	{
		cout << "\n Invalid Transaction! Can't buy stock at this price right now\n";
		return;
	}
	setCashBalance();
	cashBalance = getCashBalance();										//get recent cash bal
	if (total_amt <= cashBalance)										//checking person have enough balance to buy shares
	{
		cashBalance = cashBalance - total_amt;
		write_bal();													//write balance in text file i.e. update it
		cout << "\nYou have purchased " << NOS << " shares of " << stocksymb << " for a total of $" << total_amt << endl;
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);			//get time in dd-mm-yyyy hh:mm:ss format
		string str(buffer);
		//store transaction
		stockHistory.open("stockTransactionHistory.txt", ios::app);
		stockHistory << left << setw(8) << "Buy";
		stockHistory << left << setw(11) << stocksymb;
		stockHistory << left << setw(11) << NOS;
		stockHistory << left << setw(13) << s_price;
		stockHistory << left << setw(14) << total_amt;
		stockHistory << left << setw(19) << str << endl;
		stockHistory.close();
		
		bankTransactionHistory.open("bankTransactionHistory.txt", ios::app);
		bankTransactionHistory << left << setw(20) << "withdraw(stock)";
		bankTransactionHistory << left << setw(15) << total_amt;
		bankTransactionHistory << left << setw(25) << str;
		bankTransactionHistory << left << setw(10) << cashBalance << endl;
		bankTransactionHistory.close();										//create a new entry in the txt file


	}
	else
	{
		cout << "\n Invalid transaction, Not enough balance. \n";
		return;
	}
	buy_update(stocksymb, NOS);
	sort();
	savePortfolioValue();														//save portfolio value
}

void stockaccount::disp_portfolio()												//function to display current potfolio
{
	
	setCashBalance();
	cashBalance = getCashBalance();
	sort();
	stocknode *current = headptr;
	type B;
	double price_share,value;
	double stockval=0;
	double portfolioval;
	B = select(result1, result2);
	if (size > 0)
	{
		cout << endl << left << setw(15) << "Symbol";
		cout << left << setw(15) << "Shares";
		cout << left << setw(15) << "Price/Share($)";
		cout << left << setw(15) << "Total Value($)" << endl;
	}
	while (current != NULL)
	{
		for (type::iterator iter = B.begin(); iter != B.end(); iter++)
		{
			if (current->symbol == iter->first)									//to get price from result.txt
			{
				price_share = iter->second;
				value = current->nos*price_share;
				cout << left << setw(15) << current->symbol;
				cout << left << setw(15) << current->nos;
				cout << left << setw(15) << price_share;
				cout << left << setw(15) << value << endl;
				stockval = stockval + value;
			}
		}
		current = current->next;
	}
	
	if (size > 0)
	{
		cout << "\n Cash : " << cashBalance;
		portfolioval = cashBalance + stockval;
		cout << "\n Total portfolio value : $" << portfolioval <<endl;
	}
	else if (size == 0)												//if there are no stocks
	{
		portfolioval = cashBalance;
		cout << "\n Total portfolio value : $" << portfolioval<<endl;
		cout << "\n You don't have any shares right now!\n";
	}
}

void stockaccount::sellingshares()									//function to sell shares
{
	type C;
	int flag = 0;
	cout << "\nEnter Stock Symbol you want to sell : ";
	cin >> stocksymb;
	stocknode *tem = NULL;
	tem = search(stocksymb);									//find if symbol exists in list and store
	if (tem != NULL)
	{
		flag = 1;
	}
	if (flag == 0)
	{
		cout << "\nSymbol not found\n";
		return;
	}

	cout << "\nEnter Number of shares you want to sell : ";
	cin >> NOS;
	if (NOS > tem->nos)													//check no of shares
	{
		cout << "\n Number of shares out of range \n";
		return;
	}

	cout << "\n Enter minimum amount you want sell per share : ";
	cin >> min_amt;

	C = select(result1, result2);
	for (type::iterator iter = C.begin(); iter != C.end(); iter++)
	{
		if (stocksymb == iter->first)
		{
			s_price = iter->second;
			
		}
	}

	if (s_price < min_amt)									//check the price person want to sell share at with actual price from result.txt
	{
		cout << "\n Selling price is higher! Transaction failed\n";
		return;
	}
	setCashBalance();
	cashBalance = getCashBalance();												//read recent cash balance
	total_amt = NOS*s_price;	
	cashBalance = cashBalance + total_amt;								//update cash balance

	write_bal();		//write it in text file

	cout << "\nYou have sold " << NOS << " shares of " << stocksymb << " at rate " << s_price << " per share\n";
		//current date and time
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);					//get time in dd-mm-yyyy hh:mm:ss format
	string str(buffer);

	stockHistory.open("stockTransactionHistory.txt", ios::app);
	stockHistory << left << setw(8) << "Sell";
	stockHistory << left << setw(11) << stocksymb;
	stockHistory << left << setw(11) << NOS;
	stockHistory << left << setw(13) << s_price;
	stockHistory << left << setw(14) << total_amt;
	stockHistory << left << setw(19) << str << endl;
	stockHistory.close();

	bankTransactionHistory.open("bankTransactionHistory.txt", ios::app);
	bankTransactionHistory << left << setw(20) << "deposit(stock)";
	bankTransactionHistory << left << setw(15) << total_amt;
	bankTransactionHistory << left << setw(25) << str;
	bankTransactionHistory << left << setw(10) << cashBalance << endl;
	bankTransactionHistory.close();									//create a new entry in txt file

	sell_update(tem, NOS);		//update link list
	sort();
	savePortfolioValue();	//save portfolio value

}

void stockaccount::displayHistory()
{
	string line;
	ifstream myFile;
	cout << left << setw(8) << "Event";
	cout << left << setw(11) << "CompSymbol";
	cout << left << setw(11) << "Shares";
	cout << left << setw(13) << "Price/Share";
	cout << left << setw(14) << "Value($)";
	cout << left << setw(19) << "Date & Time" << endl;

	myFile.open("stockTransactionHistory.txt", ios::app); // open history file
															// if the file is open, read the file line by line till the end.
	if (myFile.is_open())
	{
		while (!myFile.eof())
		{
			while (getline(myFile, line))
				cout << line << "\n";
		}
	}
	myFile.close();  // close the file
}

void stockaccount::savePortfolio()
{
	sort();
	stocknode *tem5 = headptr;
	ofstream portfolioFile;
	portfolioFile.open("portfolio.txt", std::ios_base::out);
	// iterate thorugh the program and save compnay symbol and no. of shares in the text file 
	while (tem5 != NULL)
	{
		portfolioFile << tem5->symbol << "\t" << tem5->nos << "\n";
		tem5 = tem5->next;
	}
	portfolioFile.close();

	
}


void stockaccount::read_port()
{
	string s;
	int flag8 = 0;
	int n;
	string sym_temp;
	int share_temp;
	ifstream readingPortfolioFile;
	readingPortfolioFile.open("portfolio.txt", ios_base::in);
	if (readingPortfolioFile.is_open())
	{
		while (!readingPortfolioFile.eof())	//till end of line
		{
			getline(readingPortfolioFile, line1);
			B << line1;             
			B >> sym_temp >> share_temp;  
			temp.insert(pair<string, int>(sym_temp, share_temp)); // inserting it into STL map 
			B.clear();
			flag8 = 1;
		}
	}
	readingPortfolioFile.close();

	// iterating into map and creating double linked list and retrieving al values
	if (flag8 = 1)
	{
		for (type::iterator iter = temp.begin(); iter != temp.end(); ++iter)
		{

			s = iter->first;
			n = iter->second;

			buy_update(s, n);			//update link list add node and sort
		}
	}
}

void stockaccount::write_bal()	//to write cash balance
{
	ofstream writeIntoFile;
	writeIntoFile.open("CashBalance.txt", std::ios_base::out);
	writeIntoFile << endl << cashBalance;
	writeIntoFile.close();
}

void stockaccount::savePortfolioValue()		//save total potfolio value over period of time
{
	stocknode *Ptr = headptr;
	double c = 0; double tot = 0;
	double port_val=0;
	type B;
	ofstream write;
	
	B = select(result1, result2);
	//Going thru the linked list node by node
	while (Ptr != NULL)
	{
		for (type::iterator iter = B.begin(); iter != B.end(); iter++)
		{
			if (Ptr->symbol == iter->first)
			{
				c = iter->second;
				tot += Ptr->nos*c;
			}
		}

		//next node
		Ptr = Ptr->next;

	}
	setCashBalance();
	cashBalance = getCashBalance();
	port_val = tot + cashBalance;
	if (d < 100)
	{
		array1[d] = port_val;	//storing it in array for graph
	}
	//generating the current date and time 
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);
	if (g < 100)
	{
		time1[g] = str;		//storing current date and time in array
	}

	if (size == 0)
		port_val = cashBalance; // if at exit, size portfolio is empty, then store portfolio value as CashBal.
	write.open("portfolioValue.txt.", ios::app);
	write << port_val << "  " << str << endl;
	write.close();
	d++;
	g++;
}

void stockaccount::read_port_val()
{
	string line6;
	ifstream file2;
	stringstream N;
	string time2;
	//open portfolioValue text file and get the previousdata from it.save it in arrays for graph
	file2.open("portfolioValue.txt", ios_base::in);
	if (file2.is_open())
	{
		while (!file2.eof())
		{
			getline(file2, line6);
			N << line6;
			N >> array1[d] >> time1[g] >> time2; // storing porfolio values in Array1.
			if (time1[g] == "") // retrieve corresponding date and time in time1
				continue;
			else
			{
				time1[g].append(" ");
				time1[g].append(time2); // join time to it since it had space in between it got stored in temp
			}
			d++;
			g++;// increment counter for both arrays.
			N.clear();
		}
	}
	file2.close();
}

void stockaccount::view_graph()
{
	// creating a pointer to the engine
	Engine *ep;
	ep = engOpen(NULL);

	// if matlab engine is not opened show error.
	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}
	// end

	cout << "Potfolio Value" << setw(22) << "Date & Time" << endl;
	for (int i = 0; i < d; i++)
	{
		cout << array1[i] << setw(30) << time1[i] << endl;
	}

	// create mxArray and copy arrays into it
	mxArray *A;
	A = mxCreateDoubleMatrix(1, d, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)array1, d * sizeof(double));
	engPutVariable(ep, "yy", A);


	// plotting function.
	engEvalString(ep, "plot(yy);");

	//  title for graph
	engEvalString(ep, "title('Portfolio Value over Time');");
	engEvalString(ep, "xlabel('Time');");
	engEvalString(ep, "ylabel('Portfolio Value ($)');");

	mxDestroyArray(A); // destroy mxArray 

}