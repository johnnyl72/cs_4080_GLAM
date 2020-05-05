#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <list>
using namespace std;
class Employee; class PayStub; class ManagementEmployee; class LineWorkEmployee;
map<int,Employee> employees;
list<string> requests;
int schedules[][7] = { {0,0,0,0,0,0,0}};
enum class Day {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

enum class Week {
    one,
    two
};
const char* dayToString(Day day)
{
    switch (day) {
        case Day::Monday:    return "Monday";
        case Day::Tuesday:   return "Tuesday";
        case Day::Wednesday: return "Wednesday";
        case Day::Thursday:  return "Thursday";
        case Day::Friday:    return "Friday";
        case Day::Saturday:  return "Saturday";
        default:      return "[Unknown Day]";
    }
}

const char* weekToString(Week week)
{
    switch (week) {
        case Week::one:    return "one";
        case Week::two:   return "two";
        default:      return "[Unknown Week]";
    }
}
class PayStub{
    double hours, payRate;
public:
    PayStub(double hours, double payRate) {
        this->hours = hours;
        this->payRate = payRate;
    }
    double getAmount() {
        return hours * payRate;
    }
};

class Employee {
public:
    string name;
    double payRate;
    int employeeID;
    PayStub *check;
    int availability[7] = {};

    Employee(string name, double payRate, int employeeID){

        this->name = name;
        this->payRate = payRate;
        this->employeeID = employeeID;
    }

    string getName() {
        return name;
    }
    int getID() {
        return employeeID;
    }
    double getWeeksPay() {
        check = new PayStub(getHours(), payRate);
        cout << "\nAmount: $" << check->getAmount() << endl;
        return check->getAmount();
    }
    double getHours() {
        int daysWorked = 0;
        //Iterate through this weeks schedule and calculate amount of days worked then perform calculation to get hours
        for(int i = employeeID*2; i <= employeeID*2+1; i++) {
            for(int j = 0; j < sizeof(schedules); j++) {
                if(schedules[i][j] == 1) {
                    daysWorked++;
                }
            }
        }
        //Assume 8 hour shifts
        return daysWorked * 8;
    }
    void getSchedule() {
        int week = 0;
        string mon = "", tues = "", weds = "", thurs = "", fri = "", sat = "", sun = "";

        for (int j = employeeID * 2; j <= (employeeID * 2 + 1); j++) {
            if (week == 0) {
                cout << "Week 1" << endl;
            } else {
                cout << "Week 2" << endl;
            }
            for (int i = 0; i < sizeof(schedules); i++) {
                if (schedules[j][i] == 1) {
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
                } else {
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
                cout << setw(18) << setfill('-') << "+";
            }
            cout << endl;
            cout << "| " << setfill(' ') << setw(16) << left << mon;
            cout << "| " << setw(16) << left << tues;
            cout << "| " << setw(16) << left << weds;
            cout << "| " << setw(16) << left << thurs;
            cout << "| " << setw(16) << left << fri;
            cout << "| " << setw(16) << left << sat;
            cout << "| " << setw(16) << left << sun << "|" << endl;
            for (int i = 0; i < 7; i++) {
                cout << setw(18) << setfill('-') << "+";
            }
            cout << "+" << endl;
        }
    }
};

class ManagementEmployee : public Employee {
public:
    ManagementEmployee(string name, double payRate, int employeeID) :
            Employee(name, payRate, employeeID) {

    }

