/*
Account Management System
Name: Prince Bose
RUID: 186008149
NETID: pkb44
*/
#ifndef STOCK_NODE_H
#define STOCK_NODE_H

#include <iostream>
#include <string>
#include "Account.h"
using namespace std;
/*
This class creates define the nodes that we use in the Map. 1 node consists of a SYMBOL, a related VALUE, and 2 pointers (PREV, NEXT). 
Design Pattern is a Doubly Linked List.
*/
class stocknode
{
	friend class stockaccount;

public:
	stocknode(string& s, int n) :symbol(s), nos(n)
	{
		this->next = NULL;
		this->prev = NULL;
	}

private:
	stocknode *next;
	stocknode *prev;
	string symbol;
	int nos;


};
#endif

