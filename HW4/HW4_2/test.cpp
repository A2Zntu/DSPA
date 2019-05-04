#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std; 


void split(const string& s,
    vector<string>& sv,
                   const char delim = ' ') {
    sv.clear();
    istringstream iss(s);
     
    string temp;

    while (getline(iss, temp, delim)) {
        sv.emplace_back(move(temp));
    }

    return;
}

int main() {
    string s;
    vector<string> sv;
	getline(cin, s);  
    split(s, sv, ' ');

    for (const auto& s : sv) {
        cout << s << endl;
    }
 

    return 0;
}
