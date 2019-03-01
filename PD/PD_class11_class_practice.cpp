#include <iostream>
using namespace std;

// Classes (p. 23)

class A
{
public:
  A() { cout << "A\n"; }
  ~A() { cout << "a\n"; }
};
class B
{
private:
  A a;
public:
  B() { cout << "B\n"; }
  ~B() { cout << "b\n"; }
};

int main()
{
  B b;
  return 0;
}
