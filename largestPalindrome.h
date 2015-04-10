#include<string>
#include<iostream>
#include<fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class LargestPalindrome
{
private:
	string largestPalindrome;
	int sizeOfPalindrome;
	//string fileText;
	string text;
	string userInput;
	std::fstream file;
public:
	void userFileInput();
	void readFile();
	void findLargestPalindrome();
	void display();
	bool isPalindrome(const string& subStr);
	string getSubstr(int i, int j);
};

void LargestPalindrome::display()
{
	if (sizeOfPalindrome == 0 || sizeOfPalindrome == 1)
	{
		cout << "There was no winner." << endl;
	}
	else
	{
		cout << "At a length of: " << sizeOfPalindrome << endl;
		cout << "The one palindrome that rules them all is: " << largestPalindrome << endl;
	}
}
void LargestPalindrome::userFileInput()
{
	do
	{
		cout << "Please type a text filename: ";
		cin >> userInput;
		file.open(userInput);
		if (!file)
		{
			std::cerr << "Sorry, the file could not open or does not exit!";
		}
	} while (!file);
}
void LargestPalindrome::readFile()
{
	while (file)
	{ 
		//read in file contents as one string
		//save to text variable
		file >> text;
	}
}
//racecar
void LargestPalindrome::findLargestPalindrome()
{
	//string foundMatch;
	//start at the first character in the text and increment by one
	for (size_t i = 0; i < text.size() - 1; ++i)
	{
		string foundMatch;
		char beginChar = text[i];
		//this starts at the last character in the text and decremets by one
		for (int j = text.size() - 1; j > 0; --j)
		{
			char endChar = text[j];
			//if the first and last characters match
			if (beginChar == endChar)
			{
				//get the substring starting and ending at the matching characters
				foundMatch = getSubstr(i, j);
				//send the substring to function to further the search of matching characters
				//if this comes back true
				if (isPalindrome(foundMatch))
				{
					//complare the sizes of current palindrome with previous found palindrome
					if (foundMatch.size() > largestPalindrome.size())
					{
						//if the current found palindrome is larger than previous one, set current as the largest palindrome
						largestPalindrome = foundMatch;
						sizeOfPalindrome = largestPalindrome.size();
					}
				}
			}
		}
	}
}
bool LargestPalindrome::isPalindrome(const string& subStr)
{
	bool foundPalindrome = true;
	int first = 0;
	int last = subStr.size() - 1;
	while(first < last)
	{
		if (subStr[first] != subStr[last])
		{
			return foundPalindrome = false;
		}
		++first;
		--last;
	}
	return foundPalindrome;
}
string LargestPalindrome::getSubstr(int i, int j)
{
	string substr = "";
	int l = 0;
	int start = i;
	int end = j;
	while (start <= end)
	{
		substr = substr + text[start];
		++start;
		++l;
	}
	return substr;
}