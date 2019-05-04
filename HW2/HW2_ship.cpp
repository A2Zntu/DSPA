#include <iostream> 	//input, output
#include <string>
#include <sstream>		//read file
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

bool ertDebugMode = false;
bool sptDebugMode = false;

//forward declaration
class Ship;
class ShipList;
class Task;
class TaskList;
bool ertCompare(Task task1, Task task2);
bool sptCompare(Task task1, Task task2);


//Time struct
struct Time {
	int hour;
	int min;
};

//parse HH:MM string time to integer minutes formate
Time parseTime(string sTime) {
	string delimiter = ":";

	size_t pos = 0;
	string token;
	pos = sTime.find(delimiter);
	token = sTime.substr(0, pos);
	int hour  = stoi(token);
	sTime.erase(0, pos + delimiter.length());
	int minute = stoi(sTime);

	return {hour, minute};
}

//parse integer minutes formate time to HH:MM string time
string parseTime(int time) {
	string hour = ((time/60) <10) ? ("0"+to_string(time/60)) : to_string(time/60);
	string minute = ((time%60) <10) ? ("0"+to_string(time%60)) : to_string(time%60);
	return hour + ":" + minute;
}


//==================================================================================================================
//                                 Create Class Ship
//==================================================================================================================
class Ship {
	private:
		string shipName;
		int shipWeight;
		string countryName;
		string captainName;
		bool isLoadedDanger;
	public:
		//constructor
		Ship(string sName, int sWeight, string country, string cName, bool isDanger);
		//get ship information
		string getShipName() {
			return shipName;
		};
		int getShipWeight() {
			return shipWeight;
		};
		string getCountryName() {
			return countryName;
		};
		string getCaptainName() {
			return captainName;
		};
		bool getIsLoadedDanger() {
			return isLoadedDanger;
		};
		//print
		void printShipInfo();
};


Ship::Ship(string sName, int sWeight, string country, string cName, bool isDanger) {
	shipName = sName;
	shipWeight = sWeight;
	countryName = country;
	captainName = cName;
	isLoadedDanger = isDanger;
}


void Ship::printShipInfo() {
	cout << shipName << "\t" << shipWeight << "\t" << countryName << "\t" << captainName << "\t" << isLoadedDanger << endl;
}


//==================================================================================================================
//                                 Create Class ShipList
//==================================================================================================================

class ShipList {
	private:
		int shipCapacity;
		int shipNum;
		Ship **shipList;
	public:
		ShipList(int numOfShips);
		~ShipList();
		void addShip(string shipName, int shipWeight, string countryName, string captainName, bool isLoadedDanger);
		Ship* getShipByShipName(string shipName);
		void printShips();
};

//constructor
ShipList::ShipList(int numOfShips) {
	shipNum = 0;
	shipCapacity = numOfShips;
	shipList = new Ship*[numOfShips];
	//initialize nullptr
	for(int i=0; i<shipCapacity; i++) {
		shipList[i] = nullptr;
	}
}

//destructor
ShipList::~ShipList() {
	for(int i=0; i<shipNum; i++) {
		delete shipList[i];
		shipList[i] = nullptr;
	}
}

//print every ship's info in the list
void ShipList::printShips() {
	cout << "***************************************" << endl;
	for(int i=0; i<shipNum; i++)
		shipList[i]->printShipInfo();
	cout << "***************************************" << endl;
}

//add new Ship into shipList
void ShipList::addShip(string shipName, int shipWeight, string countryName, string captainName, bool isLoadedDanger) {
	if(shipNum<shipCapacity) {
		Ship* newShip = new Ship(shipName, shipWeight, countryName, captainName, isLoadedDanger);
		shipList[shipNum] = newShip;
		shipNum++;
	}
}

//search ship from shipList
Ship* ShipList::getShipByShipName(string shipName) {
	for(int i=0; i<shipNum; i++) {
		if(shipList[i]->getShipName().compare(shipName) == 0) {
			return shipList[i];
		}
	}
	return nullptr;
}

