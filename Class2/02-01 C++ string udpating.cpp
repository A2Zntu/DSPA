#include <iostream>
#include <string>
using namespace std;

int main()
{
  cout << "01234567890123456789\n";
  string myStr = "Today is not my day.";
  cout << myStr << endl;
  myStr.insert(9, "totally "); // Today is totally not my day. 
  cout << myStr << endl;
  myStr.replace(17, 3, "NOT"); // Today is totally NOT my day. 
  cout << myStr << endl;
  myStr.erase(17, 4); // Today is totally my day. 
  cout << myStr << endl;
  return 0;
}
 
