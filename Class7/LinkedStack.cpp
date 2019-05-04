#include<iostream>
#include<stdexcept>
using namespace std;

template<class ItemType>
class StackInterface
{
public :
  /** Sees whether this stack is empty.
      @return True if the stack is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Adds a new entry to the top of this stack.
      @post If the operation was successful, newEntry is at the top of the stack.
      @param newEntry The object to be added as a new entry.
      @return True if the addition is successful or false if not. */
  virtual bool push( const ItemType& newEntry) = 0;

  /** Removes the top of this stack.
      @post If the operation was successful, the top of the stack has been removed.
      @return True if the removal is successful or false if not. */
  virtual bool pop() = 0;

  /** Returns the top of this stack.
      @pre The stack is not empty.
      @post The top of the stack has been returned, and the stack is unchanged.
      @return The top of the stack. */
  virtual ItemType peek() const = 0;
}; 














template<class ItemType>
class Node
{
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
Node<ItemType>::Node() : next(nullptr)
{
} 

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} 

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
                item(anItem), next(nextNodePtr)
{
} 

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
} 

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
} 

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
  return item;
} 

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
} 












template<typename ItemType>
class LinkedStack : public StackInterface<ItemType>
{
private:
  Node<ItemType>* topPtr; // Pointer to first node in the chain;
                          // this node contains the stack's top
public:
  // Constructors and destructor:
  LinkedStack(); // Default constructor
  LinkedStack(const LinkedStack<ItemType>& aStack); // Copy constructor
  virtual ~LinkedStack(); // Destructor
  // Stack operations:
  bool isEmpty() const;
  bool push( const ItemType& newItem);
  bool pop();
  ItemType peek() const;
};

template<typename ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
} 

template<typename ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
  // Point to nodes in original chain
  Node<ItemType>* origChainPtr = aStack.topPtr; // typo in the textbook
  if(origChainPtr == nullptr)
    this->topPtr = nullptr; // Original bag is empty
  else
  {
    // Copy first node
    topPtr = new Node<ItemType>();
    topPtr->setItem(origChainPtr->getItem());
    Node<ItemType>* newChainPtr = topPtr;
    // Copy remaining nodes
    while(origChainPtr->getNext() != nullptr) // typo in the textbook
    {
      origChainPtr = origChainPtr->getNext();
      ItemType nextItem = origChainPtr->getItem();
      Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
      newChainPtr->setNext(newNodePtr);
      newChainPtr = newChainPtr->getNext();
    } 
    newChainPtr->setNext(nullptr); // Mark the bottom of stack
  } 
} 

template<typename ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
  // Pop until stack is empty
  while(!isEmpty())
    pop();
} 

template<typename ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
  return topPtr == nullptr;
} 

template<typename ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
  Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
  topPtr = newNodePtr;
  return true;
} 

template<typename ItemType>
bool LinkedStack<ItemType>::pop()
{
  bool result = false ;
  if(!isEmpty())
  {
    // Stack is not empty; delete top
    Node<ItemType>* nodeToDeletePtr = topPtr;
    topPtr = topPtr->getNext();
    delete nodeToDeletePtr;
    result = true ;
  } 
  return result;
} 

template<typename ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
  if(!this->isEmpty()) // check precondition
    return topPtr->getItem();
  else
    throw logic_error("...");
}







int main()
{
  LinkedStack<int> ls;
  ls.push(4);
  ls.push(11);
  LinkedStack<int> lsCopy(ls);
  lsCopy.pop();
  try
  {
    cout << lsCopy.peek() << endl;
    cout << ls.peek() << endl;
  }
  catch(logic_error e)
  {
    cout << "empty!" << endl;
  }
}






