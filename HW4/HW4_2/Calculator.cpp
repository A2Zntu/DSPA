#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

template<class ItemType>
class StackInterface {
	public :

		virtual bool isEmpty() const = 0;
		virtual bool push( const ItemType& newEntry) = 0;
		virtual bool pop() = 0;
		virtual ItemType popItem() = 0;
		virtual ItemType peek() const = 0;
		virtual void print() const = 0 ;
};



const int MAX_STACK = 99999; // set a value by yourself

template<typename ItemType>
class ArrayStack : public StackInterface<ItemType> {
	private:
		ItemType items[MAX_STACK]; // Array of stack items
		int top; // Index to top of stack
	public:
		ArrayStack(); // Default constructor
		bool isEmpty() const;
		bool push(const ItemType& newEntry);
		bool pop();
		ItemType popItem();
		ItemType peek() const;
		void print() const ;
};


template<typename ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1) {
}



template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const {
	return top < 0;
}

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry) {
	bool result = false ;
	if(this->top < MAX_STACK - 1) { // still have room
		top++;
		this->items[top] = newEntry;
		result = true ;
	}
	return result;
}

template<typename ItemType>
bool ArrayStack<ItemType>::pop() {
	bool result = false ;
	if(!this->isEmpty()) {
		top--;
		result = true ;
	}
	return result;
}

template<typename ItemType>
ItemType ArrayStack<ItemType>::popItem() {
	if(top < 0)
		throw out_of_range("Attempted to pop an empty stack.");
	ItemType topItem = items[top];
	top --;
	return topItem;
}



template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const {
	if(!this->isEmpty()) // check precondition
		return items[top];
	else
		throw logic_error("...");
}

template<typename ItemType>
void ArrayStack<ItemType>::print() const {

	vector<ItemType> as;
	int curNum = top;
	while(curNum >= 0) {
		as.push_back(items[curNum]);
		curNum --;
	}
	for(int i = top; i > 0; i--) {
		cout << as.at(i) << ",";
	}
	cout << as.at(0) << endl;
	as.clear();
}



//========================================================================================
//                                 Calculator
//========================================================================================
//check if char is a digit.
bool isDigit(char c) {
	return  (c >= '0' && c <= '9');
}

//check if char is an operator.
bool isOp(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

//determine the precedence of an operator
int getPrecedence (char c) {
	switch (c) {
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '(':
			return 3;
		case ')':
			return 3;
		default:
			return -1;
	}
}

//evaluate an arithmetic expression
int operate (int val1, int val2, char op) {
	if (op == '+') return val1 + val2;
	if (op == '-') return val1 - val2;
	if (op == '*') return val1 * val2;
	return val1 / val2;
}

//evaluate a string.
int evaluate (string s) {
	ArrayStack<int> vals;
	ArrayStack<char> ops;

	int val = 0;
	int pos = 0;

	while (pos < s.length()) {
		char spot = s[pos];
		if (isDigit(spot)) {
			val = (val * 10) + (int)(spot - '0'); // to deal with the number which exceed 10.
		} else if (isOp(spot)) {
			if (spot == '(') { // special case
				cout << "open parens, val = " << val << endl;
				ops.push(spot);
				val = 0;
			} else if (vals.isEmpty()) { // special case, the first digit and opt
				//cout << "empty stack, val = " << val << endl;
				vals.push(val);
				ops.push(spot);
				vals.print();
				val = 0;
			} else if (spot == ')') {
//				cout << "close parens, val = " << val << endl;
				vals.push(val);
				while (ops.peek() != '(') {
					spot = ops.popItem();
					val = vals.popItem();
					int prev = vals.popItem();
					val = operate(prev, val, spot);
					vals.push(val);
					vals.print();
				}
				ops.pop();
				vals.pop();
				//cout << "finished close parens, val = " << val << endl;
			} else {
				char prev = ops.peek();
				if (getPrecedence(spot) > getPrecedence(prev)) {
					// the new spot is * or /, higher than previous.
//					cout << "high precedence, val = " << val << endl;
					vals.push(val);
					ops.push(spot);
					vals.print();
					val = 0;
				} else {
					cout << "low or equal precedence, val = " << val << endl;
					cout << "=================================" << endl ;
					vals.print();
					ops.print();
					cout << "=================================" << endl ;

					int processVal = vals.popItem();
					char prevop = ops.popItem();
					processVal = operate(processVal, val, prevop);
					vals.push(processVal);
					// check the operator agian;
					if(!ops.isEmpty()) {
						prev = ops.peek();
//					cout << "prev: " << prev << endl;
//					cout << "Spot: " << spot << endl;
						if(getPrecedence(spot) <= getPrecedence(prev)) {
							processVal = vals.popItem();
							int processVal2 = vals.popItem();
							prevop = ops.popItem();
//						cout << "processVal2: " << processVal2 << " " << "processVal: " << processVal << " "
//							<< prevop << endl;
							processVal2 = operate(processVal2, processVal, prevop);
							vals.push(processVal2);
						}

					}

					ops.push(spot);
					vals.print();
					val = 0;
				}
			}
		}
		pos ++;
	}

	while (!ops.isEmpty()) {
		//cout << "ops not empty, val = " << val << endl;
		int prev = vals.popItem();
		char spot = ops.popItem();
		val = operate(prev, val, spot);

	}
	return val;
}

//========================================================================================
//                                 Main Function
//========================================================================================
int main() {
	string line;
	getline(cin, line);
	//cout << line << endl;
	cout << evaluate (line);

	return 0;
}

