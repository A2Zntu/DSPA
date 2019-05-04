#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;


bool debugStackStatus = true;

// initialize the coeffcient to zero
int constCoef = 0;
int aCoef = 0;
int bCoef = 0;
int cCoef = 0;
int orderArray[4] = {0, 0, 0, 0};
int curOrder = 1;

char aOps = '*';
char bOps = '*';
char cOps = '*';

//========================================================================================
//                                 StackInterface
//========================================================================================


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
	if(!this->isEmpty()) {
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

	} else
		cout << "Empty Stack!!" << endl;
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
	return (c == '+' || c == '-' || c == '*' || c == '/');
}


bool isAlphabet(char c) {
	return (c == 'a' || c == 'b' || c == 'c');
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

//Combine the Coefficient and Letter
string operateAlpha(int val, char letter, char op) {
	string strVal, strLetter;
	stringstream ss, sss;

	ss << val;
	sss << letter;
	ss >> strVal;
	sss >> strLetter;

	if(op == '*')
		if(val < 0)
			return strVal + strLetter;
		else if(val == 1)
			return strLetter;
		else if(val == -1)
			return "-" + strLetter;
		else
			return "+" + strVal + strLetter;

	else if (op == '/')
		if(val < 0) {
			strVal.erase(strVal.begin());
			return "-" + strLetter + "/" + strVal;
		} else
			return "+" + strLetter + "/" + strVal;

}

string operateAlpha(int val, bool mode = false) {
	string strVal;
	stringstream ss;
	ss << val;
	ss >> strVal;
	if(val > 0 && mode == false)
		return "+" + strVal;
	return strVal;
}



string operateLetter(char letter) {
	string strLetter;
	stringstream ss;
	ss << letter;
	ss >> strLetter;
	return strLetter;
}


string combineString() {
	string strArray[4];
	string completeStr;
	if(orderArray[0] != 0 && constCoef != 0)
		strArray[0] = operateAlpha(constCoef);
	if(orderArray[1] != 0 && aCoef != 0)
		strArray[1] = operateAlpha(aCoef, 'a', aOps);
	if(orderArray[2] != 0 && bCoef != 0)
		strArray[2] = operateAlpha(bCoef, 'b', bOps);
	if(orderArray[3] != 0 && cCoef != 0)
		strArray[3] = operateAlpha(cCoef, 'c', cOps);

	// find order to combine string
	int minCurOrder = 1000;
	string curString;
	bool complete = false;
	bool visited[4] = {false};

	while(!complete) {
		for(int i = 0; i<4; i++) {
			if(orderArray[i] < minCurOrder && visited[i] == false) {
				curString = strArray[i];
				minCurOrder = orderArray[i];

			} else if(orderArray[i] == 0)
				visited[i] = true;
		}
		// find which is the minCurOrder and make it to visited
		for(int i = 0; i < 4; i++) {
			if(minCurOrder == orderArray[i]) {
				completeStr += curString;
				visited[i] = true;
			} else if (strArray[i].length() == 0)
				visited[i] = true;
		}

		if(visited[0] == true && visited[1] == true && visited[2] == true && visited[3] == true)
			break;
		// reset the minCurOrder
		minCurOrder = 1000;
	}
	if(completeStr[0] == '+')
		completeStr.erase(completeStr.begin());

	return completeStr;
}


void refreshCoef(int processVal, char alphabet, char prevop) {
	if(alphabet == 'a') {
		aCoef += processVal;
		aOps = prevop;
	} else if(alphabet == 'b') {
		bCoef += processVal;
		bOps = prevop;
	} else if(alphabet == 'c') {
		cCoef += processVal;
		cOps = prevop;
	} else {
		if(prevop == '+')
			constCoef += processVal;
		else if (prevop == '-')
			constCoef -= processVal;
	}

}

bool signReverse(char alphabet) {
	switch(alphabet) {
		case 'a':
			aCoef = aCoef * (-1);
			return true;

		case 'b':
			bCoef = bCoef * (-1);
			return true;

		case 'c':
			cCoef = cCoef * (-1);
			return true;

		case 'z':
			return true;
	}
}


//========================================================================================
//                                 Evaluate Function
//========================================================================================

//evaluate a string.
void evaluate (string s) {
	ArrayStack<int> vals;
	ArrayStack<char> ops;
	ArrayStack<char> letter;
	ArrayStack<string> castle;

	int val = 0;
	int pos = 0;

	while (pos < s.length()) {
		char spot = s[pos];
		cout << "spot: " << spot << endl;
		if (isDigit(spot)) {
			val = (val * 10) + (int)(spot - '0'); // to deal with the number which exceed 10.

		} else if (isOp(spot)) {
			char defaultLetter = 'z';
			// change mode
			bool checkLetter = (val == 0 && !letter.isEmpty());
			if(checkLetter)
				defaultLetter = letter.peek();
			// special case, the first digit and opt
			if (vals.isEmpty()) {
				if(checkLetter) {
					ops.push(spot);
					if(!castle.isEmpty()) {
						bool mode = true;
						castle.push(operateAlpha(1, defaultLetter, '*'));
						castle.print();
						castle.pop();
					} else {
						vals.print();
					}
					val = 0;

				} else {

					if(orderArray[0] == 0) {
						orderArray[0] = curOrder;
						curOrder ++;
					}
					vals.push(val);
					ops.push(spot);
					if(!castle.isEmpty()) {
						bool mode = true;
						castle.push(operateAlpha(val, mode));
						castle.print();
						castle.pop();
					} else {
						vals.print();
					}
					val = 0;
				}


				// When ops need to Compare.
			} else {
				char prev = ops.peek();
				/*
				Higher precedence
				*/
				if (getPrecedence(spot) > getPrecedence(prev)) {
					if(debugStackStatus) {
						cout << "high precedence" << endl;
						cout << "------------------------------------" << endl ;
						cout << "vals: ";
						vals.print();

						cout << "ops: ";
						ops.print();

						cout << "letter: ";
						letter.print();

						cout << "castle: ";
						castle.print();
						cout << "------------------------------------" << endl ;
					}

					if(checkLetter) { // special case, the alphabet with no Coefficient
						ops.push(spot);
						if(!castle.isEmpty()) {
							bool mode = true;
							castle.push(operateAlpha(1, defaultLetter, '*'));
							castle.print();
							castle.pop();
						} else {
							vals.print();
						}
						val = 0;
					} else {
						vals.push(val);
						ops.push(spot);
						if(!castle.isEmpty()) {
							bool mode = true;
							castle.push(operateAlpha(val, mode));
							castle.print();
							castle.pop();
						} else {
							vals.print();
						}
						val = 0;
					}


				} else {
					/*
					Lower or equal precedence
					*/

					if(debugStackStatus) {
						cout << "low or equal precedence" << endl;
						cout << "------------------------------------" << endl ;
						cout << "vals: ";
						vals.print();

						cout << "ops: ";
						ops.print();

						cout << "letter: ";
						letter.print();

						cout << "castle: ";
						castle.print();
						cout << "------------------------------------" << endl ;
					}
					if(!letter.isEmpty()) {
						int processVal = vals.popItem();
						char alphabet = letter.popItem();
						char prevop = ops.popItem();
						// Letter dealing
						defaultLetter = alphabet;
						refreshCoef(processVal, alphabet, prevop);
					}
					// Real Number dealing
					else {
						int processVal = vals.popItem();
						char prevop = ops.popItem();
						processVal = operate(processVal, val, prevop);
						vals.push(processVal);
						constCoef += processVal;
						// reset the const variable order
						if(orderArray[0] == 0) {
							orderArray[0] = curOrder;
							curOrder ++;
						}
					}
					// Second Check;
					// check the operator agian;
					if(!ops.isEmpty()) {
						cout << "Second Check!" << endl;
						prev = ops.peek();
						cout << "constCoef: " << constCoef << endl;
						if(getPrecedence(spot) <= getPrecedence(prev)) {
							char prevop2 = ops.popItem();
							// negative sign
							if(prevop2 == '-') {
								signReverse(defaultLetter);
							}
							// maybe redudant
							if(castle.isEmpty() && defaultLetter == 'z') {
								int processVal1 = vals.popItem();
								int processVal2 = vals.popItem();
								processVal2 = operate(processVal2, processVal1, prevop2);
								vals.push(processVal2);
								constCoef = processVal2;
								cout << "constCoef: " << constCoef << endl;
							}
						}

					}
					ops.push(spot);
					// Now, we like to put the String into Castle;
					string combine = combineString();
					if(!castle.isEmpty()) {
						castle.pop();
					}
					castle.push(combine);
					castle.print();
					val = 0;
				}
			}
		} else if(isAlphabet(spot)) {
			letter.push(spot);
			// Specail Case! When the alphabet is the first digit.
			if(pos == 0) {
				int firstAlphabetCoef = 1;
				switch(spot) {
					case 'a':
						aCoef = firstAlphabetCoef;
						break;
					case 'b':
						bCoef = firstAlphabetCoef;
						break;
					case 'c':
						cCoef = firstAlphabetCoef;
						break;
				}
			}
			switch(spot) {
				case 'a':
					if(orderArray[1] == 0) {
						orderArray[1] = curOrder;
						curOrder ++;
					}
					break;

				case 'b':
					if(orderArray[2] == 0) {
						orderArray[2]= curOrder;
						curOrder ++;
					}
					break;
				case 'c':
					if(orderArray[3] == 0) {
						orderArray[3]= curOrder;
						curOrder ++;
					}
					break;
			}
		}
		pos ++;
	}

	while (!ops.isEmpty()) {
		char defaultAlphabet = 'z';
		if(debugStackStatus) {
			cout << "Final Debug" << endl;
			cout << "------------------------------------" << endl ;
			cout << "vals: ";
			vals.print();

			cout << "ops: ";
			ops.print();

			cout << "letter: ";
			letter.print();

			cout << "castle: ";
			castle.print();
			cout << "------------------------------------" << endl ;
		}

		if(!letter.isEmpty()) {
			int processVal = 0;
			if(!vals.isEmpty())
				processVal = vals.popItem();
			if(val != 0)
				processVal = val;
			char alphabet = letter.popItem();
			defaultAlphabet = alphabet;
			char prevop = ops.popItem();
			// Letter dealing
			refreshCoef(processVal, alphabet, prevop);
		} else {
			int prev = vals.popItem();
			if(!vals.isEmpty())
				val = vals.popItem();
			char spot = ops.popItem();
			val = operate(prev, val, spot);
			cout << "val: " << val << endl;
			cout << "check constCoef: " << constCoef << endl;
			if(ops.isEmpty())
				constCoef = val;

			if(orderArray[0] == 0) {
				orderArray[0] = curOrder;
				curOrder ++;
			}
		}
		if(vals.isEmpty() || ops.isEmpty()) {
			// Last sign Check for alphabet;
			if(defaultAlphabet != 'z') {
				if(ops.peek() == '-')
					signReverse(defaultAlphabet);
			}

			string combine = combineString();
			cout << combine;
			break;
		}
	}
}

//========================================================================================
//                                 Main Function
//========================================================================================
int main() {
	string line;
	getline(cin, line);
	//cout << line << endl;
	evaluate (line);
	cout << endl;
	cout << "----------------------------------------" << endl;
	cout << "constCoef: " << constCoef << endl
	     << "aCoef: " << aCoef << endl
	     << "bCoef: " << bCoef << endl
	     << "cCoef: " << cCoef << endl;
	for(int i =0; i < 4; i++) {
		cout << orderArray[i] << ' ';
	}
//	string str = combineString();
//	cout << str << endl;

}

