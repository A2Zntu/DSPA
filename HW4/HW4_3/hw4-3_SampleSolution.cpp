#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

const string OPERATORS = "+-*/";

#pragma region classes title

// Term class, element of polynomial
// Mathematical meaning : _mulCoef_ * _var_ / _divCoef_
// _next_ is a pointer points to next term in polynomial
// Defalut : 1 * "" / 1, _next_ = NULL
class Term
{
private:
	int mulCoef;
	int divCoef;
	string var;
	Term* next;

public:
	// Constructor
	Term() : mulCoef(1), divCoef(1), var(""), next(NULL) {};
	explicit Term(int m, string v, int d = 1, Term* n = NULL) : mulCoef(m), divCoef(d), var(v), next(n) { FracReduct(); }

	// Get / Set private members
	int GetMul() { return mulCoef; }
	int GetDiv() { return divCoef; }
	string GetVar() { return var; }
	Term* GetNext() { return next; }

	void SetMul(int m) { mulCoef = m; }
	void SetDiv(int d) { divCoef = d; }
	void SetVar(char v) { var = v; }
	void SetNext(Term* n) { next = n; }

	// Fraction reduction
	void FracReduct();

	// Operator overloading
	friend ostream& operator << (ostream& out, const Term& t);
	Term operator + (const Term& t);
	Term& operator += (const Term& t);
	Term operator - (const Term& t);
	Term& operator -= (const Term& t);
	Term operator * (const Term& t);
	Term& operator *= (const Term& t);
	Term operator / (const Term& t);
	Term& operator /= (const Term& t);
};

// Polynomial class, linked list
// _termsHead_ is a pointer points to first term in polynomial
// Defalut : _termsHead_ = NULL
class Polynomial
{
private:
	Term* termsHead;

public:
	// Constructor
	Polynomial() : termsHead(NULL) {};

	// Push term to the tail of polynomial
	void PushTerm(Term t);

	// Operator overloading
	friend ostream& operator << (ostream& out, const Polynomial& p);
	Polynomial operator + (Polynomial& p);
	Polynomial& operator += (Polynomial& p);
	Polynomial operator - (Polynomial& p);
	Polynomial& operator -= (Polynomial& p);
	Polynomial operator * (Polynomial& p);
	Polynomial& operator *= (Polynomial& p);
	Polynomial operator / (Polynomial& p);
	Polynomial& operator /= (Polynomial& p);
};

#pragma endregion

#pragma region functions title

// Parse string
string GetNextVar(string currentStr);
char GetNextOperator(string currentStr);
string GetNextStr(string currentStr);

// Get greatest common divisor of _num1_ and _num2_
int gcd(int num1, int num2);
// Print stack bottom to top
void PrintStack(stack<Polynomial> s);
// Get the priorty of operator
int GetPriority(char opr);
// Check if the priorty of _opr_ is prior to the top _opr_ in oprStack
bool IfPrior(char opr, stack<char> oprStack);
// Do operation _num1_ _opr_ _num2_
Polynomial DoOperation(Polynomial poly1, Polynomial poly2, char opr);
// Check priorty rule and try push _opr_ to oprStack
void TryPushOperator(char opr, stack<Polynomial>& polyStack, stack<char>& oprStack);
// Do the rest of operation
void FinalResult(stack<Polynomial> polyStack, stack<char> oprStack);

#pragma endregion

#pragma region Term functions body

void Term::FracReduct()
{
	// Two negatives make a positive
	if (mulCoef < 0 && divCoef < 0)
	{
		mulCoef *= -1;
		divCoef *= -1;
	}

	// Fraction reduction, divided by greatest common divisor
	int x = gcd(abs(mulCoef), abs(divCoef));
	if (x > 1)
	{
		mulCoef /= x;
		divCoef /= x;
	}
}

ostream& operator << (ostream& out, const Term& t)
{
	// If there is no variable, just print _mulCoef_ (guarantee _divCoef_ is 1)
	if (t.var == "")
	{
		out << t.mulCoef;
		return out;
	}
	// Otherwise, print _mulCoef_ _var_ / _divCoef_ (no space between each other)
	// If _mulCoef_ is -1, print -_var_ (ex. "-a")
	// If _mulCoef_ is 1, print _var_ (ex. "a")
	else
	{
		if (t.mulCoef == -1)
			out << "-";
		else if (t.mulCoef != 1)
			out << t.mulCoef;
		out << t.var;
		if (t.divCoef > 1)
			out << "/" << t.divCoef;
		return out;
	}
}

