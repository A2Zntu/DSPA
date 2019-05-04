#include<iostream>
#include<vector>
#include<iomanip>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

const int VERY_LARGE = 999999;

bool debugAddNodes = false;
bool debugGetNext = false;
bool debugCurPlusOne = false;
bool debugPathQueue = false;
bool debugMaxFlow = false;



//=====================================================================
//                      Class Node
//=====================================================================

class Node {
	public:
		string symbol;
		int Cnt;

};

vector<Node> node_list;


void vectorPrint(vector<Node>& ve) {
	cout << "Vector Print" << endl;
	for(int i = 0; i < ve.size(); i++)
		cout << ve[i].symbol << " " << ve[i].Cnt << endl;
}

int str2int(string aNode) {
	for(int i = 0; i < node_list.size(); i++) {
		if(node_list[i].symbol == aNode)
			return node_list[i].Cnt;
	}
	cout << "Can't turn string to int!" << endl;
}


string int2str(int num) {
	return node_list[num].symbol;
}


bool stringCompare(int lhs, int rhs) {
	string LhsTailStr = int2str(lhs);
	string RhsTailStr = int2str(rhs);
	if(LhsTailStr.compare(RhsTailStr) < 0)
		return true;
	else
		return false;
}

//=====================================================================
//                      Class Path
//=====================================================================
class Path {
	private:
		vector<int> nodes;
		int capacity;
	public:
		Path();
		Path(int aNode);
		Path(Path aShorterPath, int aNode, int capacity);
		int getTail();
		int getCapacity();
		void print();
		void reset();
		int getNodeSize();
		int getNode(int order);
		vector<int> getNodes();
		void strPrint();
		bool operator==(const Path& rhs) const;
};
// constructor of Path
Path::Path() : capacity(VERY_LARGE) {
}

Path::Path(int aNode) : capacity(VERY_LARGE) {
	this->nodes.push_back(aNode);
}

Path::Path(Path aShorterPath, int aNode, int capacity) {
	for(int i = 0; i < aShorterPath.nodes.size(); i++)
		this->nodes.push_back(aShorterPath.nodes[i]);
	this->nodes.push_back(aNode);
	this->capacity = capacity;
}
// constructor of Path

void Path::print() {
	if(this->nodes.size() == 0)
		cout << "<empty>" << endl;
	else {
		cout << "Path Route: ";
		for(int i = 0; i < this->nodes.size() - 1; i++)
			cout << this->nodes[i] << "-> ";
		cout << this->nodes.back() << ";" << endl;
		cout << "Path Capacity: " << this->capacity << endl;
	}
}

void Path::strPrint() {
	if(this->nodes.size() != 0) {
		for(int i = 0; i < this->nodes.size() - 1; i++)
			cout << int2str(this->nodes[i]) << ",";
		cout << int2str(this->nodes.back()) << ";" ;
		cout << this->capacity;
	} else
		cout << -1;
}



int Path::getTail() {
	return this->nodes.back();
}

int Path::getCapacity() {
	return this->capacity;
}

void Path::reset() {
	this -> nodes.clear();
	this -> capacity = VERY_LARGE;
}

int Path::getNodeSize() {
	return this -> nodes.size();
}


int Path::getNode(int order) {
	return this -> nodes[order];
}

vector<int> Path::getNodes() {
	return this->nodes;
}


bool Path::operator==(const Path& rhs) const {
	return equal(rhs.nodes.begin(), rhs.nodes.end(), this ->nodes.begin());
}

//=====================================================================
//                      Class Network
//=====================================================================


class Network {
	private:
		int n;
		int** resCap; // adjecent matrix
	public:
		Network(int n);
		void adjustArcCap(int node1, int node2, int capacity);
		void print();
		static bool sortByRules(Path& lhs, Path& rhs);
		vector<Path> getNextWithResCap(Path aPath);
		Path getAnAugmentingPath();
		void sendOnce(Path anAugPath);
		int maxFlow(Network &emptyNetwork);
		~Network();


};

