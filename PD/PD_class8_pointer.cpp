#include <iostream>
using namespace std;

int main(){
	int a = 5; 
	double b = 23.3; 
	int* aPtr = &a; 
	double* bPtr = &b; 
	
	cout << &a << "\n"; 
	cout << &b << "\n"; 
	cout << &aPtr << "\n"; 
	cout << &bPtr << "\n"; 
}
