//Aaron Merrill

#ifndef MYOBJECT_H
#define MYOBJECT_H

#include"Pool.h"
#include <string>
using std::string;


class MyObject
{
private:
	int id;
	string name;
	static Pool<MyObject> pool;

	MyObject(int i, const string& nm) : name(nm) {
		id = i;
	}
	void* operator new(size_t size)
	{
		return pool.allocate();                                                                               
	}
public:
	static MyObject* create(int id, const string& name) {	// Factory method
		return new MyObject(id, name);
	}

	void operator delete(void* object)
	{
		pool.deallocate(object);
	}

	void* operator new[](size_t size) = delete;
	void operator delete[](void* p) = delete;

	MyObject(const MyObject& obj) = delete;
	MyObject& operator=(const MyObject& obj) = delete;
	
	friend std::ostream& operator<<(std::ostream& os, const MyObject& o);
};
#endif
