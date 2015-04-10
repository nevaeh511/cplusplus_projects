#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
using std::string;
using std::vector;

class PriorityQueue
{
private:
	struct Pairs
	{
		string name;
		int priority;
	};
	vector<Pairs> pair;
	void sortQueue();
public:
	PriorityQueue();
	void push(string name, int number = -1);
	int size();
	string top();
	void pop();
	void print();
};
#endif

