#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//forward declaration
class Ship;
class ShipArray;
class Job;
class Port;


class Ship {
	protected:
		string id;
		int shipWeight;
		string nation;
		string captionName;
		string dangerItem;
	public:
		Ship(string id, int shipWeight, string nation, string captionName, string dangerItem);
		string getShipId() {
			return id;
		};
		int getShipWeight() {
			return shipWeight;
		};
		string getNation() {
			return nation;
		};
		string getCaptionName() {
			return captionName;
		};
		string getDangerItem() {
			return dangerItem;
		};

		void print();
};

Ship::Ship(string id, int shipWeight, string nation, string captionName, string dangerItem)
	: id(id), shipWeight(shipWeight), nation(nation), captionName(captionName),
	  dangerItem(dangerItem) {
}


void Ship::print()  {
	cout << this->id << ", ";
	cout << this->shipWeight  <<", ";
	cout << this->nation  <<", ";
	cout << this->captionName <<", ";
	cout << this->dangerItem << endl;
}


//====================================================================================
// Declare ShipArray to store ship
//====================================================================================
class ShipArray {
	protected:
		int capacity;
		int cnt;
		Ship** ShipPtr;
	public:
		ShipArray(int numOfShips);
		~ShipArray();
		bool add(string id, int shipWeight, string nation, string captionName, string dangerItem);
		Ship* getShipByShipName(string id);
		void print();
};

ShipArray::ShipArray(int numOfShips) {
	this -> cnt = 0;
	this -> capacity = numOfShips;
	this -> ShipPtr = new Ship* [this -> capacity];

	//initializer nullptr
	for(int i= 0; i< this->capacity; i++ ) {
		this->ShipPtr[i] = nullptr;
	}

}

ShipArray::~ShipArray() {
	for(int i = 0; i < this -> cnt; i++) {
		delete this -> ShipPtr[i];
	}
	delete [] this -> ShipPtr;
}

//add new Ship into shipList
bool ShipArray::add(string id, int shipWeight, string nation, string captionName, string dangerItem) {
	if(this -> cnt < this -> capacity) {
		this -> ShipPtr[this -> cnt] = new Ship(id, shipWeight, nation, captionName, dangerItem);
		this -> cnt ++;
		return true;
	} else
		return false;
}

void ShipArray::print() {
	cout << "***************************************" << endl;
	for(int i = 0; i < this -> cnt; i++ ) {
		this -> ShipPtr[i] -> print();

	}
	cout << "***************************************" << endl;
}

//search ship from shipList
Ship* ShipArray::getShipByShipName(string id) {
	for(int i=0; i< this-> cnt; i++) {
		if(this -> ShipPtr[i]-> getShipId().compare(id) == 0) {
			return ShipPtr[i];
		}
	}
	return nullptr;
}


//====================================================================================
// declare job and his children
//=============================================================================
class Job {
	protected:
		string id;
		string time;
		int optTime;
		string jobType;
		int port;
		int pier;
	public:
		Job(string id, string time, int optTime, string jobType, int port, int pier);
		void print();
		string getId();
		string getJobType();
		int getPort();
		int getPier();
		int getOptTime();
		int getAvlTime();

};

Job::Job(string id, string time, int optTime, string jobType, int port, int pier)
	: id(id), time(time), optTime(optTime), jobType(jobType), port(port), pier(pier) {

};


void Job::print() {
	cout << this->id << ", ";
	cout << this->time  <<", ";
	cout << this->optTime  <<", ";
	cout << this->jobType <<", ";
	cout << this->port <<", ";
	cout << this->pier << endl;

}

string Job::getId() {
	return this->id;
}

string Job::getJobType() {
	return this-> jobType;
}
int Job::getPort() {
	return this-> port;
}
int Job::getPier() {
	return this-> pier;
}

int Job::getOptTime() {
	return this-> optTime;
}

int Job::getAvlTime() {
	string shipAvlTime = this -> time ;
	stringstream ss;
	int hour, minute;
	char colon;
	ss << shipAvlTime; //first element is blank.
	ss >> hour >> colon >> minute;
	int totalMin = hour*60 + minute;
	return totalMin;
}


//====================================================================================

class Inbound : public Job {
	private:
	public:
		Inbound(string id, string time, int optTime, string jobType, int port, int pier);

};

Inbound::Inbound(string id, string time, int optTime, string jobType, int port, int pier)
	: Job(id, time, optTime, jobType, port, pier) {
};

class Outbound : public Job {
	private:
	public:
		Outbound(string id, string time, int optTime, string jobType, int port, int pier);

};

Outbound::Outbound(string id, string time, int optTime, string jobType, int port, int pier)
	: Job(id, time, optTime, jobType, port, pier) {
};


