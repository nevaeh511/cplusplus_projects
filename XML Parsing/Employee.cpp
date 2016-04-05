//Aaron Merrill
//CS 3370
#include"Employee.h"
using namespace std;

Employee::Employee(string name, int empid, string address, string city, string state, string country,
	string phone, double empsalary):name(name), address(address), city(city), state(state),
	country(country), phone(phone), id(empid), salary(empsalary) { }
void Employee::display(std::ostream& os) const  // Write a readable Employee representation to a stream
{
	os << "\nid: " << id << "\n" << "Name: " << name << "\n" << "Address: " << address << "\n" << "City: " << city
		<< "\n" << "Country: " << country << "\n" << "Phone: " << phone << "\n" << "Salary: " << salary << "\n" << endl;
}
void Employee::write(std::ostream& os) const // Write a fixed-length record to current file position
{
	EmployeeRec record;
	record.id = id;
	strncpy(record.name, name.c_str(), 31) [31] = '\0';
	strncpy(record.address, address.c_str(), 26)[26] = '\0';
	strncpy(record.city, city.c_str(), 21) [21] = '\0';
	strncpy(record.state, state.c_str(), 21)[21] = '\0';
	strncpy(record.country, country.c_str(), 21)[21] = '\0';
	strncpy(record.phone, phone.c_str(), 21) [21] = '\0';
	record.salary = salary;
	os.write(reinterpret_cast<const char*>(&record), sizeof record);
}
void Employee::store(std::iostream& ios) const   // Overwrite (or append) record in (to) file
{
	ios.seekg(0, ios::beg);
	ios.clear();
	unique_ptr<Employee> found = retrieve(ios, this->id);
	ios.clear();
	if (found == nullptr) //record was found. overwrite the record
	{
		ios.app;
	}
	write(ios);
}
void Employee::setSalary(double sal)
{
	salary = sal;
}
double Employee::getSalary()
{
	return salary;
}
void Employee::toXML(std::ostream& os) const   // Write XML record for Employee
{
	os << "<employee>" << endl;
	os << "\t<id>" << id << "<id>" << endl;
	os << "\t<name>" << name << "<name>" << endl;
	os << "\t<address>" << address << "<address>" << endl;
	os << "\t<city>" << city << "<city>" << endl;
	os << "\t<state>" << state << "<state>" << endl;
	os << "\t<country>" << country << "<country>" << endl;
	os << "\t<phone>" << phone << "<phone>" << endl;
	os << "\t<salary>" << salary << "</salary>" << endl;
	os << "</employee>" << endl;
}
unique_ptr<Employee> Employee::read(std::istream& is)         // Read record from current file position
{
	EmployeeRec recordFromFile;
	unique_ptr<Employee> employee(new Employee());
	is.read(reinterpret_cast<char*>(&recordFromFile), sizeof recordFromFile);
	
	if (is)
	{
		employee->id = recordFromFile.id;
		employee->name = recordFromFile.name;
		employee->address = recordFromFile.address;
		employee->city = recordFromFile.city;
		employee->state = recordFromFile.state;
		employee->country = recordFromFile.country;
		employee->phone = recordFromFile.phone;
		employee->salary = recordFromFile.salary;
		return employee;
	}
	return nullptr;
}
unique_ptr<Employee> Employee::retrieve(std::istream& is, int value) // Search file for record by id
{
	unique_ptr<Employee> recordFound;
	is.seekg(0, ios::beg);
	is.clear();
	while (is)
	{
		auto recordPos = is.tellg();
		recordFound = read(is);
		if (recordFound == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (recordFound->id == value)
			{
				is.seekg(recordPos);
				return recordFound;
			}
		}
	}
	return nullptr;
}
unique_ptr<Employee> Employee::fromXML(std::istream& is)		// Read the XML record from a stream
{
	enum {employ, empid, nam, addr, cty, sta, ctry, phn, sal};
	const int TAG_COUNT = 9;
	bitset<TAG_COUNT> trackTags;
	string startToken, endToken, token, value;
	startToken = getNextTag(is);						//this should grab the start employee tag
	unique_ptr <Employee> employee (new Employee());
	if (startToken == "employee")
	{
		do
		{
			token = getNextTag(is);
			trackTags[employ].flip();
			if (token != "employee")
			{
				value = getNextValue(is);
				endToken = getNextEndTag(is);
				if (token.compare(endToken) != 0)
				{
					throwTokenErrors(token, endToken);
				}
			}
			if (token == "id")	//checks what was read in from file matches of with a valid tag name
			{
				if (trackTags[empid] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[empid].flip();
				employee->id = stoi(value);
			}
			else if (token == "name")
			{
				if (trackTags[nam] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[nam].flip();
				employee->name = value;
			}
			else if (token == "address")
			{
				if (trackTags[addr] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[addr].flip();
				employee->address = value;
			}
			else if (token == "city")
			{
				if (trackTags[cty] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[cty].flip();
				employee->city = value;
			}
			else if (token == "state")
			{
				if (trackTags[sta] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[sta].flip();
				employee->state = value;
			}
			else if (token == "country")
			{
				if (trackTags[ctry] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[ctry].flip();
				employee->country = value;
			}
			else if (token == "phone")
			{
				if (trackTags[phn] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[phn].flip();
				employee->phone = value;
			}
			else if (token == "salary")
			{
				if (trackTags[sal] == 1){ throw runtime_error("Invalid <" + (token + ">")); }
				trackTags[sal].flip();
				employee->salary = stod(value);
			}
			else if (token == "employee")
			{
				if (trackTags[employ] == 1){ throw runtime_error("Missing </" + (token + ">")); }
				break;
			}
			else
			{
				throw runtime_error("Error occured!: <" + (token + ">"));
			}
			
		} while (token != "employee");

		if (token == "/employee")
		{

		}

		if (trackTags[empid] == 0 || trackTags[nam] == 0)	//checks if the name or id are missing
		{
			if (trackTags[empid] == 0)
			{
				throw runtime_error("Missing id!");
			}
			else
			{
				throw runtime_error("Missing name!");
			}
		}
		return employee;
	}
	else if (!is || employee->id == -1)
	{
		return nullptr;
	}
	else
	{
		throw runtime_error("Missing <employee>");
	}
}
string Employee::getNextTag(std::istream& is)
{
	string token;
	is.ignore(numeric_limits<streamsize>::max(), '<');
	if (is.peek() == '/')
	{
		is.ignore(1);
		getline(is, token, '>');
	}
	else if (is.peek() != '/')
	{
		getline(is, token, '>');
	}
	std::transform(token.begin(), token.end(), token.begin(), ::tolower);
	return token;
}
string Employee::getNextValue(std::istream& is)
{
	string value, novalue;
	getline(is, value, '<');
	if (is.peek() == '/')
	{
		return value;
	}
	return novalue;
}
bool Employee::isAllWhitespace(const string& str)
{
	for (auto i : str)
	{
		if (!isspace(i))
		{
			return false;
		}
	}
	return true;
}
string Employee::getNextEndTag(std::istream& is)
{
	string endToken;
	if (is.peek() == '/')
	{
		is.ignore(1);
		getline(is, endToken, '>');
		std::transform(endToken.begin(), endToken.end(), endToken.begin(), ::tolower);
	}
	return endToken;
}
void Employee::throwTokenErrors(const string& tag1, const string& tag2)
{
	vector<string> tagNames = { "id", "name", "address", "city", "state", "country", "phone", "salary" };
	string token = tag1;
	string endToken = tag2;
	string missingEndToken = "Missing <" + (endToken + ">");
	string missingStartToken = "Missing </" + (token + ">");
	for (size_t i = 0; i < tagNames.size(); ++i)
	{
		if (token.compare(tagNames[i]) == 0)
		{
			throw runtime_error(missingEndToken);
		}
		else
		{
			throw runtime_error(missingStartToken);
		}
	}
	
}

