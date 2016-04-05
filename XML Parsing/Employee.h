//Aaron Merrill
#ifndef UNIQUE_EMPLOYEE_H
#define UNIQUE_EMPLOYEE_H
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<stdio.h>
#include<bitset>
#include<iomanip>
#include<limits>
#include<memory>
using std::string;
using std::unique_ptr;

class Employee
{
private:
	string name;
	int id;
	string address;
	string city;
	string state;
	string country;
	string phone;
	double salary;
	struct EmployeeRec {
		int id;
		char name[31];
		char address[26];
		char city[21];
		char state[21];
		char country[21];
		char phone[21];
		double salary;
	};
	Employee()
	{
		string name = "";
		int id = -1;
		string address = "";
		string city = "";
		string state = "";
		string country = "";
		string phone = "";
		double salary = 0.0;
	}
public:
	Employee(string name, int id, string address, string city, string state, string country,
		string phone, double salary = 0.0);
	void display(std::ostream& os) const;  // Write a readable Employee representation to a stream
	void write(std::ostream& os) const;    // Write a fixed-length record to current file position
	void store(std::iostream& os) const;   // Overwrite (or append) record in (to) file
	void toXML(std::ostream& os) const;    // Write XML record for Employee
	void setSalary(double sal);
	double getSalary();

	static unique_ptr<Employee> read(std::istream& is);         // Read record from current file position
	static unique_ptr<Employee> retrieve(std::istream& is, int id); // Search file for record by id
	static unique_ptr<Employee> fromXML(std::istream& is);     // Read the XML record from a stream

	static string getNextTag(std::istream& is);
	static string getNextValue(std::istream& is);
	static void throwTokenErrors(const string& tag1, const string& tag2);
	static bool isAllWhitespace(const string& str);
	static string getNextEndTag(std::istream& is);

};
#endif

