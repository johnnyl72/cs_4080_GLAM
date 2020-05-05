import java.util.*;
import java.util.Map.Entry;

// Assume we build schedules knowing our employee's availability beforehand
// Biweekly schedule with PayStubs accounting for biweekly work


public class ScheduleBuilder {
	static Map<Integer, Employee> employees = new HashMap<>();
	static List<String> requests = new ArrayList<>();
	static int[][] schedules;
	
	public static void main(String[] args) {
		
		long start = System.nanoTime();
		//Sample availibility schedules
		int[] temp1 = {1,1,0,1,0,1,0}; //Monday, Tuesday, Thursday, Saturday
		int[] temp2 = {1,1,0,1,0,0,1}; //Monday, Tuesday, Thursday, Sunday
		int[] temp3 = {0,0,1,0,1,0,1}; //Wednesday, Friday, Sunday
		
		//Name, Hourly Rate, EmployeeID
		ManagementEmployee bob = new ManagementEmployee("Bob", 100.0, 0, temp1 );
		ManagementEmployee janet = new ManagementEmployee("Janet", 200.0, 1, temp2 );
		LineWorkEmployee steven = new LineWorkEmployee("Steven", 10.0, 2, temp3 );
		
		employees.put(bob.getID(), bob);
		employees.put(steven.getID(), steven);
		employees.put(janet.getID(), janet);
		
		printEmployeeList();
		generateSchedule();
		
		System.out.println("\nBob's Schedule");
		bob.getSchedule();
		bob.getWeeksPay();
		System.out.println("\nJanet's Schedule");
		janet.getSchedule();
		janet.getWeeksPay();
		System.out.println("\nSteven's Schedule");
		steven.getSchedule();
		steven.getWeeksPay();
		
		//Simulate requests for wap and day off
		steven.requestSwap(bob, Day.valueOf("Wednesday"), Week.valueOf("one"));
		steven.requestWipe(Day.valueOf("Friday"), Week.valueOf("one"));
		viewRequests();
		bob.swapSchedule(bob, steven, Day.valueOf("Wednesday"), Week.valueOf("one"));
		bob.wipeSchedule(steven, Day.valueOf("Friday"), Week.valueOf("one"));
		
		System.out.println("\n\nApproved Steven's Swap Request");
		System.out.println("Approved Steven's Day Off Request");
		System.out.println("\n\nNEW Schedule");
		System.out.println("\nBob's Schedule");
		bob.getSchedule();
		System.out.println("\nJanet's Schedule");
		janet.getSchedule();
		System.out.println("\nSteven's Schedule");
		steven.getSchedule();
		System.out.println("\n MASTER SCHEDULE");
		
		printMasterSchedule();
		long timeInNano = System.nanoTime() - start;
		System.out.println(timeInNano);

	}
	static void printMasterSchedule() {
		
		List<String> week1 = new ArrayList<>();
		List<String> week2 = new ArrayList<>();
		
		//Week 1
		for(int i = 0; i < 7; i++) {
			for(int j = 0; j < schedules.length; j = j+2) {
				if(schedules[j][i] == 1) {
					week1.add(employees.get(j/2).getName());
					break;
				}
				else if (j == schedules.length-2 && schedules[j][i] == 0) {
					week1.add("Empty");
				}
			}
		}
		
		//Week 2
		for(int i = 0; i < 7; i++) {
			for(int j = 1; j < schedules.length; j = j+2) {
				if(schedules[j][i] == 1) {
					week2.add(employees.get(j/2).getName());
					break;
				}
				else if (j == schedules.length-1 && schedules[j][i] == 0) {
					week2.add("Empty");
				}
			}
		}
		
		String leftAlignFormat = "| %-19s | %-19s | %-19s | %-19s | %-19s | %-19s | %-19s | %n";
		System.out.println("Week 1");
		System.out.format("+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+%n");
		System.out.format(leftAlignFormat, "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday" );
		System.out.format(leftAlignFormat, week1.get(0) , week1.get(1), week1.get(2), week1.get(3), week1.get(4), week1.get(5), week1.get(6));
		System.out.format("+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+%n");
		System.out.println("Week 2");
		System.out.format("+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+%n");
		System.out.format(leftAlignFormat, "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday" );
		System.out.format(leftAlignFormat, week1.get(0) , week2.get(1), week2.get(2), week2.get(3), week2.get(4), week2.get(5), week2.get(6));
		System.out.format("+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+%n");
	
	}
	static void generateSchedule() {
		
		int[][] sched = new int[employees.size()*2][7];
		//Generate empty schedule
		for(int i = 0; i < employees.size()*2; i++) {
			for(int j = 0; j < 7; j++ ) {
				sched[i][j] = 0;
			}
		}
		//Just assign everyone a shift based on their availibility
		for(int i = 0; i < employees.size()*2; i++) {
			int id = i/2;
			Employee emp = employees.get(id);
			int[] availibility = emp.getAvailibility();
			for(int j = 0; j < 7; j++) {
				if(sched[i][j] != availibility[j])
					sched[i][j] = availibility[j];
				else
					sched[i][j] = 0;
			}
		}
		// Now to remove conflicting schedules
		// Compare second employee with first, if conflict, give day to first employee
		// then compare third with second, fourth with third, etc....
		for(int i = 2; i < sched.length; i++) {
			for (int j = 0; j < 7; j++) {
				if(sched[i-2][j] == sched[i][j]) {
					sched[i][j] = 0;
 				}
			}
		}
		schedules = sched;
	}
	static void printEmployeeList() {
		System.out.println("Employee List:");
		
        // using for-each loop for iteration over Map.entrySet() 
        for (Entry<Integer, Employee> entry : employees.entrySet())  
            System.out.println("ID: " + entry.getKey() + "\t Name: " + entry.getValue().getName()); 
	}
	static void viewRequests() {
		System.out.println("\n\n----------------------------------------------\nCurrent Requests\n");
		for(String x: requests) {
			System.out.println(x);
		}
		System.out.println("----------------------------------------------");
	}
	static void clearRequests() {
		System.out.println("\nCleared Requests!");
		requests.clear();;
	}
}
enum Day{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
}
enum Week{
	one,
	two
}
class Employee {
	String name;
	double payRate;
	int employeeID;
	PayStub check;
	int[] availibility;
	String getName() {
		return name;
	}
	double getWeeksPay() {
		check = new PayStub(getHours(), payRate);
		System.out.println("Amount: $"+check.getAmount());
		return check.getAmount();
	}
	double getHours() {
		int daysWorked = 0;
		//Iterate through this weeks schedule and calculate amount of days worked then perform calculation to get hours
		for(int i = employeeID*2; i <= employeeID*2+1; i++) {
				for(int j = 0; j < ScheduleBuilder.schedules[i].length; j++) {
					if(ScheduleBuilder.schedules[i][j] == 1) {
						daysWorked++;
					}
				}
		}
		//Assume 8 hour shifts
		return daysWorked * 8;
	}
	void getSchedule() {
		int week = 0;
		String mon = "", tues = "", weds = "", thurs = "", fri = "", sat = "", sun = "";
		
		for(int j = employeeID*2; j <= (employeeID*2+1); j++) {
			if(week == 0) {
				System.out.println("Week 1");
			}
			else {
				System.out.println("Week 2");
			}
			for(int i = 0; i < ScheduleBuilder.schedules[j].length; i++) {
				if(ScheduleBuilder.schedules[j][i] == 1) {
					switch(i) {
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
				else{
					switch(i) {
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
			System.out.format("+---------------------+---------------------+---------------------+"
					+ "---------------------+---------------------+---------------------+---------------------+%n");
			String leftAlignFormat = "| %-19s | %-19s | %-19s | %-19s | %-19s | %-19s | %-19s | %n";
				System.out.format(leftAlignFormat, mon , tues, weds, thurs, fri, sat, sun);
			System.out.format("+---------------------+---------------------+---------------------+"
					+ "---------------------+---------------------+---------------------+---------------------+%n");
		}
	}
	int getID() {
		return employeeID;
	}
	int[] getAvailibility() {
		return availibility;
	}
	void changeName(String name) {
		this.name = name;
	}
	
	public Employee(String name, double payRate, int employeeID, int[] availibility){
		
		this.availibility = availibility;
		this.name = name;
		this.payRate = payRate;
		this.employeeID = employeeID;

	}
}
class ManagementEmployee extends Employee{
	public ManagementEmployee(String name, double payRate, int employeeID, int[] availibility) {
		super(name, payRate, employeeID, availibility);
	}
	boolean wipeSchedule(Employee employee, Day day, Week week) {
		int row = -1, col = -1;
		int id = employee.employeeID * 2; // 0
		
		switch(day) {
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
		switch(week) {
			case one:
				row = 0;
				break;	
			case two:
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
		switch(week) {
			case one:
				row = 0;
				break;	
			case two:
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
	public LineWorkEmployee(String name, double payRate, int employeeID, int[] availibility) {
		super(name, payRate, employeeID, availibility);
	}
	boolean requestSwap(Employee employee, Day day, Week week) {
		ScheduleBuilder.requests.add("Requesting Swap: \n" + name + " with " + employee.name + " on " + day + " on Week " + week);
		return true;
	}
	boolean requestWipe(Day day, Week week) {
		ScheduleBuilder.requests.add("Requesting day off: \n" + name + " on " + day + " on Week " + week);
		return true;
	}
}
class PayStub{
	double hours, payRate;
	public PayStub(double hours, double payRate) {
		this.hours = hours;
		this.payRate = payRate;
	}
	double getAmount() {
		return hours * payRate;
	}
}
