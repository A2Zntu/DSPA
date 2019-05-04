#include <iostream>

class Manager
{
	private:
		int j;
	public:
		Manager(): j(0) { }
		void print() { std::cout << " " << j++; }
};


class Employee
{
	private:
	public:
		static Manager& refManager;	//declare class static variable in class
		void fn() { refManager.print(); }
};

Manager manager;
Manager& Employee::refManager = manager; //initialize static variable outside of class

int main()
{
	Manager manager1;
	for (int i=0; i<2; i++)		//test loop, one testcase per iteration
	{
		Employee::refManager = manager1; //reset

		Employee e1;		//Employee objects being tested
		Employee e2;
					//expected output
		e1.fn();		// 0
		e2.fn();		// 1
		/*Employee destructor is automatically called
		  because its scope of existence has finished */
	}
}
