#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

void makeLowercase(string& str);
bool isInDict(string target, string dict[], int wordCnt);


int main()
{
  string target = "";
  cin >> target;
  
  string filePath = "";
  cin >> filePath;
  
  int wordCnt = 0;
  ifstream fin(filePath);
  if(fin)
  {
    while(!fin.eof())
    {
      string temp = ""; 
      getline(fin, temp);
      wordCnt++;
    }
    fin.seekg(0, fin.beg);

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
  ofstream fout("out.txt");
  string orignalTarget = target; 
  makeLowercase(target);
  for(int i = 0; i < wordCnt; i++)
  {
    fout << "Comparing " << orignalTarget << " with " << dict[i];
    if(target.compare(dict[i]) == 0)
    {
      fout << "... Got it!" << endl;
      return true;
    }
    fout << endl;
  }
  fout.close();
  return false;
}
