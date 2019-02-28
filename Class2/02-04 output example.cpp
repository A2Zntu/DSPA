#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
	ofstream scoreFile("temp.txt", ios::out);
	char name[20] = {0};
	int score = 0;
	char notFin = 0;
	bool con = true;

	if(!scoreFile)
		exit(1);
	while(con) {
		cin >> name >> score;
		scoreFile << name << " " << score << "\n";
		cout << "Continue (Y/N)? ";
		cin >> notFin;
		con = ((notFin == 'Y') ? true : false);
	}
	scoreFile.close();
	return 0;
}

