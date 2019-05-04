#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

void makeLowercase(string& str);
bool isInDict(string target, string dict[], int wordCnt);


int main()
{
  int wordCnt = 0;
  cin >> wordCnt;

  string target = "";
  cin >> target;
  makeLowercase(target);
  
  string filePath = "";
  cin >> filePath;
  
  ifstream fin(filePath);
  if(fin)
  {
    string* dict = new string[wordCnt];
    for(int i = 0; i < wordCnt; i++)
      fin >> dict[i];
    
    cout << isInDict(target, dict, wordCnt) << endl;
  
    delete [] dict;
  }
  fin.close();

  return 0;
}








void makeLowercase(string& str)
{
  for(int i = 0; i < str.length(); i++)
    str[i] = tolower(str[i]);
}

bool isInDict(string target, string dict[], int wordCnt)
{
  for(int i = 0; i < wordCnt; i++)
  {
    if(target.compare(dict[i]) == 0)
      return true;
  }
  return false;
}