Term Term::operator + (const Term& t)
{
	int newMulCoef = mulCoef * t.divCoef + t.mulCoef * divCoef;
	int newDivCoef = divCoef * t.divCoef;
	Term newTerm(newMulCoef, var, newDivCoef, next);
	return newTerm;
}

Term& Term::operator += (const Term& t)
{
	mulCoef = mulCoef * t.divCoef + t.mulCoef * divCoef;
	divCoef = divCoef * t.divCoef;
	FracReduct();
	return *this;
}

Term Term::operator - (const Term& t)
{
	int newMulCoef = mulCoef * t.divCoef - t.mulCoef * divCoef;
	int newDivCoef = divCoef * t.divCoef;
	Term newTerm(newMulCoef, var, newDivCoef, next);
	return newTerm;
}

Term& Term::operator -= (const Term& t)
{
	mulCoef = mulCoef * t.divCoef - t.mulCoef * divCoef;
	divCoef = divCoef * t.divCoef;
	FracReduct();
	return *this;
}

Term Term::operator * (const Term& t)
{
	int newMulCoef = mulCoef * t.mulCoef;
	int newDivCoef = divCoef * t.divCoef;
	string newVar;
	if (var == "")
		newVar = t.var;
	else
		newVar = var;
	Term newTerm(newMulCoef, newVar, newDivCoef, next);
	return newTerm;
}

Term& Term::operator *= (const Term& t)
{
	mulCoef = mulCoef * t.mulCoef;
	divCoef = divCoef * t.divCoef;
	if (var == "")
		var = t.var;
	FracReduct();
	return *this;
}

Term Term::operator / (const Term& t)
{
	int newMulCoef;
	int newDivCoef;
	if (var == "")
	{
		newMulCoef = mulCoef / t.mulCoef;
		newDivCoef = divCoef;
	}
	else
	{
		newMulCoef = mulCoef * t.divCoef;
		newDivCoef = divCoef * t.mulCoef;
	}
	Term newTerm(newMulCoef, var, newDivCoef, next);
	return newTerm;
}

Term& Term::operator /= (const Term& t)
{
	if (var == "")
	{
		mulCoef = mulCoef / t.mulCoef;
		divCoef = divCoef;
	}
	else
	{
		mulCoef = mulCoef * t.divCoef;
		divCoef = divCoef * t.mulCoef;
	}

	FracReduct();
	return *this;
}

#pragma endregion

#pragma region Polynomial functions

void Polynomial::PushTerm(Term t)
{
	Term* newTerm = new Term(t.GetMul(), t.GetVar(), t.GetDiv());

	// If there is no term in polynomial, just push
	if (termsHead == NULL)
	{
		termsHead = newTerm;
		return;
	}

	// Get last position and push
	Term* current = termsHead;
	while (current->GetNext() != NULL)
	{
		current = current->GetNext();
	}
	current->SetNext(newTerm);
}

ostream& operator << (ostream& out, const Polynomial& p)
{
	if (p.termsHead != NULL)
	{
		bool printPlus = true;

		// Print the first term
		if (p.termsHead->GetMul() != 0 || p.termsHead->GetNext() == NULL)
			out << *p.termsHead;
		else
			printPlus = false;

		// Print the term that the _mulCoef_ is not zero, connet them by "+" if _mulCoef_ is not smaller than 0
		Term* current = p.termsHead;
		while (current->GetNext() != NULL)
		{
			current = current->GetNext();
			if (current->GetMul() != 0)
			{
				if (current->GetMul() >= 0 && printPlus)
					out << "+";
				out << *current;

				printPlus = true;
			}
		}

		// If all _mulCoef_ are 0, print "0"
		if (!printPlus)
			out << "0";

		return out;
	}
}