    void wipeSchedule(Employee employee, Day day, Week week) {
        int row = -1, col = -1;
        int id = employee.employeeID * 2; // 0

        switch (day) {
            case Day::Monday:
                col = 0;
                break;
            case Day::Tuesday:
                col = 1;
                break;
            case Day::Wednesday:
                col = 2;
                break;
            case Day::Thursday:
                col = 3;
                break;
            case Day::Friday:
                col = 4;
                break;
            case Day::Saturday:
                col = 5;
                break;
            case Day::Sunday:
                col = 6;
                break;
        }
        switch (week) {
            case Week::one:
                row = 0;
                break;
            case Week::two:
                row = 1;
                break;
        }

        schedules[id + row][col] = 0;

    }
    void swapSchedule(Employee employee1, Employee employee2, Day day, Week week) {

        int row = -1, col = -1;
        int id1 = employee1.employeeID * 2; // 0
        int id2 = employee2.employeeID * 2; // 2

        switch (day) {
            case Day::Monday:
                col = 0;
                break;
            case Day::Tuesday:
                col = 1;
                break;
            case Day::Wednesday:
                col = 2;
                break;
            case Day::Thursday:
                col = 3;
                break;
            case Day::Friday:
                col = 4;
                break;
            case Day::Saturday:
                col = 5;
                break;
            case Day::Sunday:
                col = 6;
                break;
        }
        switch (week) {
            case Week::one:
                row = 0;
                break;
            case Week::two:
                row = 1;
                break;
        }
        //Put employee1 into temp var
        int temp = schedules[id1 + row][col];
        //Override employee1 with employee2
        schedules[id1 + row][col] = schedules[id2 + row][col];
        //Now put temp into employee1
        schedules[id2 + row][col] = temp;
    }
};

class LineWorkEmployee : public Employee {
public:
    LineWorkEmployee(string name, double payRate, int employeeID) :
    Employee(name, payRate, employeeID) {

    }

    void requestSwap(Employee employee, Day day, Week week) {
        requests.push_back(
                "\nRequesting Swap: \n" + name + " with " + employee.name + " on " + dayToString(day) + " on Week " +
                weekToString(week));
    }

    void requestWipe(Day day, Week week) {
        requests.push_back(
                "\nRequesting day off: \n" + name + " on " + dayToString(day) + " on Week " + weekToString(week));
    }
};

void printEmployeeList(){
    cout << "Employee List: " << endl;
    for (auto& x : employees) {
        cout << x.first << ": " << x.second.getName() << endl;
    }
}

void generateSchedule() {

    for (int i = 0; i < employees.size() * 2; i++) {
        for (int j = 0; j < 7; j++) {
            schedules[i][j] = 0;
        }
    }

    //assign everyone a shift based on their availability
    for (int i = 0; i < employees.size() * 2; i++) {
        int id = i / 2;
        for (int j = 0; j < 7; j++) {
            if (schedules[i][j] != employees.at(id).availability[j]) {
                schedules[i][j] = employees.at(id).availability[j];
            }
        }
    }

    // Now to remove conflicting schedules
    // Compare second employee with first, if conflict, give day to first employee
    // then compare third with second, fourth with third, etc....
    for (int i = 2; i < sizeof(schedules); i++) {
        for (int j = 0; j < 7; j++) {
            if (schedules[i - 2][j] == schedules[i][j]) {
                schedules[i][j] = 0;
            }
        }
    }
}

void viewRequests(){
    cout << "n\n----------------------------------------------\nCurrent Requests\n ";
    for (list<string>::iterator it = requests.begin(); it != requests.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << endl;
    cout << "----------------------------------------------" << endl;
}

void printMasterSchedule(){
    list<string> week1;
    list<string> week2;

    //week 1
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < sizeof(schedules); j += 2) {
            if ((schedules[j][i]) == 1) {
                week1.push_back(employees.at(j/2).getName());
                break;
            }
            else if (j == sizeof(schedules) - 2 && schedules[j][i] == 0) {
                week1.push_back("Empty");
                break;
            }
        }
    }

