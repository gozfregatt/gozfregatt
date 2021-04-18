#include <iostream>
//#include <ctime>
#include "DueDate.h"
/* function with input
	- submit date/time - values are set between 9:00 - 17:00
	- turnaround time - hours

	output is the resloution date/time

	- Get input
	- check/find time: between 9:00 - 17:00
	- check/find date: Mon - Fri
	- return Due Date
*/

using namespace std;

DueDate::DueDate() {
	// get current time info to fill the timeStruct with it
	time_t rawtime;
	time(&rawtime);
	// Populate the timeStruct; Now the members can be modified
	gmtime_s(&timeStruct, &rawtime);
}

DueDate::~DueDate() {
}

void DueDate::UpdateDateTimeStruct(int year, int month, int day, int hour, int min)
{
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = hour;
	timeStruct.tm_min = min;

	// Update timeStruct with input values
	mktime(&timeStruct);
} 

void DueDate::AddTurnaround(int turnaround)
{
	for (int i = 0; i < turnaround; i++) {
		// The "Hour" parameter is increased step by step.
		// If DAY_END is reached, the number of "Days" is also incremented 
		timeStruct.tm_hour+=1;

		if (timeStruct.tm_hour >= DAY_END) {
			timeStruct.tm_mday++;
			timeStruct.tm_hour = DAY_START;
		}

		// Refresh the timeStruct to have correct tm_wday (day of the week) value
		mktime(&timeStruct);

		// 0 = sunday; 6 = saturday, no work at weekends!
		if (timeStruct.tm_wday == 0) {
			timeStruct.tm_mday += 1;
		}
		else if (timeStruct.tm_wday == 6) {
			timeStruct.tm_mday += 2;
		}
		// Refresh timeStruct if
		mktime(&timeStruct);
	}

}

tm DueDate::CalculateDueDate(int year, int month, int day, int hour, int min, int turnaround) {

	UpdateDateTimeStruct(year, month, day, hour, min);
	
	char buffer[128];
	
	strftime(buffer, sizeof buffer, "Submit Time: %c", &timeStruct);
	cout << buffer << endl;

	AddTurnaround(turnaround);

	cout << "Turnaround: " << turnaround << " hours" << endl;
	strftime(buffer, sizeof buffer, "Due Date: %c", &timeStruct);
	cout << buffer << "\n" << endl;

	return timeStruct;
}