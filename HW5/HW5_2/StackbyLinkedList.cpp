#include<iostream>
#include<stdexcept>
#include <cassert>
#include <string>
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
		virtual bool insert(int newPosition, const ItemType& newEntry) = 0;
		virtual bool remove(int position) = 0;
		virtual void clear() = 0;
		virtual ItemType getEntry(int position) const = 0;
		//virtual void setEntry(int position, const ItemType& newEntry) = 0;
};


//=========================================================================
//                        Linked List
//=========================================================================


template<class ItemType>
class StackList : public ListInterface<ItemType> {
	private:
		Node<ItemType>* topPtr; // Pointer to first node in the chain;
		// (contains the first entry in the list)
		int itemCount;           // Current count of list items

		Node<ItemType>* getNodeAt(int position) const;

	public:
		StackList();
		StackList(const StackList<ItemType>& aList);
		virtual ~StackList();

		bool isEmpty() const;
		int getLength() const;
		bool insert(int newPosition, const ItemType& newEntry);
		bool remove(int position);
		void clear();
		ItemType top() const;
		void pop(); 
		void push(const ItemType& elmt); 

		ItemType getEntry(int position) const throw(PrecondViolatedExcep);
		//void setEntry(int position, const ItemType& newEntry)throw(PrecondViolatedExcep);
		ItemType getLastEntry() const throw(PrecondViolatedExcep);
		

};

template<class ItemType>
StackList<ItemType>::StackList() : topPtr(nullptr), itemCount(0) {
}  // end default constructor

template<class ItemType>
StackList<ItemType>::~StackList() {
	clear();
}  // end destructor

template<class ItemType>
bool StackList<ItemType>::isEmpty() const {
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int StackList<ItemType>::getLength() const {
	return itemCount;
}  // end getLength

template<class ItemType>
bool StackList<ItemType>::insert(int newPosition, const ItemType& newEntry) {
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert) {
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

		// Attach new node to chain
		if (newPosition == 1) {
			// Insert new node at beginning of chain
			newNodePtr->setNext(topPtr);
			topPtr = newNodePtr;
		} else {
			// Find node that will be before new node
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		}  // end if

		itemCount++;
	}

	return ableToInsert;
}

template<class ItemType>
bool StackList<ItemType>::remove(int position) {
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove) {
		Node<ItemType>* curPtr = nullptr;
		if (position == 1) {
			// Remove the first node in the chain
			curPtr = topPtr; // Save pointer to node
			topPtr = topPtr->getNext();
		} else {
			// Find node that is before the one to delete
			Node<ItemType>* prevPtr = getNodeAt(position - 1);

			// Point to node to delete
			curPtr = prevPtr->getNext();

			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		}  // end if

		// Return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;

		itemCount--;  // Decrease count of entries
	}  // end if

	return ableToRemove;
}  // end remove

template<class ItemType>
void StackList<ItemType>::clear() {
	while (!isEmpty())
		remove(1);
}  // end clear

template<class ItemType>
ItemType StackList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep) {
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet) {
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	} else {
		string message = "getEntry() called with an empty list or ";
		message  = message + "invalid position.";
		throw(PrecondViolatedExcep(message));
	}  // end if
}  // end getEntry

template<class ItemType>
Node<ItemType>* StackList<ItemType>::getNodeAt(int position) const {
	// Debugging check of precondition
	assert( (position >= 1) && (position <= itemCount) );

	// Count from the beginning of the chain
	Node<ItemType>* curPtr = topPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}  // end getNodeAt

template <class ItemType>
ItemType StackList<ItemType>::top() const {
	if(!getLength() == 0) {
		return topPtr->getItem();
	}
}

template <class ItemType>
void StackList<ItemType>::pop() {
	
	if(!getLength() == 0){
		Node<ItemType>* node2DeletePtr = topPtr;
		topPtr = topPtr->getNext(); 
		delete node2DeletePtr; 
		node2DeletePtr = nullptr; 
		itemCount--;  
		
	}else{
		cout << "it is empty stack, can not pop!" << endl; 
	}
}


template <class ItemType>
void StackList<ItemType>::push(const ItemType& elmt) {
	
	if(!getLength() == 0){
		Node<ItemType>* newNode = new Node<ItemType>(elmt);
		newNode->setNext(topPtr); 
		topPtr = newNode; 
		itemCount++;  
		
	}else{
		topPtr = new Node<ItemType>(elmt); 
		itemCount++; 
	}
}




//=========================================================================
//                        Main Function
//=========================================================================
int main() {

    StackList<int> s;
    s.pop();
    s.push(32);
    s.push(4);
    cout << "\ntop: " << s.top() << "\nsize: " << s.getLength() << endl;        
    s.push(15);
    cout << "\ntop: " << s.top() << "\nsize: " << s.getLength() << endl;         
    s.pop();
    s.pop();
    cout << "\ntop: " << s.top() << "\nsize: " << s.getLength() << endl;          
    s.pop();
    cout << "\ntop: " << s.top() << "\nsize: " << s.getLength() << endl;


	return 0;
}

