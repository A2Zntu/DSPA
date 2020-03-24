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
//                        QueueInterface
//=========================================================================

template<class ItemType>
class QueueInterface

{
	public:
		virtual bool isEmpty() const = 0;
		virtual bool enqueue(const ItemType& newEntry) = 0;
		virtual bool dequeue() = 0;
		virtual ItemType peekFront() const = 0;
		
};



//=========================================================================
//                        Linked Queue
//=========================================================================


template<class ItemType>
class LinkedQueue : public QueueInterface<ItemType> {
	private:
		Node<ItemType>* frontPtr;
		Node<ItemType>* backPtr;
		int itemCount;

	public:
		LinkedQueue();
		LinkedQueue  (const LinkedQueue& aQueue);
		~LinkedQueue();

		bool isEmpty() const;
		bool enqueue(const ItemType& newEntry);
		bool dequeue();
		void clear();
		void print() const;
		ItemType peekFront() const throw(PrecondViolatedExcep);
		Node<ItemType>* getFrontPtr() const; 
};



template <class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : frontPtr(nullptr), backPtr(nullptr), itemCount(0) {
}


template <class ItemType>
LinkedQueue<ItemType>::~LinkedQueue() {
	clear();
}


template <class ItemType>
LinkedQueue<ItemType>::LinkedQueue( const LinkedQueue& aQueue) :
	frontPtr(aQueue.frontPtr),  backPtr(aQueue.backPtr), itemCount(aQueue.itemCount) {
}



template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template <class ItemType>
void LinkedQueue<ItemType>::clear() {
	if(frontPtr != nullptr) {
		dequeue();
		clear();
	}
}



