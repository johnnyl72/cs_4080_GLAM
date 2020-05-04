import time
start_time = time.time()

class Employee:
    def __init__(self, name,  payrate, employeeid, availablity):
        self.DaysOfWeek = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday','Saturday','Sunday']
        self.name = name
        self.payRate = payrate
        self.ID = employeeid
        self.availability = availablity
        self.schedule = [{self.DaysOfWeek[i]: availablity[i] for i in range(len(self.DaysOfWeek))}, {self.DaysOfWeek[i]: availablity[i] for i in range(len(self.DaysOfWeek))}]

    #Returns the Name of the Employee
    def getName(self):
        return self.name

    #Prints and Returns the amount that an Employee earns in a two week period
    def getWeeksPay(self):
        print(f"Amount: ${self.PayStub()}")
        return self.PayStub()

    #Returns the Hours that an Employee worked based on the days they work
    def getHours(self):
        counter = 0
        for week in self.getSchedule():
            for k,v in week.items():
                if v == 'WORKING':
                    counter += 1
        return 8 * counter

    #Creates the Employee's schedule based on their availability (switches the 0s & 1s to 'OFF' and 'WORKING' for each day in a two week period)
    def getSchedule(self):
        temp = self.schedule
        for week in self.schedule:
            for day, avail in week.items():
                if avail == 0:
                    temp[self.schedule.index(week)][day] = 'OFF'
                if avail == 1:
                    temp[self.schedule.index(week)][day] = 'WORKING'
        return temp

    #Prints an Employee's Schedule
    def printEmployeeSchedule(self):
        print(f"{self.name}'s Schedule")
        counter = 1
        for week in self.getSchedule():
            print(f'Week {counter}')
            print('+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+')
            for day,avail in week.items():
                print(f'| {day}: {avail}'.ljust(21), end=' ')
            print('|')
            print('+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+')
            counter += 1

    def getID(self):
        return self.employeeID

    def getAvailability(self):
        return self.availability

    def changeName(self, inputName):
        self.name = inputName

    #Calculates and returns the total Amount earned by the Employee in a 2 week period
    def PayStub(self):
        return self.getHours() * self.payRate



class ManagementEmployee(Employee):
    def wipeSchedule(self, employee1, day: str, week: int):
        employee1.schedule[week-1][day] = 0

    #Swaps the Schedule of two employees by taking in the day and week they want to change
    def swapSchedule(self, employee1, employee2, day:str, week:int):
        temp = employee1.schedule[week-1][day]
        employee1.schedule[week-1][day] = employee2.schedule[week-1][day]
        employee2.schedule[week-1][day] = temp



class LineWorkEmployee(Employee):
    def requestSwap(self, employee, day: str, week: int, requests):
        requests.append(f"Requesting Swap: \n{self.name} with {employee.name} on {day} on Week {week}")

    def requestWipe(self, day: str, week: int, requests):
        requests.append(f"Requesting day off: \n{self.name} on {day} on Week {week}")





'''SCHEDULE BUILDER'''

#Updates master schedule everytime a change is made
def updateSchedule(schedule,ListofEmployees):
    Week = 0
    for employee in reversed(ListofEmployees):
        for week in employee.schedule:
            temp = {**week}
            for key, value in temp.items():
                if value == 'WORKING':
                    schedule[Week][key] = employee.name
                elif value == 'OFF' and schedule[Week][key] == employee.name:
                    schedule[Week][key] = 'Empty'
            Week += 1
        Week = 0
    return schedule

#Generates a Master Schedule (list of dictionaries; each dictionary is 1 week and k,v is day,worker)
def GenerateSchedule(ListofEmployees):
    schedule = [{'Monday':'Empty', 'Tuesday':'Empty', 'Wednesday':'Empty', 'Thursday':'Empty', 'Friday':'Empty', 'Saturday':'Empty','Sunday':'Empty'},
                {'Monday':'Empty', 'Tuesday': 'Empty', 'Wednesday': 'Empty', 'Thursday': 'Empty', 'Friday': 'Empty', 'Saturday':'Empty','Sunday':'Empty'}]
    for employee in ListofEmployees:
        for w in employee.schedule:
            temp = {**w}
            for key, value in temp.items():
                for week in range(2):
                    if schedule[week][key] == 'Empty' and value == 1:
                        schedule[0][key] = employee.name
                        schedule[1][key] = employee.name

                    elif schedule[week][key] != employee.name and value == 1:
                        employee.schedule[0][key] = 0
                        employee.schedule[1][key] = 0
    return schedule

#Prints the Employee and their IDs
def printEmployeeList(ListofEmployees):
    print("Employee List")
    for employee in ListofEmployees:
        print(f"ID: {employee.ID}   Name: {employee.name}")

#View all Swap/Wipe requests Made
def viewRequests(requests):
    print('----------------------------------------------\nCurrent Requests\n')
    for each_request in requests:
        print(each_request)
    print('----------------------------------------------')

#Clear All Requests
def clearRequests(requests):
    requests = []
    print('Cleared all Requests!')

#Prints out current Master Schedule
def printMasterSchedule(schedule):
    print(' MASTER SCHEDULE')
    counter = 1
    for week in schedule:
        print(f'Week {counter}')
        print('+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+')
        for day, name in week.items():
            print(f'| {day}'.ljust(22), end = '')
        print('|')
        for name in week.values():
            print(f'| {name}'.ljust(22), end='')
        print('|')
        print('+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+')
        counter += 1




'''INPUTS FOR SCHEDULE BUILDER'''

if __name__ == "__main__":
    requests = []

    temp1 = [1,1,0,1,0,1,0]
    temp2 = [1,1,0,1,0,0,1]
    temp3 = [0,0,1,0,1,0,1]

    Bob = ManagementEmployee("Bob",100.0, 0, temp1)
    Janet = ManagementEmployee("Janet", 200.0, 1, temp2)
    Steven = LineWorkEmployee("Steven", 10, 2, temp3)

    ListofEmployees=[Bob, Janet, Steven]

    printEmployeeList(ListofEmployees)
    print()

    Schedule = GenerateSchedule(ListofEmployees)

    Bob.printEmployeeSchedule()
    Bob.getWeeksPay()
    print()

    Janet.printEmployeeSchedule()
    Janet.getWeeksPay()
    print()

    Steven.printEmployeeSchedule()
    Steven.getWeeksPay()
    print('\n')

    Steven.requestSwap(Bob, 'Wednesday', 1, requests)
    Steven.requestWipe('Friday', 1, requests)
    viewRequests(requests)
    Bob.swapSchedule(Bob, Steven, 'Wednesday', 1)
    Bob.wipeSchedule(Steven, 'Friday', 1)

    print("\n\nApproved Steven's Swap Request")
    print("Approved Steven's Day Off Request\n\n")

    print("NEW Schedule\n")
    Bob.printEmployeeSchedule()
    Janet.printEmployeeSchedule()
    Steven.printEmployeeSchedule()
    print("\n")

    updateSchedule(Schedule, ListofEmployees)

    printMasterSchedule(Schedule)

    print("--- %s seconds ---" % (time.time() - start_time))






















