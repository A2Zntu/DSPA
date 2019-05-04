#include<iostream>
#include<stdexcept>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

template<class ItemType>
class Node {
	private:
		ItemType item;
		Node<ItemType>* next;
	public:
		Node();
		Node(const ItemType& anItem);
		Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
		void setItem(const ItemType& anItem);
		void setNext(Node<ItemType>* nextNodePtr);
		ItemType getItem() const;
		Node<ItemType>* getNext() const;
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr) {
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) {
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr) {
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
	item = anItem;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr) {
	next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const {
	return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
	return next;
}


//=========================================================================
//                        Exception
//=========================================================================
class PrecondViolatedExcep : public logic_error {
	public:
		PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("Precondition Violated Exception: " + message) {
}


//=========================================================================
//                        ListInterface
//=========================================================================


template<class ItemType>
class ListInterface {
	public:
		virtual bool isEmpty() const = 0;
		virtual int getLength() const = 0;
		virtual void append(const ItemType& newEntry) = 0;
		virtual void insert(int newPosition, const ItemType& newEntry) = 0;
		virtual void remove(const ItemType& elmt) = 0;
		virtual void clear() = 0;

		virtual void print() const = 0;
		virtual void reverse() = 0;
		virtual int index(const ItemType& elmt) const = 0;
		virtual int count(const ItemType& elmt) const = 0;
		virtual void sort() = 0;
		virtual void swap(Node<ItemType>* leftNode, Node<ItemType>* rightNode) = 0;
		virtual void doubleList() = 0;

};


//=========================================================================
//                        Linked List
//=========================================================================


template<class ItemType>
class LinkedList : public ListInterface<ItemType> {
	private:
		Node<ItemType>* headPtr; // Pointer to first node in the chain;
		// (contains the first entry in the list)
		int itemCount;           // Current count of list items

		Node<ItemType>* getNodeAt(int position) const;

	public:
		LinkedList();
		LinkedList(const LinkedList<ItemType>& aList);
		virtual ~LinkedList();

		bool isEmpty() const;
		int getLength() const;
		void clear();

		// new function
		void insert(int newPosition, const ItemType& newEntry);
		void append(const ItemType& newEntry);
		void extend(const LinkedList& anotherList);
		void print() const;
		int index(const ItemType& elmt) const;
		int count(const ItemType& elmt) const;
		void remove(const ItemType& elmt);
		void reverse();
		void sort();
		void swap(Node<ItemType>* leftNode, Node<ItemType>* rightNode);
		void doubleList();

}; // end LinkedList header

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0) {
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
	clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const {
	return itemCount;
}  // end getLength

template<class ItemType>
void LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry) {
	bool ableToInsert = (newPosition >= 0) && (newPosition <= itemCount);
	if (ableToInsert) {
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

		// Attach new node to chain
		if (newPosition == 0) {
			// Insert new node at beginning of chain
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
			itemCount++;
			return;
		} else {
			// Find node that will be before new node
			Node<ItemType>* prevPtr = getNodeAt(newPosition);

			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
			itemCount++;
			return;

		}  // end if
	} else {
		// if the size
//		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
//		Node<ItemType>* lastNodePtr = getNodeAt(itemCount);
//		newNodePtr->setNext(lastNodePtr->getNext());
//		//newNodePtr->setNext(nullptr);
//		lastNodePtr->setNext(newNodePtr);
//		itemCount++;
		this -> append(newEntry); 
		return; 

	}
	
}



template<class ItemType>
void LinkedList<ItemType>::clear() {
	while (!isEmpty())
		remove(1);
}  // end clear



template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const {
	// Debugging check of precondition
	//assert( (position >= 0) && (position <= itemCount) );

	// Count from the beginning of the chain
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}  // end getNodeAt



// =================== LinkedList  New Function ==============================

template <class ItemType>
int LinkedList<ItemType>::index(const ItemType& elmt) const {
	int pos = 0;
	bool findElmt = false;
	Node<ItemType>* currentPtr = headPtr;
	while(currentPtr != nullptr && findElmt == false) {
		ItemType tempelmt =  currentPtr -> getItem();
		if(tempelmt == elmt)
			return pos;
		else {
			currentPtr = currentPtr -> getNext();
			pos++;
		}
	}
	return -1;
}


template <class ItemType>
int LinkedList<ItemType>::count(const ItemType& elmt) const {

	int elmtCount = 0;
	Node<ItemType>* currentPtr = headPtr;
	while(currentPtr != nullptr) {
		ItemType tempelmt =  currentPtr -> getItem();
		if(tempelmt == elmt) {
			elmtCount ++;
			currentPtr = currentPtr -> getNext();
		} else
			currentPtr = currentPtr -> getNext();
	}
	return elmtCount;
}


template<class ItemType>
void LinkedList<ItemType>::append(const ItemType& newEntry) {
	// Create a new node containing the new entry
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	if (headPtr == nullptr) {

		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
		itemCount++;
		return;
	} else {
		// Last Node
		//cout << "itemCount: " << itemCount << endl;
		Node<ItemType>* lastPtr = getNodeAt(itemCount);
		newNodePtr->setNext(lastPtr->getNext());
		lastPtr->setNext(newNodePtr);
	}

	itemCount++;
}


template<class ItemType>
void LinkedList<ItemType>::doubleList() {
	// double the linkedlist
	if (headPtr == nullptr) {
		return;
	} else {
		Node<ItemType>* currentPtr = headPtr;
		int i = 0;
		int origItemCount = itemCount;
		while(currentPtr != nullptr && i < origItemCount) {
//			cout << currentPtr ->getItem() << endl;
			this -> append(currentPtr ->getItem());
			currentPtr = currentPtr->getNext();
			i++;
		}
	}
//	itemCount = itemCount*2;
}


template <class ItemType>
void LinkedList<ItemType>::extend(const LinkedList& anotherList) {
	Node<ItemType>* currentPtr = anotherList.headPtr;
	while(currentPtr != nullptr) {
		this -> append(currentPtr ->getItem());
		currentPtr = currentPtr->getNext();
	}
}

template<class ItemType>
void LinkedList<ItemType>::remove(const ItemType& elmt) {
	int findelmt = count(elmt);
	Node<ItemType>* curPtr = nullptr;
	if (findelmt > 0) {
		int pos = index(elmt);
		if(pos == 0) {
			curPtr = headPtr;
			headPtr = headPtr -> getNext();
		} else {
			Node<ItemType>* prevPtr = getNodeAt(pos);
			curPtr = prevPtr -> getNext();
			prevPtr -> setNext(curPtr -> getNext());
		}
		delete curPtr;
		curPtr = nullptr;
		itemCount--;  // Decrease count of entries
	}
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::reverse() {
	// List is empty or only one element
	if(headPtr == nullptr || headPtr -> getNext() == nullptr)
		return;
	Node<ItemType>* prevPtr = nullptr;
	Node<ItemType>* curPtr = headPtr;
	Node<ItemType>* precedPtr = headPtr -> getNext();

	while(precedPtr != nullptr) {
		curPtr -> setNext(prevPtr);
		prevPtr = curPtr;
		curPtr = precedPtr;
		precedPtr = precedPtr -> getNext();
	}

	curPtr -> setNext(prevPtr);
	headPtr = curPtr;

}  // end reverse


template<class ItemType>
void LinkedList<ItemType>::sort() {
	if(headPtr == nullptr || headPtr -> getNext() == nullptr)
		return;
	Node<ItemType>* tempPtr;
	Node<ItemType>* lPtr = nullptr;
	int swapped = 0;
	do {
		// reset the swapped = 0, reset the tempPtr = headPtr
		swapped = 0;
		tempPtr = headPtr;
		while(tempPtr -> getNext() != lPtr) {
			if(tempPtr -> getItem() > tempPtr -> getNext() -> getItem()) {
				swap(tempPtr, tempPtr -> getNext());
				swapped = 1;
			}
			tempPtr = tempPtr -> getNext();
		}
		lPtr = tempPtr;

	} while(swapped);
}  // end sort


template<class ItemType>
void LinkedList<ItemType>::swap(Node<ItemType>* leftNode, Node<ItemType>* rightNode) {
	ItemType tempItem = leftNode -> getItem();
	leftNode -> setItem(rightNode -> getItem());
	rightNode -> setItem(tempItem);
}



template <class ItemType>
void LinkedList<ItemType>::print() const {
	// print the left parenthesis
	cout << "[";
	Node<ItemType>* tempPtr = headPtr;
	while(tempPtr != nullptr) {
		if(tempPtr -> getNext() != nullptr) {
			cout << tempPtr -> getItem() << ",";
		} else
			cout << tempPtr -> getItem(); // specail case: no comma
		tempPtr = tempPtr -> getNext();
	}
	delete tempPtr;
	tempPtr = nullptr;
	cout << "]" << endl;
}


//=========================================================================
//                       Struct List
//=========================================================================

struct newList {
	string name;
	LinkedList<int>* LL = new LinkedList<int>;
};


void vectorPrint(vector<newList>& ve) {
	cout << "Vector Print" << endl;
	for(int i = 0; i < ve.size(); i++) {
		ve[i].LL -> print();
	}
}

void actionByList(vector<newList>& ve, const string& listName, const string& action,
                  const int num1, const int num2, const string& anotherListName) throw(PrecondViolatedExcep) {
	for(int i = 0; i < ve.size(); i++) {
		if(ve[i].name == listName) {
			if(action == "append")
				ve[i].LL -> append(num1);

			else if (action == "count") {
				int Cnt = ve[i].LL -> count(num1);
				cout << Cnt << endl;
			}

			else if (action == "index") {
				int indexPos = ve[i].LL -> index(num1);
				cout << indexPos << endl;
			}

			else if (action == "remove")
				ve[i].LL -> remove(num1);

			else if (action == "insert")
				ve[i].LL -> insert(num1, num2);

			else if (action == "reverse")
				ve[i].LL -> reverse();

			else if (action =="sort")
				ve[i].LL -> sort();

			else if (action == "print")
				ve[i].LL -> print();

			else if (action == "extend") {
				for(int j = 0; j < ve.size(); j++) {
					if(listName == anotherListName) {
						ve[i].LL -> doubleList();
						break;
					}
					if(ve[j].name == anotherListName) {
						ve[i].LL -> extend(*(ve[j].LL));
						break;
					}
				}
			} else {
				string message = "not defined action";
				throw(PrecondViolatedExcep(message));
			}
			break;
		}


	}
}



//=========================================================================
//                        Main Function
//=========================================================================
int main() {

	vector<newList> Lists;
	string line;
	// The delimiters
	string initializer = " = ";
	string dot = ".";
	string deleimter = ",";
	string leftB = "(";
	string rightB = ")";

	while(getline(cin, line)) {
		//cout << line;

		string listName, action, anotherListName;
		int num1 = 0;
		int num2 = 0;
		size_t last = 0;
		size_t next = 0;
		newList temp;
		// Initailizer case
		if(line.find(initializer) != string::npos) {

			next = line.find(initializer, last);
			listName = line.substr(last, next-last);
			temp.name = listName;
			Lists.push_back(temp);
			action = "init";
			//cout << " -> " << temp.name << " " << action << endl;

		} else {
			// no init
			if(line.find(dot) == string::npos) {
				// special case; print function
				action = "print";
				listName = line;
				//cout << " -> " << listName << " " << action << endl;

			} else {
				// List name
				next = line.find(dot, last);
				listName = line.substr(last, next-last);
				last = next + 1;
				// List action
				next = line.find(leftB, last);
				action = line.substr(last, next-last);
				last = next + 1;

				if(action == "reverse" || action == "sort" ) {
					// need nothing to do
				} else if(action == "insert") {
					next = line.find(deleimter, last);
					num1 = stoi(line.substr(last, next-last));
					last = next + 1;

					next = line.find(rightB, last);
					num2 = stoi(line.substr(last, next-last));

				} else if(action == "extend") {
					next = line.find(rightB, last);
					anotherListName = line.substr(last, next-last);

				} else {
					next = line.find(rightB, last);
					num1 = stoi(line.substr(last, next-last));
				}

//				cout << " -> " << listName << " " << action
//				     << " " << num1 << " " << num2 << endl;
			}
			actionByList(Lists, listName, action, num1, num2, anotherListName);
		}

		if(cin.eof())
			break;
	}
//	cout << "-----------------" << endl;
//	vectorPrint(Lists);


	return 0;
}

