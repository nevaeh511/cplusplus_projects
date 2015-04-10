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

#include "MyVector.h"
#include <iostream>
using namespace std;

MyVector::MyVector()
{
	// if default constructor is called
	// Create a vector with default capacity two
	// and size of zero
	cap = DEFAULT_CAP;
	dataPtr = new int[cap];
	numOfElements = 0;
}

MyVector::MyVector(int _cap)
{
	// if Parameterized constructor is called
	// Create a vector with user specified capacity
	// and size of zero
	cap = _cap;
	dataPtr = new int[cap];
	numOfElements = 0;
}

MyVector::~MyVector()
{
	// when the destructor is executed
	// Delete the vector that was created in constructor
	// and set the vector pointer to null
	delete[] dataPtr;
	dataPtr = nullptr;
}

MyVector::MyVector(const MyVector& rho)
{
	//calls the copy function
	copy(rho);
}

MyVector& MyVector::copy(const MyVector& rho)
{
	//	Create new vector with capacity of right side vectors capacity
	int* tempDataPtr = new int[rho.capacity()];
	//	Loop through right side vector
	for (int i = 0; i < rho.numOfElements; i++)
	{
		//Copy right side vector contents to left side vector
		tempDataPtr[i] = rho.dataPtr[i];
	}
	dataPtr = tempDataPtr;
	//Assign right side vectors size to left side vectors size
	numOfElements = rho.numOfElements;
	//Assign right side vectors capacity to left side vectors capacity
	cap = rho.cap;
	return *this;
}

int MyVector::size() const
{
	// if size function is called
	// return the number of elements in vector
	return numOfElements;
}

int MyVector::capacity() const
{
	// if capacity function is called
	// return the capacity of vector
	return cap;
}

void MyVector::push_back(int n)
{
	// if push_back function is called
	// check to see if number of elements are equal to the capacity
	if (numOfElements == cap)
	{
		// if true, then double the capacity
		// create a new vector with doubled capacity
		cap = cap * DEFAULT_CAP;
		int* tempPtr = new int[cap];
		// go through the vector and copy elements of old vector
		// to new vector
		for (int i = 0; i < numOfElements; i++)
		{
			tempPtr[i] = dataPtr[i];
		}
		// delete old vector to remove from the heap
		delete[] dataPtr;
		// now assign the new vector back to the old vector
		dataPtr = tempPtr;

	}
	// push the specified integer into the vector
	dataPtr[numOfElements] = n;
	// increment the size of vector after a number is inserted into vector
	numOfElements++;
}

int MyVector::at(int _index) const
{
	// if the at function is called
	// check to see if the specified index is greater or equal to the size of vector
	if (_index >= numOfElements)
	{
		// if true, then throw an exception and return the index
		throw _index;
	}
	else
	{
		// if index is less than the size, return the contents in specified index
		return *(dataPtr + _index);
	}

}

void MyVector::clear()
{
	// if clear function is called
	//delete the vector
	delete[] dataPtr;
	// reset the capacity back to default(two)
	cap = DEFAULT_CAP;
	// create a new vector with default capacity
	dataPtr = new int[cap];
	// reset the size back to zero
	numOfElements = 0;
}

MyVector& MyVector::operator=(const MyVector& rho)
{
	//If vectors are equal
	if (this == &rho)
	{
		//Then return the vector
		return *this;
	}
	//If vectors are not equal
	else
	{
		//Delete left side vectors pointer
		delete[] dataPtr;
		//set pointer to null
		dataPtr = nullptr;
		//Create new vector with capacity of right side vectors capacity
		//Loop through right side vector
		//Copy right side vector contents to left side vector
		return copy(rho);
	}
}

ostream& operator<<(ostream& out, const MyVector& rho)
{
	for (int i = 0; i < rho.numOfElements; i++)
	{
			out << rho.dataPtr[i] << ", ";
	}
	return out;
}
