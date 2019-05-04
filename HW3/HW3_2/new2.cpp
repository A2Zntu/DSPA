
class Node {
	public:
		string symbol;
		int Cnt;

};

vector<Node> node_list;


int str2int(string aNode) {
	change symbol to int; 
}


string int2str(int num) {
	change int to symbol;
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
	update longerPaths; 
	sort((longerPaths.begin()), (longerPaths.end()), Network::sortByRules);


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
		int sizeOfCurQueue = curPlusOne.size();
		int visited[sizeOfCurQueue] = {0};

		if(curPlusOne.empty() == false) {
			for(int i = 0; i < sizeOfCurQueue; i++) {

				// Check whether the tail is a visited node
				for(int j = 0; j < curPlusOne[i].getNodeSize() - 1; j++) {
						check whether the tail node has been visited yet.
						if visted then visited[i] = 1;
					}
				}
			}

			for(int i = 0; i < sizeOfCurQueue; i++) {
				if visited before:
					pass; 
				else:
					if the tail node == n-1; 
						anAugmentingPath = curPlusOne[i];
						break; 
					else:
						pathQueue.push_back(curPlusOne[i]);		
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

	size_t next = 0;

	cin >> nodesString;
	for (int i = 0; i< n; i++) {
		read every symbol; 
		and put into node_list; 
	}

	cin.ignore();
	Network net(n);
	string line;
	while(getline(cin, line)) {
		read startNode, endNode, capacity; 
		and convert str to int; 
		net.adjustArcCap(startNode, endNode, capacity);
		if(cin.eof())
			break;
	}
	
	net.getAnAugmentingPath().strPrint();

	return 0;
}
