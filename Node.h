//file prologue
//Aaron Merrill and Rick Puckett
//CS 1410
//Lab 14
//=============================================================================
//We declare that the following code was written by us or provided by the instructor
//for this project.  We understand that copying source code from any other source constitutes
//cheating, and that we will recieve a zero on this project if we are found in violation
//of this policy.  We, Aaron Merrill and Rick Puckett, wrote this code.  We spent at least
//85% together programming.  
//=============================================================================

#include <string>
#include <iostream>
using namespace std;

#pragma once
class Node
{
private:
	Node* next;
	string itemName;
	string itemType;
	int numItems;
public:
	// Node Function (default constructor)
	// Purpose: to initialize data members to default values
	// Parameters: none
	// Returns: none
	Node();

	// Node Function (parameterized constructor)
	// Purpose: to initialize data members
	// Parameters: takes two strings and an integer
	// Returns: none
	Node(int, string, string);

	// getNextNode Function
	// Purpose: gets the next nodes pointer
	// Parameters: none
	// Returns: a node pointer
	Node* getNextNode() const;

	// setNextNode Function
	// Purpose: sets the node pointer to the next node in list
	// Parameters: takes a node pointer
	// Returns: none
	void setNextNode(Node*);

	// getItem Function
	// Purpose: gets the items name
	// Parameters: none
	// Returns: a string value
	string getItemName() const;

	// getAmountName Function
	// Purpose: gets the item type
	// Parameters: none
	// Returns: a string value
	string getItemType() const;

	// getAmount Function
	// Purpose: gets the quantity of items in list
	// Parameters: none
	// Returns: an integer value
	int getNumItems() const;
};

class List
{
private:
	int count;
	Node* first;
	Node* last;
public:
	// List Function (default constructor)
	// Purpose: initialize data members to default values
	// Parameters: none
	// Returns: none
	List();

	// getCount Function
	// Purpose: gets the total number of nodes in the list
	// Parameters: none
	// Returns: an integer
	int getCount() const;

	// getFirst Function
	// Purpose: gets the node pointer from front of list
	// Parameters: none
	// Returns: a node pointer
	Node* getFirst() const;

	// getLast Function
	// Purpose: gets the node pointer from end of list
	// Parameters: none
	// Returns: a node pointer
	Node* getLast() const;

	// push_front Function
	// Purpose: to insert a node pointer into front of list
	// Parameters: takes a node pointer
	// Returns: none
	void push_front(Node*);

	// pop_front Function
	// Purpose: to remove a node pointer from front of list
	// Parameters: none
	// Returns: a node pointer
	Node* pop_front();

	// push_back Function
	// Purpose: to insert a node pointer into end of list
	// Parameters: takes a node pointer
	// Returns: none
	void push_back(Node*);

	// pop_back Function
	// Purpose: to remove a node from end of list
	// Parameters: none
	// Returns: a Node pointer
	Node* pop_back();
};