//==================================================================================================================
//                                 Create Class Task
//==================================================================================================================
class Task {
	private:
		Ship* shipPtr;
		int startTime;
		int portWorkingTime;
		int pierWorkingTime;
		string type;
		int port;
		int startPier;
		int destPier;
		int realStartTime;
		int avlStartTime;
	public:
		Task(Ship* sPtr, string sTime, int wTime1, int wTime2, string type, int param1, int param2);
		//get ship info
		string getShipName() {
			return shipPtr->getShipName();
		};
		int getStartTime() {
			return startTime;
		};
		int getPortWorkingTime() {
			return portWorkingTime;
		};
		int getPierWorkingTime() {
			return pierWorkingTime;
		};
		int getWorkTime() {
			return (portWorkingTime + pierWorkingTime);
		};
		string getType() {
			return type;
		};
		int getPort() {
			return port;
		};
		int getRealStartTime() {
			return realStartTime;
		}
		int getRealEndTime() {
			return realStartTime + portWorkingTime;
		}

		int getWaitingTime() {
			return realStartTime - avlStartTime;
		}
		
		int getAvlStartTime(){
			return avlStartTime; 
		}
		//set ship info
		void setRealStartTime(int rTime) {
			realStartTime = rTime;
		}

		//print ship info
		void printTaskInfo();
};

//constructor
Task::Task(Ship* sPtr, string sTime, int wTime1, int wTime2, string aType, int param1, int param2) {
	Time parsedTime = parseTime(sTime);

	shipPtr =  sPtr;
	startTime = (parsedTime.hour*60) + parsedTime.min;

	type = aType;
	realStartTime = 0;
	avlStartTime = startTime;

	if(type=="I") {
		portWorkingTime = wTime1;
		pierWorkingTime = wTime2;
		port = param1;
		startPier = 0;
		destPier = param2;
		realStartTime = 0;

	} else if(type=="O") {
		portWorkingTime = wTime2;
		pierWorkingTime = wTime1;
		port = param1;
		startPier = param2;
		destPier = 0;
		realStartTime = 0;
		avlStartTime = startTime + pierWorkingTime;

	} else if(type=="T") {
		portWorkingTime = wTime2;
		pierWorkingTime = wTime1;
		port = 0;
		startPier = param1;
		destPier = param2;
		realStartTime = startTime;
	}
};

//print task information
void Task::printTaskInfo() {
	cout << shipPtr->getShipName() << "\t" << parseTime(startTime) << "\t" << portWorkingTime << "\t"
	     << pierWorkingTime << "\t" << parseTime(avlStartTime) << "\t" << type << "\t";
	cout << parseTime(realStartTime) << "\t" << parseTime(realStartTime + portWorkingTime) << "\t" ;
	cout << realStartTime - avlStartTime  << endl;

	/*if(type=="I")
	{
		cout << port << "\t" << destPier << endl;
	}
	else if(type=="O")
	{
		cout << port << "\t" << startPier << endl;
	}
	else if(type=="T")
	{
		cout << startPier << "\t" << destPier << endl;
	}  */
}

//==================================================================================================================
//                                 Create Class TaskList
//==================================================================================================================


class TaskList {
	private:
		//array information
		Task **taskList;
		int taskCapacity;
		int taskNum;

		//function
		void swap(Task** swapList, int i, int j);
		bool ertCompare(Task task1, Task task2);
		bool sptCompare(Task task1, Task task2);
	public:
		TaskList(int numOfTasks);
		~TaskList();
		//void addTask()
		void addTask(Ship* shipPtr, string sTime, int wTime1, int wTime2, string type, int param1, int param2);


		int getERT2DelayTime();
		int getSPTDelayTime();

		void printTasks();

};

//constructor: create array of task
TaskList::TaskList(int numOfTasks) {
	taskNum = 0;
	taskCapacity = numOfTasks;
	taskList = new Task*[numOfTasks];
}

//destructor: delete task in taskList
TaskList::~TaskList() {
	for(int i=0; i<taskNum; i++) {
		delete taskList[i];
		taskList[i] = nullptr;
	}
}