Network::Network(int n) : n(n) {
	this->resCap = new int*[this->n];
	for(int i = 0; i < this->n; i++) {
		this->resCap[i] = new int[this->n];
		for(int j = 0; j < this->n; j++)
			this->resCap[i][j] = 0; // initialize

	}
}

void Network::adjustArcCap(int node1, int node2, int capacity) {
	this->resCap[node1][node2] += capacity;
}

void Network::print() {
	for(int i = 0; i < this->n; i++) {
		for(int j = 0; j < this->n; j++)
			cout << setw(2) << this->resCap[i][j] << " ";
		cout << endl;
	}
}

bool Network::sortByRules(Path& lhs, Path& rhs) {
	if(lhs.getCapacity() == rhs.getCapacity())
		return stringCompare(lhs.getTail(),  rhs.getTail());
	else
		return lhs.getCapacity() > rhs.getCapacity();
}


// input: a path of length L
// output: a vector of paths of length L + 1
// precondition: aPath is really a path in this network
vector<Path> Network::getNextWithResCap(Path aPath) {
	vector<Path> longerPaths; // mutiple paths in a vector
	int tail = aPath.getTail();


	for(int i = 0; i < this->n; i++) {
		if(this->resCap[tail][i] > 0) { // connect to next valid connected vertex
			int oldCap = aPath.getCapacity();
			int newCap = oldCap;
			if(this->resCap[tail][i] < oldCap) // refresh the capacity
				newCap = this->resCap[tail][i]; // new capacity would be bottle neck
			Path p(aPath, i, newCap);

			longerPaths.push_back(p); // a vector contains mutiple valid paths
		}
	}
	sort((longerPaths.begin()), (longerPaths.end()), Network::sortByRules);
	if(debugGetNext) {
		for(int i = 0; i < longerPaths.size(); i++)
			longerPaths[i].print();
		cout << "=====================" << endl;
	}

	return longerPaths;
}


// this function does not check whether a path visits a visited node
Path Network::getAnAugmentingPath() {
	// find an augmenting path through BFS
	vector<Path> pathQueue;
	Path start(0);
	pathQueue.push_back(start);

	Path anAugmentingPath;
	bool keepGoing = true;
	while(keepGoing && pathQueue.size() > 0) {
		Path cur = pathQueue.front();
		pathQueue.erase(pathQueue.begin());
		vector<Path> curPlusOne = this->getNextWithResCap(cur); // the next nodes may be a vector of paths
//		cout << "\nnow i am debugging\n";
//		for(int i = 0; i < curPlusOne.size(); i++) {
//			curPlusOne[i].print();
//		}
//		cout << "debugging over\n";

		// the new Queue like | [a, b, c], [a, b, d], [a, c, d] .....
		// deal with the Queue;
		// delete the repeated nodes; get next nodes;
		// The first for loop is for chceking which curPlusOne nees to append
		// The Second for loop is to append the non-repeated Path
		int sizeOfCurQueue = curPlusOne.size();
		int visited[sizeOfCurQueue] = {0};

		if(curPlusOne.empty() == false) {
			for(int i = 0; i < sizeOfCurQueue; i++) {
				if(debugCurPlusOne) {
					cout << endl;
					cout << "curPlusOne: " << endl;
					cout << "===================================" << endl;
					curPlusOne[i].print();

				}
				// Check whether the tail is a visited node
				for(int j = 0; j < curPlusOne[i].getNodeSize() - 1; j++) {
					if(curPlusOne[i].getTail() == curPlusOne[i].getNode(j)) {
//						cout << "\nfind equal: ";
//						curPlusOne[i].print();
//						cout << "after curplusone size: " << curPlusOne.size() << endl;
						visited[i] = 1;
					}
				}
			}

			for(int i = 0; i < sizeOfCurQueue; i++) {
				// Find out the destination!!
				// if the final nodes never visited then we can consider.
				if(visited[i] != 1) {
					if(curPlusOne[i].getTail() == n - 1) {
						// we assume the final answer could be found in here
						// need to rewrite, if we can't find a path.
						//cout << "\nFinally get an augmenting Path! \n";
						anAugmentingPath = curPlusOne[i];
						keepGoing = false;
						break;
					} else {
						pathQueue.push_back(curPlusOne[i]);
					}

				}

			}
		}

		// print out the current Queue
		if(debugPathQueue) {
			cout << "----------------------------------------" << endl;
			cout << "Queue: " << endl;
			for(int k = 0; k < pathQueue.size(); k++)
				pathQueue[k].print();
			cout << "----------------------------------------" << endl;
		}

	}
	return anAugmentingPath;
}


