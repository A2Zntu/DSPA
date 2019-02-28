#include <iostream>
using namespace std;

int main(){
	int totalLen = 0, maxStop = 0, startStop = 0, endStop = 0;
	cin >> totalLen >> maxStop >> startStop >> endStop;
	int** array = new int*[totalLen-1];
	for(int i = 0; i < totalLen-1; ++i)
	    array[i] = new int[totalLen-1];
		for(int j = 0; j <= i; j++ ){
			cin >> array[i][j]; 
			}
		}
	cout << endl;	
	for(int i = 0; i < totalLen-1; i++){
		for(int j = 0; j <= i; j++ ){
			cout << array[i][j]; 
			}
		cout << endl;
		}	
	cout << endl;	
	return 0; 		
}