//swap task
void TaskList::swap(Task** swapList, int i, int j) {
	Task* temp = swapList[i];
	swapList[i] = swapList[j];
	swapList[j] = temp;
}

//print each task's infomation in taskList
void TaskList::printTasks() {
	cout << "***********************************************" << endl;
	for(int i=0; i<taskNum; i++) {
		taskList[i]->printTaskInfo();
	}
	cout << "***********************************************" << endl;
}

//add task into taskList
void TaskList::addTask(Ship* shipPtr, string sTime, int wTime1, int wTime2, string type, int param1, int param2) {
	if(taskNum<taskCapacity) {
		Task* newTask = new Task(shipPtr, sTime, wTime1, wTime2, type, param1, param2);
		taskList[taskNum] = newTask;
		taskNum++;
	}
}

//==================================================================================================================
//                                 Calculate ERT Delay Time
//==================================================================================================================


//correct ERT algorithm
int TaskList::getERT2DelayTime() {
	//shallow copy taskList
	Task **sortedList = new Task*[taskNum];
	for(int i=0; i<taskNum; i++) {
		sortedList[i] = taskList[i];
	}

	//sort
	for(int i=0; i<taskNum; i++) {
		for(int j=i+1; j<taskNum; j++) {
			if(!ertCompare(*sortedList[i],*sortedList[j])) {
				swap(sortedList, i, j);
			}
		}
	}

	//calculate waiting time
	int totalWaitingTime = 0;

	//count
	int port1Count =0;
	int port2Count =0;
	for(int i=0; i<taskNum; i++) {
		if(sortedList[i]->getPort()==1)
			port1Count++;
		else if(sortedList[i]->getPort()==2)
			port2Count++;
	}

	Task** port1Task = new Task*[port1Count];
	Task** port2Task = new Task*[port2Count];

	//reset to zero
	port1Count =0;
	port2Count =0;
	Task* curTask;
	for(int i=0; i<taskNum; i++) {
		curTask = sortedList[i];

		//skip T type task
		if(curTask->getType()=="T")
			continue;

		int portNum = curTask->getPort();

		//empty: directly insert
		if(portNum == 1 && port1Count== 0) {
			curTask->setRealStartTime(curTask->getAvlStartTime());
			port1Task[port1Count] = curTask;
			port1Count++;
		} else if(portNum == 2 && port2Count== 0) {
			curTask->setRealStartTime(curTask->getAvlStartTime());
			port2Task[port2Count] = sortedList[i];
			port2Count++;
		}
		//non empty
		else if(portNum == 1) {

			//head: waiting time = 0; The case will move the (0, 1, ... n ) task backward;
			if(curTask->getAvlStartTime() + curTask->getPortWorkingTime() <= port1Task[0]->getRealStartTime()) {
				//move and insert
				for(int j=port1Count; j>0; j--) {
					port1Task[j] = port1Task[j-1];
				}
				curTask->setRealStartTime(curTask->getAvlStartTime());
				port1Task[0] = curTask;
				port1Count++;
			} else {
				//body
				bool isFound = false;
				//find insertion point
				for(int j=1; j<port1Count; j++) {
					//
					if(max(curTask->getAvlStartTime() ,port1Task[j-1]->getRealEndTime()) + curTask->getPortWorkingTime() <= port1Task[j]->getRealStartTime()) {

						//move
						for(int k=port1Count; k>j; k--) {
							port1Task[k] = port1Task[k-1];
						}
						//insert
						curTask->setRealStartTime(max(curTask->getAvlStartTime(), port1Task[j-1]->getRealEndTime()));
						port1Task[j] = curTask;

						//add waiting time
						totalWaitingTime += port1Task[j]->getWaitingTime();

						port1Count++;
						isFound = true;
						break;
					}
				}

				//tail if can't find an insertion point, then put it to the end;
				if(!isFound) {
					//insert
					curTask->setRealStartTime(max(curTask->getAvlStartTime(), port1Task[port1Count-1]->getRealEndTime()));
					port1Task[port1Count] = curTask;

					//add waiting time
					totalWaitingTime += port1Task[port1Count]->getWaitingTime();

					port1Count++;
				}
			}
		} else if(portNum == 2) {

			//head: waiting time = 0
			if(curTask->getAvlStartTime() + curTask->getPortWorkingTime() <= port2Task[0]->getRealStartTime()) {
				//move and insert
				for(int j=port2Count; j>0; j--) {
					port2Task[j] = port2Task[j-1];
				}
				curTask->setRealStartTime(curTask->getAvlStartTime());
				port2Task[0] = curTask;
				port2Count++;
			} else {
				//find insertion point (if not found: insert at tail)
				int pos = port2Count;
				bool isFound = false;
				for(int j=1; j<port2Count; j++) {
					//find enough space
					if(max(curTask->getAvlStartTime() ,port2Task[j-1]->getRealEndTime()) + curTask->getPortWorkingTime() <= port2Task[j]->getRealStartTime()) {
						isFound = true;
						pos = j;
						break;
					}
				}

				//body
				if(isFound) {
					//move
					for(int k=port2Count; k>pos; k--) {
						port2Task[k] = port2Task[k-1];
					}
				}

				//insert
				curTask->setRealStartTime(max(curTask->getAvlStartTime(), port2Task[pos-1]->getRealEndTime()));
				port2Task[pos] = curTask;

				//add waiting time
				totalWaitingTime += curTask->getWaitingTime();

				port2Count++;
			}
		}

		//debug message
		if(ertDebugMode) {
			cout << "Port " << curTask->getPort() << endl;
			cout << "NAME" << "\t" << "startT" << "\t" << "PortT"  << "\t" << "PierT" << "\t"
			     << "AvlST" << "\t"<< "type" << "\t" << "realT" << "\t" << "endT" << "\t" << "waitT" << endl;
			curTask->printTaskInfo();
			cout << "---------------------PORT 1---------------------------" << endl;
			for(int p=0; p<port1Count; p++) {
				port1Task[p]->printTaskInfo();
			}
			cout << "---------------------PORT 2---------------------------" << endl;
			for(int p=0; p<port2Count; p++) {
				port2Task[p]->printTaskInfo();
			}
			cout << "Accu waiting Time: " << totalWaitingTime << endl << endl;
		}

	}
	return totalWaitingTime;
}


