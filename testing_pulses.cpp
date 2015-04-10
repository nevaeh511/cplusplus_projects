#if defined(_WIN32)
#define listcmd "dir /b *.dat > datfiles.txt 2>nul"
#elif defined(__GNUC__)
#define listcmd "ls *.dat > datfiles.txt 2>/dev/null"
#else
#error  Unsupported compiler.
#endif

#include<iostream>
#include<bitset>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
using namespace std::placeholders;
int wghtAvg(int& it);
void readPulseParameters(int size, ifstream& in);
int detectPulse(int& p);
bool findPeak(int& f, int& n);
//global variables: pulse parameters
double drop_ratio = 0;
int below_drop_ratio = 0, pulse_delta = 0, voltage_threshold = 0, width = 0;

int main(int argc, char* argv[])
{
	system(listcmd);
	vector<string> fileVec;
	ifstream datFiles("datfiles.txt");
	ifstream iniFile(argv[1]);
	string fileName, fileName2;
	try{
		readPulseParameters(argc, iniFile);	
	}
	catch (runtime_error& exceptions){
		cerr << exceptions.what() << endl;
		return -1;
	}
	while (datFiles >> fileName){
		fileVec.push_back(fileName);
	}

	for (size_t j = 0; j < fileVec.size(); ++j)	//read and process pulses in a file
	{
		ifstream file;
		int number;
		vector<int> jagged, smooth;

		file.open(fileVec[j]);
		while (file >> number){
			jagged.push_back(number);
		}

		transform(begin(jagged), end(jagged), begin(jagged), negate<int>());
		copy(begin(jagged), begin(jagged) + 3, back_inserter(smooth));
		transform(begin(jagged) + 3, end(jagged) - 3, back_inserter(smooth), wghtAvg);
		copy(end(jagged) - 3, end(jagged), back_inserter(smooth));

		//detect pulses
		vector<int>::iterator peakItr, pulseItr;
		vector<int> pulses, peaks;
		int startFind, testPoint;
		for (int i = 0; i < smooth.size() - 2; ++i)
		{
			testPoint = smooth[i + 2] - smooth[i];
			if (testPoint > voltage_threshold)
			{
				pulses.push_back(i);	//pulse found
				startFind = i+2;
				peakItr = adjacent_find(begin(smooth) + startFind, end(smooth), findPeak);	//peak of pulse found
				peaks.push_back(peakItr - begin(smooth));
				i = peakItr - begin(smooth);
			}
		}//end detect pulse

		//remove piggyback pulses
		for (int k = 0; k < pulses.size()-1; ++k)
		{
			int pulseTwoPos, pulseOnePos, peakBetween, pulseDelta, points; 
			pulseTwoPos = pulses[k+1];
			pulseOnePos = pulses[k];
			peakBetween = peaks[k];
			pulseDelta = pulseTwoPos - pulseOnePos;
			if (pulseDelta <= pulse_delta)
			{
				int heightOfPeak = smooth[peakBetween];
				peakItr = begin(smooth) + (peakBetween + 1);
				pulseItr = begin(smooth) + (pulseTwoPos);
				points = count_if(peakItr, pulseItr, [heightOfPeak](int p){return p < (drop_ratio* heightOfPeak); });
				if (points > below_drop_ratio)
				{
					pulses.erase(begin(pulses) + k);
					peaks.erase(begin(peaks) + k);
					--k;
				}
			}

		}

		//calculate area of each pulse
		vector<int> areas;
		for (int i = 0; i < pulses.size(); i++){
			int area, diff;
			if (i == pulses.size() - 1){
				int lastPulse = pulses[i] + width;
				area = accumulate(begin(jagged) + pulses[i], begin(jagged) + lastPulse, 0);
				areas.push_back(area);
			}
			else{
				diff = pulses[i + 1] - pulses[i];
				if (diff < width){
					area = accumulate(begin(jagged) + pulses[i], begin(jagged) + pulses[i + 1], 0);
					areas.push_back(area);
				}
				else{
					area = accumulate(begin(jagged) + pulses[i], begin(jagged) + (pulses[i] + width), 0);
					areas.push_back(area);
				}
			}
		}

		//print out file name, pulses and areas
		cout << fileVec[j] << ": ";	
		for_each(begin(pulses), end(pulses), [](int pulse){cout << pulse << " "; });
		cout << endl;
		for_each(begin(areas), end(areas), [](int a){cout << a << " "; });
		cout << endl;
	}
	remove("datfiles.txt");
	return 0;
}

bool findPeak(int& f, int& n)
{
	int* first = &f;
	int* next = &n;
	return *next < *first;
}
//read and parse .ini files
void readPulseParameters(int argc, ifstream& in)
{
	string param, line;
	int pos;
	double value;
	enum { v, w, pd, dr, bdr };
	int const COUNT = 5;
	bitset<COUNT> parameters;
	static int counter = 0;
	if (argc != 2 || !in){
		if (!in){
			throw runtime_error("Error! The file could not open.");
		}
		else{
			throw runtime_error("Error! There was no input file.");
		}
	}
	while (in >> line){
		//getline(in, line);
		pos = line.find('=');
		param = line.substr(0, pos);
		value = stod(line.substr(pos + 1));

		if (param == "vt"){
			parameters[v].flip();
			voltage_threshold = value;
			++counter;
		}
		else if (param == "width"){
			parameters[w].flip();
			width = value;
			++counter;
		}
		else if (param == "pulse_delta"){
			parameters[pd].flip();
			pulse_delta = value;
			++counter;
		}
		else if (param == "drop_ratio"){
			parameters[dr].flip();
			drop_ratio = value;
			++counter;
		}
		else if (param == "below_drop_ratio"){
			parameters[bdr].flip();
			below_drop_ratio = value;
			++counter;
		}
		else{
			throw runtime_error("Error! Parameter not found.");
		}
		//setPulseParam(param, value);
	}
	if (counter != COUNT)
	{
		for (int i = 0; i < parameters.size(); i++)
		{
			if (parameters[i] == 0)
			{
				throw runtime_error("Missing parameter!");
			}
		}
	}
}
int wghtAvg(int &it)
{
	int* iter = &it;
	int number;
	number = (iter[-3] + 2 * iter[-2] + 3 * iter[-1] + 3 * iter[0] + 3 * iter[1] + 2 * iter[2] + iter[3]) / 15;
	return number;
}

/*
I really like the ability and funcitonality of the algorithms. However, I had a bit of difficulty figuring out
how to use them. It was so tempting to use more and more loops. I still used some though because I just
counldn't figure out what else to do. I had some ideas but time did not allow me to keep going. Very interesting
project. This was a mind twister for me.
*/