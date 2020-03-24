#include<iostream>
#include<stdexcept>
#include <cassert>
#include <string>
#include <vector>
#include <math.h>
using namespace std;



bool debugQueueMode = false;


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
double delaytime(LinkedQueue<ItemType>& aQueue, LinkedQueue<ItemType>& wQueue) {
	int custCnt = 0;
	double avlTime = 0.0;
	double delayTime = 0.0;
	while(!aQueue.isEmpty()) {
		double arriveTime = aQueue.peekFront();
		double workTime = wQueue.peekFront();
		double realStartTime = max(arriveTime, avlTime);
		double endTime = realStartTime + workTime;
		delayTime = delayTime + (realStartTime - arriveTime);
		avlTime = endTime;
		aQueue.dequeue();
		wQueue.dequeue();
		custCnt ++;
	}
	delayTime = delayTime/custCnt;
	return delayTime;
}





//=========================================================================
//                        Main Function
//=========================================================================
int main() {

	LinkedQueue<double> aQueue;
	LinkedQueue<double> wQueue;

	int custCnt = 0;
	double lambda, mu, W;

	cin >> custCnt >> lambda >> mu;

	W = lambda/(mu*(mu-lambda));

	cin.ignore();
	cin.clear();
	string line;
	double arriveTime, workTime;
	while(custCnt > 0) {

		if(cin >> arriveTime >> workTime) {
			aQueue.enqueue(arriveTime);
			wQueue.enqueue(workTime);
		}
		custCnt --; 


//		cout << "arriveTime: " << arriveTime << " "
//		     << "workTime :" << workTime << endl;



		if(cin.eof())
			break;
	}
	
	if(debugQueueMode) {
		cout << endl;
		cout << "W " << W << endl;
		cout << "arriveTime: " << endl;
		display(aQueue);
		cout << "workTime: " << endl;
		display(wQueue);
	}

	double dTime = delaytime(aQueue, wQueue);
	double error = 0.0;
	error = ((dTime - W)/W)*100;
	//cout << "dTime: " << dTime << endl;
	cout  << round(error);


	return 0;
}