//==================================================================================================================
//                                 Calculate SPT Delay Time
//==================================================================================================================

int TaskList::getSPTDelayTime() {

	//shallow copy taskList
	Task **sortedList = new Task*[taskNum];
	for(int i=0; i<taskNum; i++) {
		sortedList[i] = taskList[i];
	}

	//sort
	for(int i=0; i<taskNum; i++) {
		for(int j=i+1; j<taskNum; j++) {
			if(!sptCompare(*sortedList[i],*sortedList[j])) {
				swap(sortedList, i, j);
			}
		}
	}

	//calculate waiting time
	int totalWaitingTime = 0;

	//count
	int port1Count =0;
	int port2Count =0;
	for(int i=0; i<taskNum; i++) {
		if(sortedList[i]->getPort()==1)
			port1Count++;
		else if(sortedList[i]->getPort()==2)
			port2Count++;
	}

	Task** port1Task = new Task*[port1Count];
	Task** port2Task = new Task*[port2Count];

	//reset to zero
	port1Count =0;
	port2Count =0;

	Task* curTask;
	for(int i=0; i<taskNum; i++) {
		curTask = sortedList[i];

		//skip T type task
		if(curTask->getType()=="T")
			continue;

		int portNum = curTask->getPort();

		//empty: directly insert
		if(portNum == 1 && port1Count== 0) {
			curTask->setRealStartTime(curTask->getAvlStartTime());
			port1Task[port1Count] = curTask;
			port1Count++;
		} else if(portNum == 2 && port2Count== 0) {
			curTask->setRealStartTime(curTask->getAvlStartTime());
			port2Task[port2Count] = sortedList[i];
			port2Count++;
		}
		//non empty
		else if(portNum == 1) {

			//head: waiting time = 0
			if(curTask->getAvlStartTime() + curTask->getPortWorkingTime() <= port1Task[0]->getRealStartTime()) {
				//move and insert
				for(int j=port1Count; j>0; j--) {
					port1Task[j] = port1Task[j-1];
				}
				curTask->setRealStartTime(curTask->getAvlStartTime());
				port1Task[0] = curTask;
				port1Count++;
			} else {
				//body
				bool isFound = false;
				//find insertion point
				for(int j=1; j<port1Count; j++) {
					//
					if(max(curTask->getAvlStartTime() ,port1Task[j-1]->getRealEndTime()) + curTask->getPortWorkingTime() <= port1Task[j]->getRealStartTime()) {

						//move
						for(int k=port1Count; k>j; k--) {
							port1Task[k] = port1Task[k-1];
						}
						//insert
						curTask->setRealStartTime(max(curTask->getAvlStartTime(), port1Task[j-1]->getRealEndTime()));
						port1Task[j] = curTask;

						//add waiting time
						totalWaitingTime += port1Task[j]->getWaitingTime();

						port1Count++;
						isFound = true;
						break;
					}
				}

				//tail
				if(!isFound) {
					//insert
					curTask->setRealStartTime(max(curTask->getAvlStartTime(), port1Task[port1Count-1]->getRealEndTime()));
					port1Task[port1Count] = curTask;

					//add waiting time
					totalWaitingTime += port1Task[port1Count]->getWaitingTime();

					port1Count++;
				}
			}
		} else if(portNum == 2) {

			//head: waiting time = 0
			if(curTask->getAvlStartTime() + curTask->getWorkTime() <= port2Task[0]->getRealStartTime()) {
				//move and insert
				for(int j=port2Count; j>0; j--) {
					port2Task[j] = port2Task[j-1];
				}
				curTask->setRealStartTime(curTask->getAvlStartTime());
				port2Task[0] = curTask;
				port2Count++;
			} else {
				//find insertion point (if not found: insert at tail)
				int pos = port2Count;
				bool isFound = false;
				for(int j=1; j<port2Count; j++) {
					//find enough space
					if(max(curTask->getAvlStartTime() ,port2Task[j-1]->getRealEndTime()) + curTask->getPortWorkingTime() <= port2Task[j]->getRealStartTime()) {
						isFound = true;
						pos = j;
						break;
					}
				}

				//body
				if(isFound) {
					//move
					for(int k=port2Count; k>pos; k--) {
						port2Task[k] = port2Task[k-1];
					}
				}

				//insert
				curTask->setRealStartTime(max(curTask->getAvlStartTime(), port2Task[pos-1]->getRealEndTime()));
				port2Task[pos] = curTask;

				//add waiting time
				totalWaitingTime += curTask->getWaitingTime();

				port2Count++;
			}
		}

		if(sptDebugMode) {
			cout << "Port " << curTask->getPort() << endl;
			cout << "NAME" << "\t" << "startT" << "\t" << "PortT"  << "\t" << "PierT" << "\t"
			     << "AvlST" << "\t"<< "type" << "\t" << "realT" << "\t" << "endT" << "\t" << "waitT" << endl;
			curTask->printTaskInfo();
			cout << "---------------------PORT 1---------------------------" << endl;
			for(int p=0; p<port1Count; p++) {
				port1Task[p]->printTaskInfo();
			}
			cout << "---------------------PORT 2---------------------------" << endl;
			for(int p=0; p<port2Count; p++) {
				port2Task[p]->printTaskInfo();
			}
			cout << "Accu waiting Time: " << totalWaitingTime << endl << endl;
		}

	}
	return totalWaitingTime;
}


