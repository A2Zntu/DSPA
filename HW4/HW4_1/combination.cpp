#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std; 

int factorial(int n) {
    stack<int> stack;
    stack.push(1);

    for(int i=1; i<=n; ++i) {
       stack.push((stack.top())*i);
    }
    return stack.top();
}


int comb(int n , int r){
	int nfac = factorial(n); 
	int rfac = factorial(r); 
	int n_rfac = factorial(n - r); 
	int res = nfac/(rfac * n_rfac); 
	return res; 
}


int main() {
	int n; 
	int r; 
	cin >> n >> r; 
	cout << "Answer: " << comb(n, r); 
}
