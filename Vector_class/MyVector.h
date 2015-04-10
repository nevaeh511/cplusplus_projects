//file prologue
//Aaron Merrill and Rick Puckett
//CS 1410
//Project 12
//=============================================================================
//We declare that the following code was written by us or provided by the instructor
//for this project.  We understand that copying source code from any other source constitutes
//cheating, and that we will recieve a zero on this project if we are found in violation
//of this policy.  We, Aaron Merrill and Rick Puckett, wrote this code.  We spent at least
//85% together programming.
//=============================================================================

#include <iostream>
using namespace std;

#pragma once

const int DEFAULT_CAP = 2;
class MyVector
{
private:

	int cap;
	int* dataPtr;
	int numOfElements;

public:
	// MyVector Function
	// Purpose: creates a vector and allocates memory on the heap
	// sets size of vector to zero
	// sets capacity of vector to two
	// Parameters: none
	// Returns: none
	MyVector();

	// MyVector(parameterized) Function
	// Purpose: creates a vector and allocates memory on the heap
	// with user specified capacity and size is set to zero
	// Parameters: takes an integer of vector capacity
	// Returns: none
	MyVector(int);

	// ~MyVector Function
	// Purpose: deletes the vector and sets the pointer to null
	// Parameters: none
	// Returns: none
	~MyVector();

	// MyVector copy constructor Function
	// Purpose: to copy the elements of one vector object to another
	// Parameters: takes a constant vector class by reference
	// Returns: none
	MyVector(const MyVector&);

	// size Function
	// Purpose: to know how many elements in the vector
	// Parameters: none
	// Returns: current size of the vector
	int size() const;

	// capacity Function
	// Purpose: to know how many elements the vector can hold
	// Parameters: none
	// Returns: the capcity of the vector
	int capacity() const;

	// push_back Function
	// Purpose: pushes last input down and sets in new input on top
	// Parameters: an integer value, element value
	// Returns: none
	void push_back(int);

	// at Function
	// Purpose: to find what is in a specified index position
	// Parameters: takes an integer of index value
	// Returns:  the contents at position n in the vector
	int at(int) const;

	// Clear Function
	// Purpose: deletes all of the elements from the vector
	// and resets its size to zero and its capacity to two
	// Parameters: none
	// Returns: none
	void clear();

	// assignment operator function
	// Purpose: to assign the right side to the left side
	// Parameters: takes a constant vector class by reference
	// Returns: vector class by reference
	MyVector& operator=(const MyVector& rho);

	// copy function
	// Purpose: to copy the elements of one vector object to another
	// Parameters: takes a constant vector class by reference
	// Returns: vector class by reference
	MyVector& copy(const MyVector&);

	// ostream operator function
	// Purpose: to output the elements of a vector
	// Parameters: takes a constant vector class by reference
	// Returns: output stream by reference
	friend ostream& operator<<(ostream&, const MyVector& rho);

};