/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************
vector<process_stats> stats;

bool compareIOTime(const process_stats &p1, const process_stats &p2)
{
	return p1.io_time < p2.io_time;
}

bool compareCPUTime(const process_stats &p1, const process_stats &p2)
{
	return p1.cpu_time < p2.cpu_time;
}

bool compareStartTime(const process_stats &p1, const process_stats &p2)
{
	return p1.start_time < p2.start_time;
}

bool compareProcessNumber(const process_stats &p1, const process_stats &p2) 
{
	return p1.process_number < p2.process_number;
}

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) 
{
	stats.clear();
	fstream currentStream;
	string line;
	currentStream.open(filename, ios::in);
	
	if (!currentStream.is_open()) 
	{
			return COULD_NOT_OPEN_FILE;
	}
	if (ignoreFirstRow) 
	{
		getline(currentStream, line);
	}
	while(!currentStream.eof()) 
	{
		getline(currentStream, line);
		stringstream stringStream(line);
		
		process_stats stat;
		
		string procestringStream_num;
		string start_time;
		string cpu_time;
		string io_time;
		
		getline(stringStream, process_num, ',');
		getline(stringStream, start_time, ',');
		getline(stringStream, cpu_time, ',');
		getline(stringStream, io_time, ',');
		
		// For some reason the only way im able to get these to work the way I want
		bool pnl = (process_num.length() > 0);
		bool stl = (start_time.length() > 0);
		bool ctl = (cpu_time.length() > 0);
		bool itl = (io_time.length() > 0);
		
		if ( pnl || stl || ctl || itl ) 
		{
	           stat.procestringStream_number = stoi(procestringStream_num);
	           stat.start_time = stoi(start_time);
	           stat.cpu_time = stoi(cpu_time);
	           stat.io_time = stoi(io_time);
	           stats.push_back(stat);
	    }
	}
		currentStream.close();
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) 
{
	switch(mySortOrder)
	{
	case IO_TIME:
		sort(stats.begin(), stats.end(), compareIOTime);
		break;
	case START_TIME:
		sort(stats.begin(), stats.end(), compareStartTime);
		break;
	case CPU_TIME:
		sort(stats.begin(), stats.end(), compareCPUTime);
		break;
	case PROCESS_NUMBER:
		sort(stats.begin(), stats.end(), compareProcessNumber);
		break;
	default:
		break;
	}
}

process_stats getNext() 
{
	process_stats isFirst;
	isFirst = stats.front();
	stats.erase(stats.begin());
	return isFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows()
{
	return stats.size();
}


