package cs4080;

import java.util.*;

// Prototype
// Assume we build schedules knowing our employee's availability beforehand
// Biweekly schedule with PayStubs accounting for biweekly work

public class ScheduleBuilder {
	static Map<String, Integer> employees = new HashMap<>();
	static List<String> requests = new ArrayList<>();
	//For now we will not focus on creating the schedule lets just seed the data
	static int[][] schedules =
		{
			{1,0,1,1,1,0,1},	// Mon: Day 	Tues: Off 		Wed: Day 	Thurs: Day		Fri: Day 	Sat: Off 	Sun: Day
			{2,1,0,2,0,1,2},	// Mon: Night 	Tues: Day 		Wed: Off 	Thurs: Night 	Fri: Off 	Sat: Day 	Sun: Night

			{0,2,2,0,2,2,0},	// Mon: Off 	Tues: Night 	Wed: Night 	Thurs: Off 	 	Fri: Night 	Sat: Night 	Sun: Off
			{0,0,0,0,0,0,0},	// Mon: Off 	Tues: Off 		Wed: Off 	Thurs: Off 	 	Fri: Off 	Sat: Off 	Sun: Off

			{2,2,2,2,2,2,2},	// Mon: Night 	Tues: Night 	Wed: Night 	Thurs: Night	Fri: Night 	Sat: Night 	Sun: Night
			{1,1,1,1,1,1,1}		// Mon: Day 	Tues: Day 		Wed: Night 	Thurs: Day		Fri: Day 	Sat: Day 	Sun: Day
		};
	public static void main(String[] args) {
		//Name, Hourly Rate, EmployeeID
		ManagementEmployee bob = new ManagementEmployee("Bob", 22.0, 0 );
		System.out.println(bob.getName());
		bob.getSchedule();
		System.out.println("Pay " + bob.getWeeksPay() + "\n");

		//Name, Hourly Rate, EmployeeID
		ManagementEmployee janet = new ManagementEmployee("Janet", 220.0, 1);
		System.out.println(janet.getName());
		janet.getSchedule();
		System.out.println("Pay " + janet.getWeeksPay() + "\n");

		String str1 = "THURSDAY";
		String str2 = "WEDNESDAY";
		String str3 = "FIRST";
		bob.swapSchedule(bob, janet, Day.valueOf(str1), Week.valueOf(str3));
		bob.wipeSchedule(bob, Day.valueOf(str2), Week.valueOf(str3));
		bob.wipeSchedule(bob, Day.valueOf("MONDAY"), Week.valueOf(str3));
		bob.getSchedule();
		System.out.println(bob.getWeeksPay());

		System.out.println(bob.getName());
		bob.getSchedule();
		System.out.println("Pay " + bob.getWeeksPay() + "\n");
		System.out.println(janet.getName());
		janet.getSchedule();
		System.out.println("Pay " + janet.getWeeksPay() + "\n");

		employees.put(bob.getName(), bob.getID());
		employees.put(janet.getName(), janet.getID());
		printEmployeeList();

		LineWorkEmployee steven = new LineWorkEmployee("Steven", 12.99, 2);
		steven.requestSwap(bob, steven, Day.valueOf(str2), Week.valueOf(str3));
		viewRequests();

	}
	static void printEmployeeList() {

		System.out.println("Employee List:");

        // using for-each loop for iteration over Map.entrySet()
        for (Map.Entry<String,Integer> entry : employees.entrySet())
            System.out.println("Name: " + entry.getKey() + "\t ID: " + entry.getValue());
	}
	static void printMasterSchedule() {
		//Print employee working each day and shift they are working
	}
	static void viewRequests() {
		System.out.println("Current Requests:");
		for(String x: requests) {
			System.out.println(x);
		}
	}
}
enum Day{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
}
enum Week{
	FIRST,
	SECOND
}
class Employee {
	String name;
	double payRate;
	int employeeID;
	PayStub check;
	String getName() {
		return name;
	}
	double getWeeksPay() {
		check.hours = getHours(); //Get latest hours
		return check.getAmount();
	}
	double getHours() {
		int daysWorked = 0;
		//Iterate through this weeks schedule and calculate amount of days worked then perform calculation to get hours
		for(int i = employeeID*2; i <= employeeID*2+1; i++) {
			for(int j = 0; j < ScheduleBuilder.schedules[i].length; j++) {
				if(ScheduleBuilder.schedules[i][j] == 1 || ScheduleBuilder.schedules[i][j] == 2) {
					daysWorked++;
				}
			}
		}
		return daysWorked * 8;
	}
	void getSchedule() {
		int week = 0;

		for(int j = employeeID*2; j <= (employeeID*2+1); j++) {
			if(week == 0)
				System.out.println("Week 1");
			else
				System.out.println("Week 2");
			for(int i = 0; i < ScheduleBuilder.schedules[j].length; i++) {
				if(ScheduleBuilder.schedules[j][i] == 1) {
					switch(i) {
						case 0:
							System.out.print(" | Mon: Morning");
							break;
						case 1:
							System.out.print(" | Tues: Morning");
							break;
						case 2:
							System.out.print(" | Weds: Morning");
							break;
						case 3:
							System.out.print(" | Thurs: Morning" );
							break;
						case 4:
							System.out.print(" | Fri: Morning" );
							break;
						case 5:
							System.out.print(" | Sat: Morning" );
							break;
						case 6:
							System.out.println(" | Sun: Morning | " );
							break;
					}
				}
				else if (ScheduleBuilder.schedules[j][i] == 2) {
					switch(i) {
						case 0:
							System.out.print(" | Mon: Night" );
							break;
						case 1:
							System.out.print(" | Tues: Night" );
							break;
						case 2:
							System.out.print(" | Weds: Night" );
							break;
						case 3:
							System.out.print(" | Thurs: Night" );
							break;
						case 4:
							System.out.print(" | Fri: Night" );
							break;
						case 5:
							System.out.print(" | Sat: Night" );
							break;
						case 6:
							System.out.println(" | Sun: Night | " );
							break;
					}
				}
				else{
					switch(i) {
						case 0:
							System.out.print(" | Mon: Off");
							break;
						case 1:
							System.out.print(" | Tues: Off");
							break;
						case 2:
							System.out.print(" | Weds: Off");
							break;
						case 3:
							System.out.print(" | Thurs: Off");
							break;
						case 4:
							System.out.print(" | Fri: Off");
							break;
						case 5:
							System.out.print(" | Sat: Off");
							break;
						case 6:
							System.out.println(" | Sun: Off | ");
							break;
					}
				}
			}
			week++;
		}
	}
	int getID() {
		return employeeID;
	}
	public Employee(String name, double payRate, int employeeID){
		this.name = name;
		this.payRate = payRate;
		this.employeeID = employeeID;
	}
}
class ManagementEmployee extends Employee{
	public ManagementEmployee(String name, double payRate, int employeeID) {
		super(name, payRate, employeeID);
		check = new PayStub(getHours(), payRate);
	}
	boolean wipeSchedule(Employee employee, Day day, Week week) {
		int row = -1, col = -1;
		int id = employee.employeeID * 2; // 0

		switch(day) {
			case MONDAY:
				col = 0;
				break;
			case TUESDAY:
				col = 1;
				break;
			case WEDNESDAY:
				col = 2;
				break;
			case THURSDAY:
				col = 3;
				break;
			case FRIDAY:
				col = 4;
				break;
			case SATURDAY:
				col = 5;
				break;
			case SUNDAY:
				col = 6;
				break;
		}
		switch(week) {
			case FIRST:
				row = 0;
				break;
			case SECOND:
				row = 1;
				break;
		}

		ScheduleBuilder.schedules[id+row][col] = 0;

		return true;
	}
	boolean swapSchedule(Employee employee1, Employee employee2, Day day, Week week) {

		int row = -1, col = -1;
		int id1 = employee1.employeeID * 2; // 0
		int id2 = employee2.employeeID * 2; // 2

		switch(day) {
			case MONDAY:
				col = 0;
				break;
			case TUESDAY:
				col = 1;
				break;
			case WEDNESDAY:
				col = 2;
				break;
			case THURSDAY:
				col = 3;
				break;
			case FRIDAY:
				col = 4;
				break;
			case SATURDAY:
				col = 5;
				break;
			case SUNDAY:
				col = 6;
				break;
		}
		switch(week) {
			case FIRST:
				row = 0;
				break;
			case SECOND:
				row = 1;
				break;
		}
		//Put employee1 into temp var
		int temp = ScheduleBuilder.schedules[id1+row][col];
		//Override employee1 with employee2
		ScheduleBuilder.schedules[id1+row][col] = ScheduleBuilder.schedules[id2+row][col];
		//Now put temp into employee1
		ScheduleBuilder.schedules[id2+row][col] = temp;

		return true;
	}
}

class LineWorkEmployee extends Employee{
	public LineWorkEmployee(String name, double payRate, int employeeID) {
		super(name, payRate, employeeID);
		check = new PayStub(getHours(), payRate);
	}
	boolean requestSwap(Employee employee1, Employee employee2, Day day, Week week) {

		ScheduleBuilder.requests.add("Employee: " + employee1.employeeID + " Employee: " + employee2.employeeID + " Day: " + day + " Week: "+ week);
		return true;
	}
	boolean requestWipe(Day day, Week week) {
		return false;
	}
}


class PayStub{
	double hours, payRate, minsLate;
	public PayStub(double hours, double payRate) {
		this.hours = hours;
		this.payRate = payRate;
	}
	double getAmount() {
		return hours * payRate;
	}
}
