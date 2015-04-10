#include "Node.h"
#include <string>
using namespace std;

Node::Node()
{
	next = nullptr;
	itemName = "none";
	itemType = "none";
	numItems = 0;
}

Node::Node(int _num, string _type, string _item)
{
	numItems = _num;
	itemType = _type;
	itemName = _item;
}

Node* Node::getNextNode() const
{
	return next;
}

void Node::setNextNode(Node* _node)
{
	this->next = _node;
}

string Node::getItemName() const
{
	return itemName;
}

string Node::getItemType() const
{
	return itemType;
}

int Node::getNumItems() const
{
	return numItems;
}

//=====================================================================
//List class

List::List()
{
	count = 0;
	last = nullptr;
	first = nullptr;
}

int List::getCount() const
{
	return count;
}

Node* List::getFirst() const
{
	return first;
}

Node* List::getLast() const
{
	return last;
}

void List::push_front(Node* f)
{
	if (first == nullptr)
	{
		first = f;
		last = f;
		count++;

	}
	else
	{
		Node* temp = first;
		first = f;
		f->setNextNode(temp);
		count++;
	}

}

Node* List::pop_front()
{
	if (first == nullptr)
	{
		return first;
	}
	else if (first == last)
	{
		Node* temp = first;
		first = nullptr;
		last = nullptr;
		count--;
		return temp;
	}
	else
	{
		Node* temp = first;
		first = first->getNextNode();
		count--;
		return temp;
	}
}

void List::push_back(Node* b)
{
	if (first == nullptr)
	{
		first = b;
		last = b;
		last->setNextNode(nullptr);
	}
	else
	{
		Node* temp = last;
		temp->setNextNode(b);
		last = b;
		last->setNextNode(nullptr);
	}
	count++;
}

Node* List::pop_back()
{
	if (first == last)
	{
		Node* temp = first;
		first = nullptr;
		last = nullptr;
		count--;
		return temp;
	}
	else
	{
		Node* current = first;
		for (int i = 0; i < count - 1; i++)
		{
			current = current->getNextNode();
			if (current->getNextNode() == last)
			{
				Node* temp = last;
				last = current;
				last->setNextNode(nullptr);
				count--;
				return temp;
			}
		}
	}
}


