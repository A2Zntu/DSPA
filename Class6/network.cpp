#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class Network {
	private:
		int n;
		int** resCap;
	public:
		Network(int n);
		void adjustArcCap(int node1, int node2, int capacity);
		void print();
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
	char c; 
	for(int i = 0; i < m; i++) {
		int u = 0, v = 0, capacity = 0;
		cin >> u  >> v >> capacity;
		net.adjustArcCap(u, v, capacity);
	}
	net.print();

	return 0;
}
