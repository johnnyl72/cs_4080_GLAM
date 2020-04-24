#include "ScheduleBuilder.h"
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
using namespace std;

enum Day {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

enum Week {
	one,
	two
};

struct ScheduleBuilder : public Employee {
public:
	static map<int, Employee> employees;
	static list<string> requests;
	static int schedules[6][6];
};

class PayStub
{
	double hours, payRate;
public:
	PayStub() {

	}
	PayStub(double hours, double payRate) {
		this->hours = hours;
		this->payRate = payRate;
	}
	double getAmount() { return (hours * payRate); }
};

class Employee {
	
public:
	string name;
	double payRate;
	int employeeID;
	PayStub* check;
	int availability[7];

	Employee() {
		name = "";
		payRate = 0;
		employeeID = 0;
	}
	Employee(string name, double payRate, int employeeID, int availability[]) {
		this->name = name;
		this->payRate = payRate;
		this->employeeID = employeeID;
		*this->availability = *availability;

	}
	string getName() {
		return name;
	}
	double getHours() {
		int daysWorked = 0;
		for (int i = employeeID * 2; i <= employeeID * 2 + 1; i++) {
			for (int j = 0; j < 7; j++) {
				if (ScheduleBuilder::schedules[i][j] == 1) {
					daysWorked++;
				}
			}
		}
	}
	double getWeeksPay() {
		check = new PayStub(getHours(), payRate);
		return check->getAmount();
	}

	void getSchedule() {
		int week = 0;
		string mon = "";
		string tues = "";
		string weds = "";
		string thurs = "";
		string fri = "";
		string sat = "";
		string sun = "";

		for (int j = employeeID * 2; j < employeeID * 2 + 1; j++) {
			if (week == 0) {
				std::cout << "Week 1" << endl;
			}
			else {
				cout << "Week 2" << endl;
			}
			for (int i = 0; i <7; i++) {
				if (ScheduleBuilder::schedules[j][i] == 1) {
					switch (i) {
					case 0:
						mon = "Monday: Working";
						break;
					case 1:
						tues = "Tuesday: Working";
						break;
					case 2:
						weds = "Wednesday: Working";
						break;
					case 3:
						thurs = "Thursday: Working";
						break;
					case 4:
						fri = "Friday: Working";
						break;
					case 5:
						sat = "Saturday: Working";
						break;
					case 6:
						sun = "Sunday: Working";
						break;
					}

				}
				else {
					switch (i) {
					case 0:
						mon = "Monday: Off";
						break;
					case 1:
						tues = "Tuesday: Off";
						break;
					case 2:
						weds = "Wednesday: Off";
						break;
					case 3:
						thurs = "Thursday: Off";
						break;
					case 4:
						fri = "Friday: Off";
						break;
					case 5:
						sat = "Saturday: Off";
						break;
					case 6:
						sun = "Sunday: Off";
						break;
					}
				}
			}
			week++;
			cout << "+";
			for (int i = 0; i < 7; i++) {
				cout << setw(19) << setfill('-') << "+";
			}
			cout << endl;
			cout << "| " << setfill(' ') << setw(17) << left << mon;
			cout << "| " << setw(17) << left << mon;
			cout << "| " << setw(17) << left << tues;
			cout << "| " << setw(17) << left << weds;
			cout << "| " << setw(17) << left << thurs;
			cout << "| " << setw(17) << left << fri;
			cout << "| " << setw(17) << left << sat;
			cout << "| " << setw(17) << left << sun << "|" << endl;
			for (int i = 0; i < 7; i++) {
				cout << setw(19) << setfill('-') << "+";
			}
			cout << "+" << endl;
		}
	}
	int getID() {
		return employeeID;
	}
	
};
