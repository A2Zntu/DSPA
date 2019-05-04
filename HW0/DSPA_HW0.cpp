#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <typeinfo>

using namespace std;

void addEdge( vector<int>graph[], int u, int v);
void print(vector<int>graph[], int nodeNum);
void searchAdjNode( vector<int>graph[], const int startNode, const int routeLen);
void insertNode(vector<int>adjList[], vector<int>graph[], const int startNode, int curNode);
int main() {
	int nodeNum = 0, edgeNum = 0;
	int u, v;
	int startNode;
	int routeLen;
	cin >> nodeNum >> edgeNum;
	vector<int>* graph = new vector<int>[nodeNum + 1]; // because the start node is 1

	for(int i = 0; i < edgeNum; i++) {
		cin >> u >> v;
		addEdge(graph, u, v);
	}
	//print(graph, nodeNum + 1);
	cin >> startNode >> routeLen;
	searchAdjNode(graph, startNode, routeLen);
	return 0;
}

void addEdge( vector<int>graph[], int u, int v) {
	graph[u].push_back(v);
	graph[v].push_back(u);
}

void searchAdjNode( vector<int>graph[], const int startNode, const int routeLen) {
	vector<int>* adjList = new vector<int>[1];
	int curNode;
	int nextNodeNum = 1;
	int nodecounter = 0;
	int cur_node;
	curNode = startNode;
	for(int i = 0; i < routeLen; i++) {
		insertNode(adjList, graph, startNode, curNode);
		nextNodeNum = graph[curNode].size();
		while(nodecounter < nextNodeNum && i > 0) {
			cur_node = graph[curNode][nodecounter];
			insertNode(adjList, graph, startNode, cur_node);
			nodecounter++;
		}

	}
	// start sorting the adjList by element
	set<int> s;
	unsigned size = adjList[0].size();
	for( unsigned i = 0; i < size; ++i ) s.insert( adjList[0][i] );
	adjList[0].assign( s.begin(), s.end());


	// cout the element
	vector<int>::iterator it;
	for (it = adjList[0].begin(); it != adjList[0].end(); it++)
		if(it != adjList[0].end()-1)
			cout << *it << " ";
		else
			cout << *it;

}

void insertNode(vector<int>adjList[], vector<int>graph[], const int startNode, int curNode) {
	vector<int>::iterator it;
	for(it = graph[curNode].begin(); it != graph[curNode].end(); it++) {
		if(*it != startNode)
			adjList[0].push_back(*it);
	}
}

void print(vector<int>graph[], int nodeNum) {
	vector<int>::iterator it;
	for(int i = 0; i < nodeNum; i++) {
		cout << "Adjacent List" << " " << i << "\n";
		for(it = graph[i].begin(); it != graph[i].end(); it++) {
			cout << *it << " ";
			cout << "\n";
		}
	}
}
