#include <iostream>
using namespace std;

const int MAX_NODE_CNT = 10; 

void distFromSource(const bool adjacent[][MAX_NODE_CNT], 
					int dist[], int nodeCnt, int source); 
int main(){
	int nodeCnt = 5; 
	bool adjacent[MAX_NODE_CNT][MAX_NODE_CNT]
	= {{1, 1, 0, 0, 1}, {1, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, 
	  {0, 0, 1, 1, 1}, {1, 0, 0, 1, 1}}; 
	int dist[MAX_NODE_CNT] = {0}; 
	int source = 0; 
	
	distFromSource(adjacent, dist, nodeCnt, source); 
	
	cout << "\nThe Complete Result: \n"; 
	for(int i = 0; i < nodeCnt; i++)
		cout << dist[i] << " "; 
	return 0;	
}

void distFromSource(const bool adjacent[][MAX_NODE_CNT], 
					int dist[], int nodeCnt, int source){
for(int i = 0; i < nodeCnt; i++)
	dist[i] = nodeCnt; 

dist[source] = 0;
int curDist= 1; 
int complete = 1; // Record how many nodes have been completed.

while(complete < nodeCnt){
	for(int i = 0; i < nodeCnt; i++){ // one for a level
		if(dist[i] == curDist - 1){
			for(int j = 0; j < nodeCnt; j++){
				if(adjacent[i][j] == true && dist[j] == nodeCnt){
					dist[j] = curDist; 
					complete++;  
				}
			}
		}
	}
	curDist++; 
}						
}