void Network::sendOnce(Path anAugPath) {
	int flow = anAugPath.getCapacity();
	vector<int> nodes = anAugPath.getNodes();
	int nodeCnt = nodes.size();
	for(int i = 0; i < nodes.size() - 1; i++) {
		// forward: send something and decrease capacity
		this->adjustArcCap(nodes[i], nodes[i + 1], -flow);
		// backward: add capacity
		this->adjustArcCap(nodes[i + 1], nodes[i], flow);
	}
}


int Network::maxFlow(Network &emptyNetwork) {
	Path anAugPath = this->getAnAugmentingPath();
	anAugPath.strPrint();
	if(debugMaxFlow) {
		cout << "First Augmenting Path: " << endl;
		anAugPath.print();
	}

	int maxFlowAmount = 0;
	int iteration = 0;

	while(anAugPath.getCapacity() < VERY_LARGE) { // if capacity == VERY_LARGE which means the anAugPath is an empty path, then stop.
		iteration ++;
		maxFlowAmount += anAugPath.getCapacity();
		this->sendOnce(anAugPath);
		emptyNetwork.sendOnce(anAugPath);

		// Get a new augmenting path again!

		if(debugMaxFlow) {
			cout << "++++++++++++++++ net +++++++++++++++++++" << endl;
			this->print();
			cout << "================= EmptyNetWork =========" << endl;
			emptyNetwork.print();
			cout << "The " << iteration << " Augmenting Path: " << endl;

		}
		anAugPath = this->getAnAugmentingPath();

		anAugPath.strPrint();
	}

	// clear positive values; flip negative values
	for(int i = 0; i < emptyNetwork.n; i++) {
		for(int j = 0; j < emptyNetwork.n; j++) {
			if(emptyNetwork.resCap[i][j] > 0)
				emptyNetwork.resCap[i][j] = 0;
			else if(emptyNetwork.resCap[i][j] < 0)
				emptyNetwork.resCap[i][j] *= -1;
		}
	}

	return maxFlowAmount;
}




Network::~Network() {
	for(int i = 0; i < this->n; i++)
		delete [] resCap[i];
	delete [] resCap;
}



//=====================================================================
//                      Main Function
//=====================================================================



int main() {
	char c;
	int n = 0, m = 0;
	cin >> n >> c >> m;
	// initialize an vocabulary array

	string nodesString;
	string delimiter = ",";
	size_t last = 0;
	size_t next = 0;

	cin >> nodesString;
	for (int i = 0; i< n; i++) {
		Node temp;
		string voc;
		next = nodesString.find(delimiter, last);
		voc = nodesString.substr(last, next-last);
		last = next + 1;
		temp.symbol = voc;
		temp.Cnt = i;
		node_list.push_back(temp);
	}

	cin.ignore();
	Network net(n);
	string line;
	while(getline(cin, line)) {

		string u, v, cap;
		int capacity = 0;
		int startNode = 0, endNode = 0;
		size_t last = 0;
		size_t next = 0;
		string delimiter = ",";

		next = line.find(delimiter, last);
		u = line.substr(last, next-last);
		last = next + 1;
		startNode = str2int(u);


		next = line.find(delimiter, last);
		v = line.substr(last, next-last);
		last = next + 1;
		endNode = str2int(v);

		cap = line.substr(last);
		capacity = stoi(cap);

		if(debugAddNodes) {
			cout << "capacity: " << capacity << endl;
			cout << "u: " << u << "-> " << startNode << endl;
			cout << "v: " << v << "-> " << endNode << endl;
			cout << "=====================================" << endl;

		}
		net.adjustArcCap(startNode, endNode, capacity);
		if(cin.eof())
			break;
	}
	
	net.getAnAugmentingPath().strPrint();

	return 0;
}
