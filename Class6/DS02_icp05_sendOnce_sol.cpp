#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

const int VERY_LARGE = 999999;

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
		vector<int> getNodes();
		void print();
};

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

void Path::print() {
	if(this->nodes.size() == 0)
		cout << "<empty>" << endl;
	else {
		for(int i = 0; i < this->nodes.size() - 1; i++)
			cout << this->nodes[i] << ",";
		cout << this->nodes.back() << ";";
		cout << this->capacity << endl;
	}
}

int Path::getTail() {
	return this->nodes.back();
}

int Path::getCapacity() {
	return this->capacity;
}

vector<int> Path::getNodes() {
	return this->nodes;
}





class Network {
	private:
		int n;
		int** resCap;
	public:
		Network(int n);
		void adjustArcCap(int node1, int node2, int capacity);
		void print();
		vector<Path> getNextWithResCap(Path aPath);
		Path getAnAugmentingPath();
		void sendOnce(Path anAugPath);
		~Network();
};

Network::Network(int n) : n(n) {
	this->resCap = new int*[this->n];
	for(int i = 0; i < this->n; i++) {
		this->resCap[i] = new int[this->n];
		for(int j = 0; j < this->n; j++)
			this->resCap[i][j] = 0;
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

// input: a path of length L
// output: a vector of paths of length L + 1
// precondition: aPath is really a path in this network
vector<Path> Network::getNextWithResCap(Path aPath) {
	vector<Path> longerPaths;
	int tail = aPath.getTail();

	for(int i = 0; i < this->n; i++) {
		if(this->resCap[tail][i] > 0) {
			int oldCap = aPath.getCapacity();
			int newCap = oldCap;
			if(this->resCap[tail][i] < oldCap)
				newCap = this->resCap[tail][i];
			Path p(aPath, i, newCap);
			longerPaths.push_back(p);
		}
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
		vector<Path> curPlusOne = this->getNextWithResCap(cur);

		for(int i = 0; i < curPlusOne.size(); i++) {
			// whether the tail is a visited node should be checked below

//      cout << "..." << curPlusOne[i].getTail() << endl;
			if(curPlusOne[i].getTail() == n - 1) {
				anAugmentingPath = curPlusOne[i];
				keepGoing = false;
				break;
			} else
				pathQueue.push_back(curPlusOne[i]);
		}

//    cout << "===============\n";
//    for(int i = 0; i < pathQueue.size(); i++)
//      pathQueue[i].print();
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
		this->adjustArcCap(nodes[i + 1], nodes[i], flow); // direct the flow inversely  
	}
}

Network::~Network() {
	for(int i = 0; i < this->n; i++)
		delete [] resCap[i];
	delete [] resCap;
}







int main() {
	// initializing the original network
	int n = 0, m = 0;
	cin >> n >> m;
	Network net(n);
	for(int i = 0; i < m; i++) {
		int u = 0, v = 0, capacity = 0;
		cin >> u >> v >> capacity;
		net.adjustArcCap(u, v, capacity);
	}
	net.print();

	Path anAugPath = net.getAnAugmentingPath();
	anAugPath.print();
	net.sendOnce(anAugPath);
	net.print();

	anAugPath = net.getAnAugmentingPath();
	anAugPath.print();
	net.sendOnce(anAugPath);
	net.print();

	anAugPath = net.getAnAugmentingPath();
	anAugPath.print();
	net.sendOnce(anAugPath);
	net.print();

	return 0;
}
