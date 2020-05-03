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

const char* dayToString(Day day)
{
	switch (day) {
	case Monday:    return "Monday";
	case Tuesday:   return "Tuesday";
	case Wednesday: return "Wednesday";
	case Thursday:  return "Thursday";
	case Friday:    return "Friday";
	default:      return "[Unknown Day]";
	}
}

enum Week {
	one,
	two
};

const char* weekToString(Week week)
{
	switch (week) {
	case one:    return "one";
	case two:   return "two";
	default:      return "[Unknown Week]";
	}
}

class ScheduleBuilder : public Employee {
public:
	static map<int, Employee> *employees;
	static list<string> *requests;
	static int schedules[employees->size*2][7];
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

class ManagementEmployee : public Employee {
public:
	ManagementEmployee(string name, double payRate, int employeeID, int availability[]) :
		Employee(name, payRate, employeeID, availability) {

	}
	bool wipeSchedule(Employee employee, Day day, Week week) {
		int row = -1, col = -1;
		int id = employee.employeeID * 2; // 0

		switch (day) {
		case Monday:
			col = 0;
			break;
		case Tuesday:
			col = 1;
			break;
		case Wednesday:
			col = 2;
			break;
		case Thursday:
			col = 3;
			break;
		case Friday:
			col = 4;
			break;
		case Saturday:
			col = 5;
			break;
		case Sunday:
			col = 6;
			break;
		}
		switch (week) {
		case one:
			row = 0;
			break;
		case two:
			row = 1;
			break;
		}

		ScheduleBuilder::schedules[id + row][col] = 0;

		return true;
	}
	bool swapSchedule(Employee employee1, Employee employee2, Day day, Week week) {

		int row = -1, col = -1;
		int id1 = employee1.employeeID * 2; // 0
		int id2 = employee2.employeeID * 2; // 2

		switch (day) {
		case Monday:
			col = 0;
			break;
		case Tuesday:
			col = 1;
			break;
		case Wednesday:
			col = 2;
			break;
		case Thursday:
			col = 3;
			break;
		case Friday:
			col = 4;
			break;
		case Saturday:
			col = 5;
			break;
		case Sunday:
			col = 6;
			break;
		}
		switch (week) {
		case one:
			row = 0;
			break;
		case two:
			row = 1;
			break;
		}
		//Put employee1 into temp var
		int temp = ScheduleBuilder::schedules[id1 + row][col];
		//Override employee1 with employee2
		ScheduleBuilder::schedules[id1 + row][col] = ScheduleBuilder::schedules[id2 + row][col];
		//Now put temp into employee1
		ScheduleBuilder::schedules[id2 + row][col] = temp;

		return true;
	}

};

class LineWorkEmployee : public Employee {
public:
	LineWorkEmployee(string name, double payRate, int employeeID, int availability[]) :
		Employee(name, payRate, employeeID, availability) {

	}
	bool requestSwap(Employee employee, Day day, Week week) {
		ScheduleBuilder::requests->push_back("Requesting Swap: \n" + name + " with " + employee.name + " on " + dayToString(day) +" on Week " + weekToString(week));
		return true;
	}
	bool requestWipe(Day day, Week week) {
		ScheduleBuilder::requests->push_back("Requesting day off: \n" + name + " on " + dayToString(day) + " on Week " + weekToString(week));
		return true;
	}
};

int main() {
	ScheduleBuilder* schedule = new ScheduleBuilder();
	int temp1[] = { 1,1,0,1,0,1,0 }; //Monday, Tuesday, Thursday, Saturday
	int temp2[] = { 1,1,0,1,0,0,1 }; //Monday, Tuesday, Thursday, Sunday
	int temp3[] = { 0,0,1,0,1,0,1 }; //Wednesday, Friday, Sunday

	ManagementEmployee *bob = new ManagementEmployee("Bob", 100.0, 0, temp1);
	ManagementEmployee* janet = new ManagementEmployee("Janet", 200.0, 1, temp2);
	LineWorkEmployee* steven = new LineWorkEmployee("Steven", 10.0, 2, temp3);

	schedule->employees->insert(pair<int,ManagementEmployee>(bob->getID(), *bob));
	schedule->employees->insert(pair<int,ManagementEmployee>(janet->getID(), *janet));
	schedule->employees->insert(pair<int,LineWorkEmployee>(steven->getID(), *steven));


}
