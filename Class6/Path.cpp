#include<iostream>
#include<vector>
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







int main() {
	Path myPath; 
	Path tryPath(myPath, 32, 100); 
	tryPath.print(); 
	

	return 0;
}
