#include <iostream>
using namespace std;

const int MAX_LEN = 10000;

void ruleOutPrime
  (int x, bool isPrime[], int n);

int main()
{
  int n = 0; 
  cin >> n; // must < 10000
  bool isPrime[MAX_LEN] = {0};
  for(int i = 0; i < n; i++)
    isPrime[i] = true;
  for(int i = 2; i <= n; i++)
  {
    if(isPrime[i] == true)
    {
      cout << i << " ";
      ruleOutPrime(i, isPrime, n);
    }
  }
  return 0;
}

void ruleOutPrime
  (int x, bool isPrime[], int n)
{
  for(int i = 1; x * i < n; i++)
    isPrime[x * i] = false;
}
