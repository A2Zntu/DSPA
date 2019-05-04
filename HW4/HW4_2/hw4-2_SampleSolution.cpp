#include <iostream>
#include <string>
#include <stack>

using namespace std;

string OPERATORS = "+-*/";

#pragma region functions title

// Parse string
int GetNextNum(string currentStr);
char GetNextOperator(string currentStr);
string GetNextStr(string currentStr);

// Print stack bottom to top
void PrintStack(stack<int> s);
// Get the priorty of operator
int GetPriority(char opr);
// Check if the priorty of _opr_ is prior to the top _opr_ in oprStack
bool IfPrior(char opr, stack<char> oprStack);
// Do operation _num1_ _opr_ _num2_
int DoOperation(int num1, int num2, char opr);
// Check priorty rule and try push _opr_ to oprStack
void TryPushOperator(char opr, stack<int> &numStack, stack<char> &oprStack);
// Do the rest of operation
void FinalResult(stack<int> numStack, stack<char> oprStack);

#pragma endregion

#pragma region Global functions body

int GetNextNum(string currentStr)
{
	return stoi(currentStr.substr(0, currentStr.find_first_of(OPERATORS)));
}

char GetNextOperator(string currentStr)
{
	return currentStr[currentStr.find_first_of(OPERATORS)];
}

string GetNextStr(string currentStr)
{
	return currentStr.erase(0, currentStr.find_first_of(OPERATORS) + 1);
}

void PrintStack(stack<int> s)
{
	stack<int> tmp;
	
	// Pour out stack item and push to temp stack
	while (!s.empty())
	{
		tmp.push(s.top());
		s.pop();
	}
	
	// Print items one by one
	cout << tmp.top();
	tmp.pop();
	while (!tmp.empty())
	{
		cout << "," << tmp.top();
		tmp.pop();
	}
	cout << "\n";
}

int GetPriority(char opr)
{
	if (opr == '+' || opr == '-')
		return 0;
	else if (opr == '*' || opr == '/')
		return 1;
}

bool IfPrior(char opr, stack<char> oprStack)
{
	if (oprStack.empty())
		return true;
	else
	{
		char topOpr = oprStack.top();
		return GetPriority(opr) > GetPriority(topOpr);
	}
}

int DoOperation(int num1, int num2, char opr)
{
	switch (opr)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			return num1 / num2;
	}
}

void TryPushOperator(char opr, stack<int> &numStack, stack<char> &oprStack)
{
	// If _opr_ is prior, just push
	if (IfPrior(opr, oprStack))
		oprStack.push(opr);
	// Otherwise, do operation _num1_ _opr_ _num2_, push result to _numStack_, try push _opr_ again
	else
	{
		int num2 = numStack.top();
		numStack.pop();
		int num1 = numStack.top();
		numStack.pop();
		char oprInStack = oprStack.top();
		oprStack.pop();

		numStack.push(DoOperation(num1, num2, oprInStack));

		TryPushOperator(opr, numStack, oprStack);
	}
}

void FinalResult(stack<int> numStack, stack<char> oprStack)
{
	// Do operation _num1_ _opr_ _num2_, push result to _numStack_
	while (numStack.size() > 1)
	{
		int num2 = numStack.top();
		numStack.pop();
		int num1 = numStack.top();
		numStack.pop();
		char oprInStack = oprStack.top();
		oprStack.pop();

		numStack.push(DoOperation(num1, num2, oprInStack));
	}

	// Print final result
	cout << numStack.top();
}

#pragma endregion

int main()
{
	stack<int> numStack;
	stack<char> oprStack;

	string inputStr;
	cin >> inputStr;

	string currentStr = inputStr;
	int currentNum;
	char currentOpr;
	while (currentStr.find_first_of(OPERATORS) != string::npos)
	{
		// Push number to _numStack_
		currentNum = GetNextNum(currentStr);
		numStack.push(currentNum);

		// Try push operator to _oprStack_
		currentOpr = GetNextOperator(currentStr);
		TryPushOperator(currentOpr, numStack, oprStack);

		// Move to next position
		currentStr = GetNextStr(currentStr);
		PrintStack(numStack);
	}

	// Push last number to _numStack_
	currentNum = GetNextNum(currentStr);
	numStack.push(currentNum);

	// Do the rest of operation and print final result
	FinalResult(numStack, oprStack);

	return 0;
}

