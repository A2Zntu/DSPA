#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

void makeLowercase(string& str);
bool isInDict(string target, ifstream& fin);


int main()
{
  string target = "";
  cin >> target;
  makeLowercase(target);
  
  string filePath = "";
  cin >> filePath;
  
  ifstream fin(filePath);
  if(fin)
    cout << isInDict(target, fin) << endl;
  fin.close(); 

  return 0;
}








void makeLowercase(string& str)
{
  for(int i = 0; i < str.length(); i++)
    str[i] = tolower(str[i]);
}

bool isInDict(string target, ifstream& fin)
{
  while(!fin.eof())
  {
    string current = ""; 
    getline(fin, current);

    if(target.compare(current) == 0)
      return true;
  }
  return false;
}
