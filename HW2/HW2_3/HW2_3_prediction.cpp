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
class regress;

//int calDST(int port, int startPier, int destPier);

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

bool night(string sTime) {
	Time parsedTime = parseTime(sTime);
	int intTime = (parsedTime.hour*60) + parsedTime.min;
	if(intTime <= 360 || intTime >= 1080) {
		return true;
	} else
		return false;
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
		string type;
		int port;
		int startPier;
		int destPier;
		int predWorkTime;
		int movingDST;

	public:
		Task(Ship* sPtr, string sTime, string type, int param1, int param2);
		//get ship info
		string getShipName() {
			return shipPtr->getShipName();
		};
		int getStartTime() {
			return startTime;
		};

		string getType() {
			return type;
		};
		int getPort() {
			return port;
		};
		int getPredWorkTime() {
			return predWorkTime;
		};
		int getMovingDST() {
			return movingDST;
		};

		//print ship info
		void printTaskInfo();
		int spendingTime(string sTime, string type, int startPier, int destPier);
};

//constructor
Task::Task(Ship* sPtr, string sTime, string aType, int param1, int param2) {
	Time parsedTime = parseTime(sTime);

	shipPtr =  sPtr;
	startTime = (parsedTime.hour*60) + parsedTime.min;
	type = aType;

	if(type=="I") {
		port = param1;
		startPier = 0;
		destPier = param2;


	} else if(type=="O") {
		port = param1;
		startPier = param2;
		destPier = 0;

	} else if(type=="T") {
		port = 0;
		startPier = param1;
		destPier = param2;
	}

	movingDST = calDST(port, startPier, destPier);
};

