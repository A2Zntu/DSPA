#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string toDollarNumber(int value); 
int main(){
	int value = 0; 
	cin >> value; 
	string dollar; 
	dollar = toDollarNumber(value); 
	return dollar; 
}

string toDollarNumber(int value){
	string str = to_string(value);
	string dollar = "$";   
	for(int i = 0; i< str.length(); i++){
		if(i%3 != 0){
			dollar = dollar + str[i]
		}
		else
			dollar = dollar + ", " + str[i]
	}
	return dollar
}	
