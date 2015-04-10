#include"PriorityQueue.h"


PriorityQueue::PriorityQueue()
{
	Pairs mypairs;
	mypairs.name = "";
	mypairs.priority = -1;
	vector<Pairs> pair;
}

void PriorityQueue::push(string name, int num)
{
	Pairs pairs;
	pairs.name = name;
	pairs.priority = num;
	pair.push_back(pairs);
	if (pair.size() > 1)
	{
		sortQueue();
	}
}
void PriorityQueue::sortQueue()
{
	Pairs firstPair;
	Pairs nextPair;
	int indexOfLargest;
	int largest;
	for (int i = pair.size() - 1; i > 0; --i)
	{
		indexOfLargest = 0;
		firstPair = pair.front();
		largest = firstPair.priority;
		for (int j = 1; j <= i; ++j)
		{
			Pairs nextPair = pair[j];
			if (nextPair.priority > largest)
			{
				largest = nextPair.priority;
				indexOfLargest = j;
			}
			iter_swap(pair.begin() + j, pair.begin() + indexOfLargest);
		}
	}
}

int PriorityQueue::size()
{
	int size = pair.size();
	return size;
}
string PriorityQueue::top()
{
	Pairs mypairs = pair.front();
	return mypairs.name;
}
void PriorityQueue::pop()
{
	pair.erase(pair.begin());
}