//==================================================================================================================
//                                 Develope the ERT and SPT Algorithm
//==================================================================================================================



//true: task1 is prior to task2, false: task2 is prior to task1
bool TaskList::ertCompare(Task task1, Task task2) {
	//compare start time
	if(task1.getStartTime() < task2.getStartTime())
		return true;
	else if(task1.getStartTime() > task2.getStartTime())
		return false;
	//compare working duration time
	if(task1.getWorkTime() < task2.getWorkTime())
		return true;
	else if(task1.getWorkTime() > task2.getWorkTime())
		return false;
	//compare ship name
	if(task1.getShipName().compare(task2.getShipName()) <0)
		return true;
	else
		return false;
}

//true: task1 is prior to task2, false: task2 is prior to task1
bool TaskList::sptCompare(Task task1, Task task2) {
	//compare working duration time
	if(task1.getWorkTime() < task2.getWorkTime())
		return true;
	else if(task1.getWorkTime() > task2.getWorkTime())
		return false;
	//compare start time
	if(task1.getStartTime() < task2.getStartTime())
		return true;
	else if(task1.getStartTime() > task2.getStartTime())
		return false;
	//compare ship name
	if(task1.getShipName().compare(task2.getShipName()) <0)
		return true;
	else
		return false;
}

//true: task1 is prior to task2, false: task2 is prior to task1
bool realStartTimeCompare(Task task1, Task task2) {
	//
	if(task1.getRealStartTime() < task2.getRealStartTime())
		return true;
	else
		return false;

}

