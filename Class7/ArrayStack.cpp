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










const int MAX_STACK = 999; // set a value by yourself

template<typename ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
  ItemType items[MAX_STACK]; // Array of stack items
  int top; // Index to top of stack
public:
  ArrayStack(); // Default constructor
  bool isEmpty() const;
  bool push(const ItemType& newEntry);
  bool pop();
  ItemType peek() const;
}; 

template<typename ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
} 

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
  return top < 0;
} 

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
  bool result = false ;
  if(this->top < MAX_STACK - 1) // still have room
  {
    top++;
    this->items[top] = newEntry;
    result = true ;
  } 
  return result;
} 

template<typename ItemType>
bool ArrayStack<ItemType>::pop()
{
  bool result = false ;
  if(!this->isEmpty())
  {
    top--;
    result = true ;
  }
  return result;
} 

template<typename ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
  if(!this->isEmpty()) // check precondition
    return items[top];
  else
    throw logic_error("...");
} 






int main()
{
  StackInterface<int>* as = new ArrayStack<int>();
  as->push(4);
  as->push(11);
  as->pop();
  try
  {
    cout << as->peek() << endl;
  }
  catch(logic_error e)
  {
    cout << "empty!" << endl;
  }
  as->pop();
  try
  {
    cout << as->peek() << endl;
  }
  catch(logic_error e)
  {
    cout << "empty!" << endl;
  }
}