Polynomial Polynomial::operator + (Polynomial& p)
{
	Polynomial newPoly;
	newPoly.termsHead = termsHead;

	// Find the corresponding term and do operation. If it doesn't exist, push to the tail of polynomial
	Term* pCurrent = p.termsHead;
	while (pCurrent != NULL)
	{
		Term* current = newPoly.termsHead;
		bool findTerm = false;
		while (current != NULL)
		{
			if (pCurrent->GetVar() == current->GetVar())
			{
				*current += *pCurrent;
				findTerm = true;
				break;
			}

			current = current->GetNext();
		}
		if (!findTerm)
			newPoly.PushTerm(*pCurrent);

		pCurrent = pCurrent->GetNext();
	}

	return newPoly;
}

Polynomial& Polynomial::operator += (Polynomial& p)
{
	// Find the corresponding term and do operation. If it doesn't exist, push to the tail of polynomial
	Term* pCurrent = p.termsHead;
	while (pCurrent != NULL)
	{
		Term* current = termsHead;
		bool findTerm = false;
		while (current != NULL)
		{
			if (pCurrent->GetVar() == current->GetVar())
			{
				*current += *pCurrent;
				findTerm = true;
				break;
			}

			current = current->GetNext();
		}
		if (!findTerm)
			PushTerm(*pCurrent);

		pCurrent = pCurrent->GetNext();
	}

	return *this;
}

Polynomial Polynomial::operator - (Polynomial& p)
{
	Polynomial newPoly;
	newPoly.termsHead = termsHead;

	// Find the corresponding term and do operation. If it doesn't exist, push to the tail of polynomial
	Term* pCurrent = p.termsHead;
	while (pCurrent != NULL)
	{
		Term* current = newPoly.termsHead;
		bool findTerm = false;
		while (current != NULL)
		{
			if (pCurrent->GetVar() == current->GetVar())
			{
				*current -= *pCurrent;
				findTerm = true;
				break;
			}

			current = current->GetNext();
		}
		if (!findTerm)
		{
			Term tmp(-1, "");
			*pCurrent *= tmp;
			newPoly.PushTerm(*pCurrent);
		}

		pCurrent = pCurrent->GetNext();
	}

	return newPoly;
}

Polynomial& Polynomial::operator -= (Polynomial& p)
{
	// Find the corresponding term and do operation. If it doesn't exist, push to the tail of polynomial
	Term* pCurrent = p.termsHead;
	while (pCurrent != NULL)
	{
		Term* current = termsHead;
		bool findTerm = false;
		while (current != NULL)
		{
			if (pCurrent->GetVar() == current->GetVar())
			{
				*current -= *pCurrent;
				findTerm = true;
				break;
			}

			current = current->GetNext();
		}
		if (!findTerm)
		{
			Term tmp(-1, "");
			*pCurrent *= tmp;
			PushTerm(*pCurrent);
		}

		pCurrent = pCurrent->GetNext();
	}

	return *this;
}

Polynomial Polynomial::operator * (Polynomial& p)
{
	Polynomial newPoly;
	newPoly.termsHead = termsHead;

	// Find the last term and do operation
	Term* pCurrent = p.termsHead;
	while (pCurrent->GetNext() != NULL)
	{
		pCurrent = pCurrent->GetNext();
	}
	Term* current = newPoly.termsHead;
	while (current->GetNext() != NULL)
	{
		current = current->GetNext();
	}

	*current *= *pCurrent;

	return newPoly;
}

Polynomial& Polynomial::operator *= (Polynomial& p)
{
	// Find the last term and do operation
	Term* pCurrent = p.termsHead;
	while (pCurrent->GetNext() != NULL)
	{
		pCurrent = pCurrent->GetNext();
	}
	Term* current = termsHead;
	while (current->GetNext() != NULL)
	{
		current = current->GetNext();
	}

	*current *= *pCurrent;

	return *this;
}

Polynomial Polynomial::operator / (Polynomial& p)
{
	Polynomial newPoly;
	newPoly.termsHead = termsHead;

	// Find the last term and do operation
	Term* pCurrent = p.termsHead;
	while (pCurrent->GetNext() != NULL)
	{
		pCurrent = pCurrent->GetNext();
	}
	Term* current = newPoly.termsHead;
	while (current->GetNext() != NULL)
	{
		current = current->GetNext();
	}

	*current /= *pCurrent;

	return newPoly;
}