class Transfer : public Job {
	private:
	public:
		Transfer(string id, string time, int optTime, string jobType, int port, int pier);

};

Transfer::Transfer(string id, string time, int optTime, string jobType, int port, int pier)
	: Job(id, time, optTime, jobType, port, pier) {
};




//==========================================================================
// declare Class Port and use Polymorphism to store different type of objects
//==========================================================================

class Port {
	private:
		int memberCount = 0;
//        static const int maxMemNum = 2000;
//        Job* member[maxMemNum];
		vector<Job*> member;
	public:
		Port();
		~Port();
		void addInbound(string id, string time, int optTime, string jobType, int port, int pier);
		void addOutbound(string id, string time, int optTime, string jobType, int port, int pier);
		void addTransfer(string id, string time, int optTime, string jobType, int port, int pier);
		void printMember();
		int getMemberCount();
		Job getJob(int i);
		int getMemberSize();
		friend int portERTsorted(Port& Port);
		friend int portSPTsorted(Port& Port);

};

//==========================================================================

Port::Port() {

}

Port::~Port() {
	while(this->member.size() >0) {
		delete this->member.back();
		this->member.pop_back();

	}
}

void Port::addInbound(string id, string time, int optTime, string jobType, int port, int pier) {

	Inbound jobIn(id, time, optTime, jobType, port, pier);
	this->member.push_back(&jobIn);
	memberCount++;

}

void Port::addOutbound(string id, string time, int optTime, string jobType, int port, int pier) {

	Outbound jobOut(id, time, optTime, jobType, port, pier);
	this->member.push_back(&jobOut);
	memberCount++;

}

void Port::addTransfer(string id, string time, int optTime, string jobType, int port, int pier) {

	Transfer jobTrn(id, time, optTime, jobType, port, pier);
	this->member.push_back(&jobTrn);
	memberCount++;

}

void Port::printMember() {
	for(int i = 0; i < this->member.size(); i++) {
		this->member[i]->print();
	}
}

int Port::getMemberCount() {
	return this->memberCount;
}

Job Port::getJob(int i) {
	return *(this-> member[i]);
}

int Port::getMemberSize() {
	return this->member.size();
}

//==========================================================================
//  Fraction function
//==========================================================================

void parseShipInfo(string Path, ShipArray& sa) {
	string id, nation, captionName, dangerItem, weight;
	ifstream file;
	file.open(Path);
	if(file) {
		while(!file.eof()) {
			getline(file, id, ',');
			getline(file, weight, ',');
			getline(file, nation, ',');
			getline(file, captionName, ',');
			getline(file, dangerItem, '\n');
			int shipWeight = stoi(weight);
			sa.add(id, shipWeight, nation, captionName, dangerItem);

		}
		//sa.print();
		file.close();
	} else {
		cout << "read data error" << endl;
	}
}

void parseJobInfo(string Path, Port& Port1, Port& Port2) {
	string id, avlTime, OptTime, jobType, Port, Pier;
	ifstream file2;
	file2.open(Path);
	if(file2) {
		while(!file2.eof()) {
			getline(file2, id, ',');
			getline(file2, avlTime, ',');
			getline(file2, OptTime, ',');
			getline(file2, jobType, ',');
			getline(file2, Port, ',');
			getline(file2, Pier, '\n');
			int optTime = stoi(OptTime);
			int port = stoi(Port);
			int pier = stoi(Pier);
			//ja.add(id, avlTime, optTime, jobType, port, pier);
			if(jobType == "I") {
				if(port == 1) {
					Port1.addInbound(id, avlTime, optTime, jobType, port, pier);
				} else {
					Port2.addInbound(id, avlTime, optTime, jobType, port, pier);
				}
			} else if(jobType == "O") {
				if(port == 1) {
					Port1.addOutbound(id, avlTime, optTime, jobType, port, pier);
				} else {
					Port2.addOutbound(id, avlTime, optTime, jobType, port, pier);
				}
			} else {
				// Transfer TO DO.
			}
		}
		//ja.print();
      cout << "Port1 member" << endl;
//      Port1.printMember();
      cout << "Port2 member" << endl;
//      Port2.printMember();
		file2.close();
	} else {
		cout << "read data error" << endl;
	}
}
//===============================================================
// sorting functions
//===============================================================

bool sortByOptTime(Job& lhs,  Job& rhs) {
	return lhs.getOptTime() < rhs.getOptTime();
}

bool sortByAvlTime(Job& lhs,  Job& rhs) {
	return lhs.getAvlTime() < rhs.getAvlTime();
}

