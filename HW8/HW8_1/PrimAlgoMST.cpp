// C++ code
#include <iostream>
#include <vector>
#include <iomanip>      // for setw()

const int Max_Weight = 1000;    // 初始化key[]時需要infinity, 以Max_Weight代替

class GraphMST{
private:
    int num_vertex;
    std::vector<std::vector<int>> AdjMatrix;
public:
    GraphMST():num_vertex(0){};
    GraphMST(int n):num_vertex(n){
        AdjMatrix.resize(num_vertex);
        for (int i = 0; i < num_vertex; i++) {
            AdjMatrix[i].resize(num_vertex);
        }
    }
    void AddEdge(int from, int to, int weight);

    void PrimMST(int Start = 0);        // 可以指定起點Start, 若沒有指定, 則從vertex(0)作為MST的root
    friend int MinKeyExtract(int *key, bool *visited, int size);
};

int MinKeyExtract(int *key, bool *visited, int size){

    int min = Max_Weight, min_idx = 0;
    for (int i = 0; i < size; i++) {
        if (visited[i]==false && key[i]<min) {
            min = key[i];
            min_idx = i;
        }
    }
    return min_idx;
}
void GraphMST::PrimMST(int Start){

    int key[num_vertex], predecessor[num_vertex];
    bool visited[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        key[i] = Max_Weight;
        predecessor[i] = -1;
        visited[i] = false;     // false表示vertex還沒有被visited
    }

    key[Start] = 0;
    for (int i = 0; i < num_vertex; i++) {
        int u = MinKeyExtract(key, visited, num_vertex);
        visited[u] = true;
        for (int i = 0; i < num_vertex; i++) {
            if ( visited[i]==false && AdjMatrix[u][i]!=0 && AdjMatrix[u][i]<key[i]) {
                predecessor[i] = u;
                key[i] = AdjMatrix[u][i];
            }
        }
    }
    // print MST, 與MST演算法主體無關
    std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    int i = (Start+1)%num_vertex;   // 若從4開始, i依序為5,6,0,1,2,3
    while (i != Start) {
        std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
                  << " : " << std::setw(4) << AdjMatrix[predecessor[i]][i] <<"\n";
        i = (++i)%num_vertex;       // 到了6之後, 6+1 = 7, error:bad_access, 透過mod把7喬回0
    }
}
void GraphMST::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}

int main(){

    GraphMST g6(9);
    g6.AddEdge(0, 1, 2);g6.AddEdge(0, 2, 4);g6.AddEdge(0, 3, 6);
    g6.AddEdge(1, 0, 2);g6.AddEdge(1, 2, 5);
    g6.AddEdge(2, 0, 4);g6.AddEdge(2, 1, 5);g6.AddEdge(2, 3, 1);g6.AddEdge(2, 4, 2);
    g6.AddEdge(3, 0, 6);g6.AddEdge(3, 2, 1);g6.AddEdge(3, 5, 3);g6.AddEdge(3, 7, 4);
    g6.AddEdge(4, 2, 2);g6.AddEdge(4, 5, 1);g6.AddEdge(4, 6, 5);g6.AddEdge(4, 8, 3);
    g6.AddEdge(5, 3, 3);g6.AddEdge(5, 4, 1);g6.AddEdge(5, 6, 4);
    g6.AddEdge(6, 4, 5);g6.AddEdge(6, 5, 4);
	g6.AddEdge(7, 3, 4);
	g6.AddEdge(8, 4, 3); 
	
    std::cout << "MST found by Prim:\n";
    g6.PrimMST(2);

    return 0;
}