Polynomial& Polynomial::operator /= (Polynomial& p)
{
	// Find the last term and do operation
	Term* pCurrent = p.termsHead;
	while (pCurrent->GetNext() != NULL)
	{
		pCurrent = pCurrent->GetNext();
	}
	Term* current = termsHead;
	while (current->GetNext() != NULL)
	{
		current = current->GetNext();
	}

	*current /= *pCurrent;

	return *this;
}

#pragma endregion

#pragma region Global functions

int gcd(int num1, int num2)
{
	if (num2 == 0)
		return num1;
	return gcd(num2, num1 % num2);
}

string GetNextVar(string currentStr)
{
	return currentStr.substr(0, currentStr.find_first_of(OPERATORS));
}

char GetNextOperator(string currentStr)
{
	return currentStr[currentStr.find_first_of(OPERATORS)];
}

string GetNextStr(string currentStr)
{
	return currentStr.erase(0, currentStr.find_first_of(OPERATORS) + 1);
}

void PrintStack(stack<Polynomial> s)
{
	stack<Polynomial> tmp;
	
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

Polynomial DoOperation(Polynomial poly1, Polynomial poly2, char opr)
{
	switch (opr)
	{
	case '+':
		return poly1 + poly2;
	case '-':
		return poly1 - poly2;
	case '*':
		return poly1 * poly2;
	case '/':
		return poly1 / poly2;
	}
}

void TryPushOperator(char opr, stack<Polynomial>& polyStack, stack<char>& oprStack)
{
	// If _opr_ is prior, just push
	if (IfPrior(opr, oprStack))
		oprStack.push(opr);
	// Otherwise, do operation _num1_ _opr_ _num2_, push result to _polyStack_, try push _opr_ again
	else
	{
		Polynomial poly2 = polyStack.top();
		polyStack.pop();
		Polynomial poly1 = polyStack.top();
		polyStack.pop();
		char oprInStack = oprStack.top();
		oprStack.pop();

		polyStack.push(DoOperation(poly1, poly2, oprInStack));

		TryPushOperator(opr, polyStack, oprStack);
	}
}

void FinalResult(stack<Polynomial> polyStack, stack<char> oprStack)
{
	// Do operation _num1_ _opr_ _num2_, push result to _polyStack_
	while (polyStack.size() > 1)
	{
		Polynomial poly2 = polyStack.top();
		polyStack.pop();
		Polynomial poly1 = polyStack.top();
		polyStack.pop();
		char oprInStack = oprStack.top();
		oprStack.pop();

		polyStack.push(DoOperation(poly1, poly2, oprInStack));
	}

	// Print final result
	cout << polyStack.top();
}

#pragma endregion

int main()
{
	stack<Polynomial> polyStack;
	stack<char> oprStack;

	string inputStr;
	cin >> inputStr;

	string currentStr = inputStr;
	string currentVar;
	char currentOpr;
	while (currentStr.find_first_of(OPERATORS) != string::npos)
	{
		// Read new number/variable and make a polynomial by number/variable
		currentVar = GetNextVar(currentStr);
		Polynomial p;
		Term t;
		if (isdigit(currentVar[0]))
			t.SetMul(stoi(currentVar));
		else
			t.SetVar(currentVar[0]);

		// Push the polynomial into _polyStack_
		p.PushTerm(t);
		polyStack.push(p);

		// Read new operator and try to push operator into _oprStack_
		currentOpr = GetNextOperator(currentStr);
		TryPushOperator(currentOpr, polyStack, oprStack);

		// Move to next position
		currentStr = GetNextStr(currentStr);
		PrintStack(polyStack);
	}

	// Push last number/variable into _polyStack_
	currentVar = GetNextVar(currentStr);
	Polynomial p;
	Term t;
	if (isdigit(currentVar[0]))
		t.SetMul(stoi(currentVar));
	else
		t.SetVar(currentVar[0]);
	p.PushTerm(t);
	polyStack.push(p);

	// Do the rest of operation and print final result
	FinalResult(polyStack, oprStack);

	return 0;
}

