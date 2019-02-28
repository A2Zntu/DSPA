#include <iostream>
using namespace std;

int main()
{
int num1 = 0, num2 = 0, zero = 0; 
int bigNum = 0, smallNum = 0;
int mod = 1; 
cin >> num1 >> num2;
if (num1 > num2){
	cout << num1 << " " << num2 << ":";
	bigNum = num1; 
	smallNum = num2; 
	}
else{ 
	cout << num2 << " " << num1 << ":";
	bigNum = num2; 
	smallNum = num1;}  

while(mod != 0){
	mod = bigNum % smallNum;
	if(mod != 0){
		cout << mod;
		bigNum = smallNum;
		smallNum = mod;
		
		mod = bigNum % smallNum; 
		if (mod!= 0)
			cout << " "; 
		else 
			cout << ".";
			
		}
	else
		cout << zero << ".";
		
	}
}

 			

