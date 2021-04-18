#include <ctime>

class DueDate {
public:
	DueDate();
	~DueDate();
	// The main functionality of this class called with simple integer parameters
	tm CalculateDueDate(int year, int month, int day, int hour, int min, int turnaround);

private:
	// This function updates the timeStruct (tm) with Submit Date and Time
	void UpdateDateTimeStruct(int year, int month, int day, int hour, int min);

	// This function adds Turnaround time to Submit Date and Time
	void AddTurnaround(int turnaround);


	struct tm timeStruct;		// The tm time structure, as the core element of this module
	int turnaround = 0;
	const int DAY_START = 9;
	const int DAY_END = 17;
};