    //week 2
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < sizeof(schedules); j += 2) {
            if (schedules[j][i] == 1) {
                week2.push_back(employees.at(j/2).getName());
                break;
            }
            else if (j == sizeof(schedules) - 2 && schedules[j][i] == 0) {
                week2.push_back("Empty");
            }
        }
    }

    cout << endl;
    cout << "Week 1" << endl;
    cout << "| " << setfill(' ') << setw(11) << left << "Monday";
    cout << "| " << setw(11) << left << "Tuesday";
    cout << "| " << setw(11) << left << "Wednesday";
    cout << "| " << setw(11) << left << "Thursday";
    cout << "| " << setw(11) << left << "Friday";
    cout << "| " << setw(11) << left << "Saturday";
    cout << "| " << setw(11) << left << "Sunday" << "|" << endl;
    for (int i = 0; i < 7; i++) {
        cout << setw(13) << setfill('-') << "+";
    }
    cout << "+" << endl;

    for (list<string>::iterator it = week1.begin(); it != week1.end(); ++it) {
        cout << "|" ;
        cout << ' ' << setw(11) << setfill(' ') << *it;
    }
    cout << "|";

    cout << endl;
    cout << "Week 2" << endl;
    cout << "| " << setfill(' ') << setw(11) << left << "Monday";
    cout << "| " << setw(11) << left << "Tuesday";
    cout << "| " << setw(11) << left << "Wednesday";
    cout << "| " << setw(11) << left << "Thursday";
    cout << "| " << setw(11) << left << "Friday";
    cout << "| " << setw(11) << left << "Saturday";
    cout << "| " << setw(11) << left << "Sunday" << "|" << endl;
    for (int i = 0; i < 7; i++) {
        cout << setw(13) << setfill('-') << "+";
    }
    cout << "+" << endl;

    for (list<string>::iterator it = week2.begin(); it != week2.end(); ++it) {
        cout << "|" ;
        cout << ' ' << setw(11) << setfill(' ') << *it;
    }
    cout << "|";
}

int main() {

    int temp1[] = { 1,1,0,1,0,1,0 }; //Monday, Tuesday, Thursday, Saturday
    int temp2[] = { 1,1,0,1,0,0,1 }; //Monday, Tuesday, Thursday, Sunday
    int temp3[] = { 0,0,1,0,1,0,1 }; //Wednesday, Friday, Sunday

    ManagementEmployee* bob = new ManagementEmployee("Bob", 100.0, 0);
    copy(begin(temp1), end(temp1), begin(bob->availability));

    ManagementEmployee* janet = new ManagementEmployee("Janet", 200.0, 1);
    copy(begin(temp2), end(temp2), begin(janet->availability));

    LineWorkEmployee* steven = new LineWorkEmployee("Steven", 10.0, 2);
    copy(begin(temp3), end(temp3), begin(steven->availability));

    employees.insert({ bob->getID(), *bob });
    employees.insert({ janet->getID(), *janet });
    employees.insert({ steven->getID(), *steven });

    printEmployeeList();
    generateSchedule();

    cout << "\nBob's Schedule: " << endl;
    bob->getSchedule();
    bob->getWeeksPay();
    cout << "\nJanet's Schedule: " << endl;
    janet->getSchedule();
    janet->getWeeksPay();
    cout << "\nSteven's Schedule: " << endl;
    steven->getSchedule();
    steven->getWeeksPay();

    //Simulate requests for swap and day off
    steven->requestSwap(*bob, Day::Wednesday, Week::one);
    steven->requestWipe(Day::Friday, Week::one);
    viewRequests();

    bob->swapSchedule(*bob, *steven, Day::Wednesday, Week::one);
    bob->wipeSchedule(*steven, Day::Friday, Week::one);

    cout << "\n\nApproved Steven's Swap request" << endl;
    cout << "Approved Steven's Day Off Request" << endl;
    cout << "\n\nNEW Schedule" << endl;
    cout << "\nBob's Schedule" << endl;
    bob->getSchedule();

    cout << "\nJanet's Schedule" << endl;
    janet->getSchedule();

    cout << "\nSteven's Schedule" << endl;
    steven->getSchedule();

    cout << "MASTER SCHEDULE "<< endl;
    printMasterSchedule();

    return 0;

};
