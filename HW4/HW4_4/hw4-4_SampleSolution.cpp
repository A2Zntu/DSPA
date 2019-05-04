#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// Print stack bottom to top
void PrintStack(stack<int> s)
{
	stack<int> tmp;
	
	// Pour out stack item and push to temp stack
	while (!s.empty())
	{
		tmp.push(s.top());
		s.pop();
	}
	
	// Print items one by one
	cout << tmp.top() + 1;
	tmp.pop();
	while (!tmp.empty())
	{
		cout << "," << tmp.top() + 1;
		tmp.pop();
	}
	cout << "\n";
}

// Depth First Search
// In each iteration, peek stack and check if there is available and unvisited node
// If such nodes exist, push them to the stack
// Otherwise, pop node from the stack
// Repeat until the stack is empty
bool DFS(string* map, int n)
{
	bool find = false;
	
	stack<int> DFS;
	bool* visit;
	visit = new bool[n];
	for (int i = 0; i < n; i++)
		visit[i] = false;
	
	// Push node 1 to stack
	DFS.push(0);
	visit[0] = true;
	PrintStack(DFS);
	
	while (!DFS.empty())
	{
		int thisNode = DFS.top();
		
		bool existPath = false;
		for (int i = 0; i < n; i++)
		{
			if (map[thisNode][i] == '1' && !visit[i])
			{
				existPath = true;
				DFS.push(i);
				visit[i] = true;  // record the visited node 
				
				if (i + 1 == n)
					find = true;
			}
		}
		
		if (!existPath)
			DFS.pop(); // no new nodes to add 
		else
			PrintStack(DFS);
			
		if (find)
			break;
	}
	
	delete [] visit;
	
	return find;
}

int main()
{
	string firstStr;
	cin >> firstStr;
	
	// Build map
	firstStr.erase(remove(firstStr.begin(), firstStr.end(), ','), firstStr.end());
	int n = firstStr.length();
	
	string* map;
	map = new string[n];
	
	map[0] = firstStr;
	
	for (int i = 1; i < n; i++)
	{
		string tmp;
		cin >> tmp;
		tmp.erase(remove(tmp.begin(), tmp.end(), ','), tmp.end());
		
		map[i] = tmp;
	}
	
	// Do DFS
	bool find = DFS(map, n);
	
	// Print searching result
	if (find)
		cout << 1;
	else
		cout << 0;
	
	delete [] map;
    return 0;
}

