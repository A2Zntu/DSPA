#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ofstream myFile;
  myFile.open("temp.txt", ios::ate);
  myFile.seekp(100);
  myFile << "1 abc\n &%^ " << 123.45;
  myFile.close();

  return 0;
}
