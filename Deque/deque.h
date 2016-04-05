//Aaron Merrill
//CS3370

#ifndef DEQUE_H
#define DEQUE_H

#include<cstddef>
#include<algorithm>
#include<iostream>
#include<stdexcept>

template<typename T>
class Deque {
	enum { CHUNK = 10 };
	// Add your data members here…
	size_t used;
	size_t theFront;
	size_t theBack;
	T* data;
	size_t incrementForResize;
	size_t arrayLength;
public:
	Deque()		  	// Allocate default-size array
	{
		data = new T[CHUNK];
		used = 0;
		theFront = CHUNK / 2;
		theBack = CHUNK / 2;
		incrementForResize = 1;
		arrayLength = CHUNK;
	}

	~Deque()            	// Delete array memory
	{
		delete[] data;
		data = nullptr;
	}
	void push_front(T item)   	// Adds new element to the front (left end)
	{
		if (theFront == 0)	//if the front of the array gets full first, resize the deque
		{
			resizeDequeArray();
		}
		theFront = theFront - 1;
		data[theFront] = item;
		++used;
	}
	void push_back(T item)    	// Adds new element to the back (right end)
	{
		if (theBack == arrayLength)	//if the back of the array gets full first, resize the deque
		{
			resizeDequeArray();
		}
		data[theBack] = item;
		theBack = theBack + 1;
		++used;
	}
	T& front()		// Returns a reference to the first used element
	{
		if (used != 0)
		{
			return data[theFront];
		}
		else
		{
			throw std::logic_error("Error! Access to non-existant item.");
		}
	}
	T& back()		// Returns a reference to the last used element
	{
		if (used != 0)
		{
			return data[theBack - 1];
		}
		else
		{
			throw std::logic_error("Error! Access to non-existant item.");
		}
	}
	T& at(size_t pos)    	// Return the element in position pos by reference
	{
		//check out of bounds
		if (pos >= 0 && pos < used)
		{
			return *(begin() + pos);
		}
		else
		{
			throw std::logic_error("Error! Out of bounds.");
		}
	}
	void pop_front()	// "Removes" first deque element (just change _front)
	{
		if (used != 0)
		{
			++theFront;
			--used;
		}
	}
	void pop_back()	// "Removes" last deque element (just change _back)
	{
		if (used != 0)
		{
			--theBack;
			--used;
		}
	}
	size_t size() const 	// Returns the # of used items. NOTE:size_t is defined in <cstddef>
	{
		return used;
	}

	T* begin()	  	// Returns a pointer to the first element
	{
		//create a pointer
		//assign pointer to address of front
		//return pointer
		T* beginPtr = data + theFront;
		return beginPtr;
	}
	T* end()		  	// Returns a pointer to one position past the last element
	{
		//create a pointer
		//assign pointer to address of back
		//return pointer
		T* backPtr = data + theBack;
		return backPtr;
	}
	void resizeDequeArray()
	{
		arrayLength = ++incrementForResize * CHUNK; //set new array length
		size_t tempFront = (arrayLength - used) / 2;	//the index where the elements from old array will start copying to
		
		T* newData = new T[arrayLength];

		std::copy(begin(), end(), newData + tempFront);	//copy the contents of old array to temp array at specified index
		
		delete[] data;
		data = newData;
		newData = nullptr;

		theFront = tempFront;
		theBack = theFront + used;
	}
};
#endif

//
//The most difficult and challenging was the resizing of the deque. 
//I wasn't sure if I needed to delete the data member array or the newly allocated array
//that was created in the function resizeDequeArray()
//The at() function was interesting. I was a bit confused at first then reviewing that lab I realized I could use pointers
// to get the first element of deque to functionally start at zero.