template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry) {
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr;        // Insertion into empty queue
	else
		backPtr->setNext(newNodePtr); // Insertion into nonempty queue

	backPtr = newNodePtr;            // New node is at back

	itemCount ++;
	return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() {
	bool result = false;
	if (!isEmpty()) {
		// Queue is not empty; delete front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr) {
			// Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		} else
			frontPtr = frontPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}  // end if
	itemCount --;
	return result;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const throw(PrecondViolatedExcep) {
	if(isEmpty())
		throw PrecondViolatedExcep("peekFront() called with empty queue.");

	return frontPtr->getItem();

}

template<class ItemType>
void LinkedQueue<ItemType>::print() const {
	// print the left parenthesis

	Node<ItemType>* tempPtr = frontPtr;
	while(tempPtr != nullptr) {
		if(tempPtr -> getNext() != nullptr) {
			cout << tempPtr -> getItem() << ",";
		} else
			cout << tempPtr -> getItem(); // specail case: no comma
		tempPtr = tempPtr -> getNext();
	}
	delete tempPtr;
	tempPtr = nullptr;
	cout << endl;
}


template<class ItemType>
Node<ItemType>* LinkedQueue<ItemType>::getFrontPtr() const {
	return frontPtr; 
	
}


//=========================================================================
//                         deque
//=========================================================================


template<class ItemType>
class deque : public QueueInterface<ItemType> {
	private:
		Node<ItemType>* frontPtr;
		Node<ItemType>* backPtr;
		int itemCount;
		Node<ItemType>* getNodeAt(int position) const;

	public:
		deque();
		deque  (const deque& aQueue);
		~deque();

		bool isEmpty() const;
		bool enqueue(const ItemType& newEntry);  
		bool add_front(const ItemType& newEntry); 
		bool add_back(const ItemType& newEntry); 
		bool remove_front();
		bool remove_back();
		
		bool dequeue();
		void clear();
		void print() const;
		ItemType peekFront() const throw(PrecondViolatedExcep);
		Node<ItemType>* getFrontPtr() const; 
};



template <class ItemType>
deque<ItemType>::deque() : frontPtr(nullptr), backPtr(nullptr), itemCount(0) {
}


template <class ItemType>
deque<ItemType>::~deque() {
	clear();
}


template <class ItemType>
deque<ItemType>::deque(const deque& aQueue) :
	frontPtr(aQueue.frontPtr),  backPtr(aQueue.backPtr), itemCount(aQueue.itemCount) {
}


template<class ItemType>
Node<ItemType>* deque<ItemType>::getNodeAt(int position) const {
	// Debugging check of precondition
	assert( (position >= 1) && (position <= itemCount) );

	// Count from the beginning of the chain
	Node<ItemType>* curPtr = frontPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}  // end getNodeAt


template<class ItemType>
bool deque<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template <class ItemType>
void deque<ItemType>::clear() {
	if(frontPtr != nullptr) {
		dequeue();
		clear();
	}
}



template<class ItemType>
bool deque<ItemType>::enqueue(const ItemType& newEntry) {
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr;        // Insertion into empty queue
	else
		backPtr->setNext(newNodePtr); // Insertion into nonempty queue

	backPtr = newNodePtr;            // New node is at back

	itemCount ++;
	return true;
}  // end enqueue



template<class ItemType>
bool deque<ItemType>::add_back(const ItemType& newEntry) {
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	if (isEmpty())
		frontPtr = newNodePtr;        
	else
		backPtr->setNext(newNodePtr); 

	backPtr = newNodePtr;            

	itemCount ++;
	return true;
}  

template<class ItemType>
bool deque<ItemType>::add_front(const ItemType& newEntry) {
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	if (isEmpty())
		frontPtr = newNodePtr;        
	else
		newNodePtr->setNext(frontPtr); 

	frontPtr = newNodePtr;            

	itemCount ++;
	return true;
}  



template<class ItemType>
bool deque<ItemType>::dequeue() {
	bool result = false;
	if (!isEmpty()) {
		// Queue is not empty; delete front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr) {
			// Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		} else
			frontPtr = frontPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}  // end if
	itemCount --;
	return result;
}



template<class ItemType>
bool deque<ItemType>::remove_front() {
	bool result = false;
	if (!isEmpty()) {
		// Queue is not empty; delete front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr) {
			// Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		} else
			frontPtr = frontPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}  // end if
	itemCount --;
	return result;
}

template<class ItemType>
bool deque<ItemType>::remove_back() {
	bool result = false;
	if (!isEmpty()) {
		if (frontPtr == backPtr) {
			// Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		} else{
			Node<ItemType>* prevPtr = getNodeAt(itemCount - 1);
			prevPtr->setNext(backPtr->getNext());
			backPtr = prevPtr; 
		}

		result = true;
	}  // end if
	itemCount --;
	return result;
}



template<class ItemType>
ItemType deque<ItemType>::peekFront() const throw(PrecondViolatedExcep) {
	if(isEmpty())
		throw PrecondViolatedExcep("peekFront() called with empty queue.");

	return frontPtr->getItem();

}

template<class ItemType>
void deque<ItemType>::print() const {
	// print the left parenthesis

	Node<ItemType>* tempPtr = frontPtr;
	while(tempPtr != nullptr) {
		if(tempPtr -> getNext() != nullptr) {
			cout << tempPtr -> getItem() << ",";
		} else
			cout << tempPtr -> getItem(); // specail case: no comma
		tempPtr = tempPtr -> getNext();
	}
	delete tempPtr;
	tempPtr = nullptr;
	cout << endl;
}


template<class ItemType>
Node<ItemType>* deque<ItemType>::getFrontPtr() const {
	return frontPtr; 
	
}





//=========================================================================
//                        Queue Micro Function
//=========================================================================
template<class ItemType>
void display(LinkedQueue<ItemType>& aQueue) {

	Node<ItemType>* tempPtr = aQueue.getFrontPtr();
	while(tempPtr != nullptr) {
		if(tempPtr -> getNext() != nullptr) {
			cout << tempPtr -> getItem() << ",";
		} else
			cout << tempPtr -> getItem(); // specail case: no comma
		tempPtr = tempPtr -> getNext();
	}
	delete tempPtr;
	tempPtr = nullptr;
	cout << endl;

}


template<class ItemType>
void display(deque<ItemType>& aQueue) {

	Node<ItemType>* tempPtr = aQueue.getFrontPtr();
	while(tempPtr != nullptr) {
		if(tempPtr -> getNext() != nullptr) {
			cout << tempPtr -> getItem() << ",";
		} else
			cout << tempPtr -> getItem(); // specail case: no comma
		tempPtr = tempPtr -> getNext();
	}
	delete tempPtr;
	tempPtr = nullptr;
	cout << endl;

}


//=========================================================================
//                        Main Function
//=========================================================================
int main() {

	deque<int> aQueue;
//	aQueue.add_back(3);
//	aQueue.add_back(7);
//	aQueue.add_back(5);
//	aQueue.add_front(6); 
//	display(aQueue); 
//	
	aQueue.clear();
	aQueue.add_back(5);
	aQueue.add_back(8);
	aQueue.add_back(8);
	aQueue.add_back(9);
	aQueue.remove_back();
	display(aQueue); 
	
//	aQueue.add_back(10);
//	aQueue.add_front(43);
//	aQueue.remove_back();
//	display(aQueue); 

	return 0;
}