//print task information
void Task::printTaskInfo() {
	cout << shipPtr->getShipName() << "\t" << parseTime(startTime) << "\t" << type << "\t";

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

//int Task::spendingTime(string sTime, string type, int startPier, int destPier) {
//	if(type == "I") {
//		predWorkTime = a0 + a1*movingDst + a2*shipPtr->getShipWeight() + a3*shipPtr->getIsLoadedDanger() + a4*night(sTime);
//	} else if(type == "O") {
//		predWorkTime = b0 + b1*movingDst + b2*shipPtr->getShipWeight() + b3*shipPtr->getIsLoadedDanger() + b4*night(sTime);
//	} else if(type == "T") {
//		predWorkTime = c0 + c1*movingDst + c2*shipPtr->getShipWeight() + c3*shipPtr->getIsLoadedDanger() + c4*night(sTime);
//	}
//	return predWorkTime;
//}

//==================================================================================================================
//                                 Create Class TaskList
//==================================================================================================================


class TaskList {
	private:
		//array information
		Task **taskList;
		int taskCapacity;
		int taskNum;


	public:
		TaskList(int numOfTasks);
		~TaskList();
		//void addTask()
		void addTask(Ship* shipPtr, string sTime, string type, int param1, int param2);
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


//print each task's infomation in taskList
void TaskList::printTasks() {
	cout << "***********************************************" << endl;
	for(int i=0; i<taskNum; i++) {
		taskList[i]->printTaskInfo();
	}
	cout << "***********************************************" << endl;
}

//add task into taskList
void TaskList::addTask(Ship* shipPtr, string sTime, string type, int param1, int param2) {
	if(taskNum<taskCapacity) {
		Task* newTask = new Task(shipPtr, sTime, type, param1, param2);
		taskList[taskNum] = newTask;
		taskNum++;
	}
}



//int calDST(int port, int startPier, int destPier) {
//	int DST = 0;
//	int block = abs(startPier - destPier)/2;
//	bool odd = (abs(startPier - destPier)%2 == 0.5)? true : false;
//	if(port == 0)
//		DST = t2*block +t3*odd;
//	else
//		DST = t1 + t2*block +t3*odd;
//	return DST;
//}


//==================================================================================================================
//                                 Main Function
//==================================================================================================================

int main() {

	int m = 0;
	string shipFileName;
	string taskFileName;

	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	double coef0 = 0;
	double coef1 = 0;
	double coef2 = 0;
	double coef3 = 0;
	double coef4 = 0;
	double a0, a1, a2, a3, a4;
	double b0, b1, b2, b3, b4;
	double c0, c1, c2, c3, c4;


	string delimiter = ",";
	string line;
	cin >> line; 
	getline(cin, line, ',');


//	while(getline(cin, line)) {
//		size_t last = 0;
//		size_t next = 0;
//		//m
//		next = line.find(delimiter, last);
//		m = stoi(line.substr(last, next-last));
//		last = next + 1;
//		for(int i = 0; i < 3; i++) {
//			//coef0
//			next = line.find(delimiter, last);
//			coef0 = stod(line.substr(last, next-last));
//			last = next + 1;
//			//coef1
//			next = line.find(delimiter, last);
//			coef1 = stod(line.substr(last, next-last));
//			last = next + 1;
//			//coef2
//			next = line.find(delimiter, last);
//			coef2 = stod(line.substr(last, next-last));
//			last = next + 1;
//			//coef3
//			next = line.find(delimiter, last);
//			coef3 = stod(line.substr(last, next-last));
//			last = next + 1;
//			//coef4
//			next = line.find(delimiter, last);
//			coef4 = stod(line.substr(last, next-last));
//			last = next + 1;
//			if(i == 0) {
//				a0 = coef0;
//				a1 = coef1;
//				a2 = coef2;
//				a3 = coef3;
//				a4 = coef4;
//			} else if(i == 1) {
//				b0 = coef0;
//				b1 = coef1;
//				b2 = coef2;
//				b3 = coef3;
//				b4 = coef4;
//			} else {
//				c0 = coef0;
//				c1 = coef1;
//				c2 = coef2;
//				c3 = coef3;
//				c4 = coef4;
//			}
//
//		}
//		//t1
//		next = line.find(delimiter, last);
//		t1 = stoi(line.substr(last, next-last));
//		last = next + 1;
//		//t2
//		next = line.find(delimiter, last);
//		t2 = stoi(line.substr(last, next-last));
//		last = next + 1;
//		//t3
//		next = line.find(delimiter, last);
//		t3 = stoi(line.substr(last, next-last));
//		last = next + 1;
//		break;
//	}

	cin >> shipFileName >> taskFileName;

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
	shipList.printShips();

//	//read task information
//	infile.open(taskFileName);
//	while(getline(infile, line)) {
//		string shipName;
//		string startTime;
//		int workingTime1 = 0;
//		int workingTime2 = 0;
//		string type;
//		int param1 =0;
//		int param2 =0;
//
//		//string split
//		string delimiter = ",";
//		size_t pos = 0;
//
//		//shipName
//		pos = line.find(delimiter);
//		shipName = line.substr(0, pos);
//		line.erase(0, pos + delimiter.length());
//		//startTime
//		pos = line.find(delimiter);
//		startTime = line.substr(0, pos);
//		line.erase(0, pos + delimiter.length());
//
//
//		// deal with the transfer specific format
//		try {
//			//workingTime2
//			pos = line.find(delimiter);
//			workingTime2 = stoi(line.substr(0, pos));
//			line.erase(0, pos + delimiter.length());
//			//type
//			pos = line.find(delimiter);
//			type = line.substr(0, pos);
//			line.erase(0, pos + delimiter.length());
//
//		} catch(invalid_argument e) {
//			pos = line.find(delimiter);
//			workingTime2 = 0;
//			type = "T";
//			line.erase(0, pos + delimiter.length());
//		}
//
//		//param1
//		pos = line.find(delimiter);
//		param1 = stoi(line.substr(0, pos));
//		line.erase(0, pos + delimiter.length());
//		//param2
//		param2 = stoi(line);
//		Ship* shipPtr = shipList.getShipByShipName(shipName);
//		taskList.addTask(shipPtr, startTime, type, param1, param2);
//	}
//	infile.close();
//	taskList.printTasks();

	return 0;
}
