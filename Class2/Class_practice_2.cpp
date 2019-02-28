#include <iostream>
#include <string>
#include <cctype>
using namespace std;
 
void makeLowerCase(string& str); 
 
int main(){
	int wordCnt = 0; 
	cin >> wordCnt; 
	string target = " "; 
	cin >> target; 
	makeLowerCase(target); 
	
	string* dict = new string[wordCnt]; 
	for(int i = 0; i< wordCnt; i++)
		cin >> dict[i]; 
	
	bool findword = false; 
	while(findword == false){
		for(int i = 0; i < wordCnt; i++){
			if(target == dict[i]){
				cout << 1;
				findword = true; 
				break;
			}	
		}
		if(findword == false)
			cout << 0; 
		findword = true;
	}
		
	return 0; 		
}

void makeLowerCase(string& str){
	for(int i = 0; i < str.length(); i++){
		str[i] = tolower(str[i]); 
	}
}
