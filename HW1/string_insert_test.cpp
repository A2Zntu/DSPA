// inserting into a string
#include <iostream>
#include <string>

int main ()
{
  std::string str="My name is ";
  std::string str2="Evan";
  std::string str3="I am I Fan Chiang a.k.a. ";
  std::string::iterator it;

  // used in the same order as described above:
  str.insert(11,str2);                 // My name is Evan 
  str.insert(11,str3, 5, str3.length());   // My name is I Fan Chiang a.k.a. Evan 
  std::cout << str << '\n';
  return 0;
}
