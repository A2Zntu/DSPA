#include <iostream>
using namespace std;


class mother {
	public:
		mother () {
			cout << "mother: no parameters\n";
		}
		mother (int a) {
			cout << "mother: int parameter\n";
		}
};
class daughter : public mother {
	public:
		daughter (int a)
//daughter建構子會自動呼叫mother()
		{
			cout << "daughter: int parameter\n\n";
		}
};
class son : public mother {
	public:
//son建構子會呼叫mother(a)
		son (int a) : mother (a) {
			cout << "son: int parameter\n\n";
		}
};
int main () {
	daughter cynthia (1);
	son daniel(1);
	return 0;
}