bool sortById(Job& lhs,  Job& rhs) {
	if(lhs.getId().compare(rhs.getId()) < 0)
		return true;
	else
		return false;
}

bool sortByERT( Job& lhs,  Job& rhs) {
	if(lhs.getAvlTime() == rhs.getAvlTime()) {
		if(lhs.getOptTime() == rhs.getOptTime()) {
			sortById(lhs, rhs);
		} else {
			sortByOptTime(lhs, rhs);
		}
	} else {
		sortByAvlTime(lhs, rhs);
	}
}


bool sortBySPT( Job& lhs,  Job& rhs) {
	if(lhs.getOptTime() == rhs.getOptTime()) {
		if(lhs.getAvlTime() == rhs.getAvlTime()) {
			sortById(lhs, rhs);
		} else {
			sortByAvlTime(lhs, rhs);
		}
	} else {
		sortByOptTime(lhs, rhs);
	}
}

void vectorPrint(vector<Job> &myvector) {
	cout << "myvector contains:" << endl;
	for(unsigned i=0; i< myvector.size(); i++)
		cout << "AvlTime: " << (myvector.at(i)).getAvlTime() << " OptTime: " << (myvector.at(i)).getOptTime()
		     << "ID: " << (myvector.at(i)).getId() << endl;
	cout << '\n';
}

int delayTotalTime(vector<Job> &myvector) {
	int curDelayTime = 0;
	int startTime = 0;
	int endTime = 0;
	int diff = 0;
	int fakeEndTime = 0;
	for(unsigned i=0; i< myvector.size(); i++) {
		if(i !=0 && myvector.at(i).getOptTime() == 0) {
			fakeEndTime = endTime - (myvector.at(i-1)).getOptTime();
			diff = fakeEndTime - (myvector.at(i)).getAvlTime();
			startTime = fakeEndTime;
//          cout << "startTime: " << startTime << endl;
			endTime = startTime + (myvector.at(i)).getOptTime();
//          cout << "endTime: " << endTime << endl;
			curDelayTime = curDelayTime + diff;
		} else {

			if(endTime <= myvector.at(i).getAvlTime()) {
				startTime = (myvector.at(i)).getAvlTime();
//              cout << "startTime: " << startTime << endl;
				endTime = startTime + (myvector.at(i)).getOptTime();
//              cout << "endTime: " << endTime << endl;
			} else {
				diff = endTime - (myvector.at(i)).getAvlTime();
				startTime = endTime;
//              cout << "startTime: " << startTime << endl;
				endTime = startTime + (myvector.at(i)).getOptTime();
//              cout << "endTime: " << endTime << endl;
				curDelayTime = curDelayTime + diff;
			}
		}
	}

	return curDelayTime;
}


int portERTsorted(Port& Port) {
	vector<Job> Joblist;
	for(int i =0; i < Port.getMemberCount(); i++) {
		Joblist.push_back(*(Port.member[i]));
	}
	sort((Joblist.begin()), (Joblist.end()), sortByERT);
//	cout << "ERT: " << endl;
//	vectorPrint(Joblist);
	int delay = delayTotalTime(Joblist);
	Joblist.clear();
	return delay;
}

int portSPTsorted(Port& Port) {
	vector<Job> Joblist2;
	for(int i =0; i < Port.getMemberCount(); i++) {
		Joblist2.push_back(*(Port.member[i]));
	}
	sort((Joblist2.begin()), (Joblist2.end()), sortBySPT);
//  cout << "SPT: " << endl;
//  vectorPrint(Joblist2);
	int delay = delayTotalTime(Joblist2);
	Joblist2.clear();
	return delay;
}


//==========================================================================
//  Main function
//==========================================================================

int main() {
	int pierNum = 0;
	cin >> pierNum;

	string shipPath = "";
	cin >> shipPath;

	string jobPath = "";
	cin >> jobPath;

	//count ship / job numbers
	ifstream infile(shipPath);
	int shipCnt = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') + 1;
	infile.close();

	infile.open(jobPath);
	int jobCnt = count(istreambuf_iterator<char>(infile), istreambuf_iterator<char>(), '\n') +1;
	infile.close();


	ShipArray sa(shipCnt);
	parseShipInfo(shipPath, sa);

	Port Port1;
	Port Port2;
	parseJobInfo(jobPath, Port1, Port2);

	// Sorting the Jobs in Port1 adn Port2
	int delayTimeERT = portERTsorted(Port1) + portERTsorted(Port2);
	int delayTimeSPT = portSPTsorted(Port1) + portSPTsorted(Port2);
	//cout <<"DelayTime: ";
	cout << delayTimeERT << " " << delayTimeSPT;

	return 0;
}
