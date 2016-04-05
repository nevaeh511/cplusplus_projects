//Aaron Merrill
#ifndef POOL_H
#define POOL_H

#include<cstddef>


template<typename T>
class Pool
{
private:
	char* freeHead = nullptr;
	char** poolList = nullptr;
	size_t poolSize;
	size_t blockSize;
	size_t elementSize;
	
public:
	Pool(size_t elemSize, size_t blockSize = 5);
	Pool(const Pool& obj) = delete;
	Pool& operator=(const Pool& obj) = delete;
	~Pool();
	void* allocate();       // Get a pointer inside a pre-allocated block for a new object
	void deallocate(void* T); // Free an object's slot (push the address on the "free list")
	void growPool();
	void linkTheBlock();
	void poke(void* t, char* p);
};
#endif

//_______________________________________
//DEFINITIONS
#include<iostream>
#include<cassert>
using std::cout;
using std::endl;

template<typename T>
Pool<T>::Pool(size_t elemSize, size_t blkSize)
{
	poolSize = 0;
	blockSize = blkSize;
	elementSize = elemSize;
	cout << "Initializing a pool with element size " << elementSize << " and block size " << blockSize << endl;
	assert(elementSize > 0);
	assert(blockSize > 0);
}

template<typename T>
Pool<T>::~Pool()
{
	cout << "Deleting " << static_cast<int>(poolSize) << "blocks" << endl;
	for (size_t i = 0; i < poolSize; i++)
	{
		delete poolList[i];
	}
	delete[] poolList;
}
template<typename T>
void* Pool<T>::allocate()	// Get a pointer inside a pre-allocated block for a new object
{
	//if first allocation or a block of memory is full, 
	if (freeHead == nullptr)
	{
		growPool();
	}
	assert(freeHead != nullptr);
	char* tempFreeHead = freeHead;
	freeHead = *reinterpret_cast<char**>(freeHead);
	cout << "Cell allocated at 0x" << static_cast<void*>(tempFreeHead) << endl;
	return tempFreeHead;
}
template<typename T>
void Pool<T>::deallocate(void* obj) // Free an object's slot (push the address on the "free list")
{
	poke(obj, freeHead);
	freeHead = reinterpret_cast<char*>(obj);
	cout << "Cell deallocated at 0x" << static_cast<void*>(freeHead) << endl;
	assert(freeHead != nullptr);
}

template<typename T>
void Pool<T>::linkTheBlock()
{
	char* aBlockOfMem = new char[elementSize * blockSize];
	poolList[poolSize - 1] = aBlockOfMem;
	freeHead = aBlockOfMem;
	cout << "Linking cells starting at 0x" << static_cast<void*>(freeHead) << endl;
	char* nextPos = aBlockOfMem;
	char* tempPos = nullptr;
	for (size_t i = 0; i < blockSize; i++)
	{
		tempPos = nextPos;
		nextPos += elementSize;
		if (i == (blockSize - 1))
		{
			nextPos = nullptr;
		}
		poke(tempPos, nextPos);
	}
}

template<typename T>
void Pool<T>::growPool()
{
	cout << "Expanding Pool....." << endl;
	++poolSize;
	//if there is a previous full block of memory, copy full array to larger temp array
	char** largerPool = new char*[poolSize];
	if (poolSize > 1)
	{
		for (size_t i = 0; i < poolSize - 1; ++i)
		{
			largerPool[i] = poolList[i];
		}
	}
	poolList = largerPool;
	largerPool = nullptr;

	linkTheBlock();
}

template<typename T>
void Pool<T>::poke(void* t, char* p)
{
	new (t)char*(p);   // "Placement new"
}