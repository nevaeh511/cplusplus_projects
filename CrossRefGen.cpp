#include<regex>
#include<vector>
#include<functional>
#include<iterator>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<map>
#include<iomanip>
#include<string>
using namespace std;

struct Compare
{
	bool operator()(const string& first, const string& second) const
	{
		int compVal1 = _stricmp(first.c_str(), second.c_str());
		if (compVal1 == 0){
			return first < second;
		}
		else if (compVal1 < 0){
			return true;
		}
		else{
			return false;
		}
	}
};

class CrossRefGen
{
private:
	map <string, map <int, int>, Compare> keyWords;
	int width;
	const int LINE_LIMIT = 9;
public:
	CrossRefGen(){ width = 0; }

	void readFromFile(ifstream &f){
		int lineCount = 1;
		string line;
		while (f)
		{
			//regex e("[^a-zA-Z'\s\-]");
			regex aregx("\[a-zA-Z'-]+");
			getline(f, line);
			//lines.push_back(line);
			auto words_begin = sregex_iterator(line.begin(), line.end(), aregx);
			auto words_end = sregex_iterator();
			for (sregex_iterator it = words_begin; it != words_end; ++it) {
				smatch match = *it;
				string match_str = match.str();
				if (width < match_str.size()){
					width = match_str.size();
				}
				++(keyWords[match_str][lineCount]);			}
			++lineCount;
		}
	}

	void printCrossRef()
	{
		ofstream outFile("Cross.txt");
		map<string, map<int, int>>::iterator outerItr;
		map<int, int>::iterator innerItr;
		int counter = 0;
		for (outerItr = keyWords.begin(); outerItr != keyWords.cend(); ++outerItr)
		{	//output the word and width space
			outFile << setw(width + 2) << left << outerItr->first << ": ";
			//output line number : word count
			for (innerItr = outerItr->second.begin(); innerItr != outerItr->second.cend(); ++innerItr)
			{
				size_t size = outerItr->second.size();
				++counter;
				outFile << right << innerItr->first << ":" << innerItr->second;
				if (size > 1)
				{
					if (counter % LINE_LIMIT == 0)
					{
						outFile << "," << endl << setw(width + 2) << "  " << ": ";
					}
					else if (counter != size)
					{
						outFile << ", ";
					}
				}
			}
			counter = 0;
			outFile << endl;
		}
	}
};


int main(int argc, char* argv[])
{
	ifstream file;
	if (argc != 2){
		//get filename from user input
		string userInput;
		cout << "Please enter file name: "; cin >> userInput;
		cout << endl;
		file.open(userInput);
	}
	else
	{
		if (argc == 2 && !file){
			cerr << "Error! The file did not open." << endl;
		}
		else{
			file.open(argv[1]);
		}
	}
	CrossRefGen cross;
	cross.readFromFile(file);
	cross.printCrossRef();

	return 0;
}