//==================================================================================================================
//                                 Main Function
//==================================================================================================================

int main() {

	int m =0;
	string shipFileName;
	string taskFileName;
	cin >> m >> shipFileName >> taskFileName;

	//count ship / task numbers
	ifstream infile(shipFileName);
	int shipCount = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') +1;
	infile.close();

	infile.open(taskFileName);
	int taskCount = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') +1;
	infile.close();

	//create class
	ShipList shipList(shipCount);
	TaskList taskList(taskCount);

	string line;
	//read ship information
	infile.open(shipFileName);
	while(getline(infile, line)) {
		string shipName;
		int shipWeight=0;
		string countryName;
		string captainName;
		bool isLoadedDanger=false;

		string delimiter = ",";
		size_t last = 0;
		size_t next = 0;
		//shipName
		next = line.find(delimiter, last);
		shipName = line.substr(last, next-last);
		last = next + 1;
		//shipWeight
		next = line.find(delimiter, last);
		shipWeight = stoi(line.substr(last, next-last));
		last = next + 1;
		//countryName
		next = line.find(delimiter, last);
		countryName = line.substr(last, next-last);
		last = next + 1;
		//captainName
		next = line.find(delimiter, last);
		captainName = line.substr(last, next-last);
		last = next + 1;
		//isLoadedDanger
		isLoadedDanger = (line.substr(last)=="Y") ? true : false;

		//create ship
		shipList.addShip(shipName, shipWeight, countryName, captainName, isLoadedDanger);
	}
	infile.close();
	//shipList.printShips();

	//read task information
	infile.open(taskFileName);
	while(getline(infile, line)) {
		string shipName;
		string startTime;
		int workingTime1 = 0;
		int workingTime2 = 0;
		string type;
		int param1 =0;
		int param2 =0;

		//string split
		string delimiter = ",";
		size_t pos = 0;

		//shipName
		pos = line.find(delimiter);
		shipName = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		//startTime
		pos = line.find(delimiter);
		startTime = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		//workingTime1
		pos = line.find(delimiter);
		workingTime1 = stoi(line.substr(0, pos));
		line.erase(0, pos + delimiter.length());

		// deal with the transfer specific format
		try {
			//workingTime2
			pos = line.find(delimiter);
			workingTime2 = stoi(line.substr(0, pos));
			line.erase(0, pos + delimiter.length());
			//type
			pos = line.find(delimiter);
			type = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

		} catch(invalid_argument e) {
			pos = line.find(delimiter);
			workingTime2 = 0;
			type = "T";
			line.erase(0, pos + delimiter.length());
		}

		//param1
		pos = line.find(delimiter);
		param1 = stoi(line.substr(0, pos));
		line.erase(0, pos + delimiter.length());
		//param2
		param2 = stoi(line);
		Ship* shipPtr = shipList.getShipByShipName(shipName);
		taskList.addTask(shipPtr, startTime, workingTime1, workingTime2, type, param1, param2);
	}
	infile.close();
	//taskList.printTasks();

	//result
	cout << taskList.getERT2DelayTime() << "," <<taskList.getSPTDelayTime() << endl;


}
