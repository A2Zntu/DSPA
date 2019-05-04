#include <string>
#include <iostream> 
#include <stdexcept>
using namespace std; 


//Time struct
struct Time {
	int hour;
	int min;
};


//parse HH:MM string time to integer minutes formate
Time parseTime(string sTime) {
	string delimiter = ":";

	size_t pos = 0;
	string token;
	pos = sTime.find(delimiter);
	token = sTime.substr(0, pos);
	int hour  = stoi(token);
	sTime.erase(0, pos + delimiter.length());
	int minute = stoi(sTime);

	return {hour, minute};
}

//parse integer minutes formate time to HH:MM string time
string parseTime(int time) {
	string hour = ((time/60) <10) ? ("0"+to_string(time/60)) : to_string(time/60);
	string minute = ((time%60) <10) ? ("0"+to_string(time%60)) : to_string(time%60);
	return hour + ":" + minute;
}

int main(){
	bool odd = true; 
	int num = 101; 
	int num2 = 3; 
	string sTime = "18:00";
	Time parsedTime = parseTime(sTime);
	int intTime = (parsedTime.hour*60) + parsedTime.min;
	cout << intTime << endl; 

}
