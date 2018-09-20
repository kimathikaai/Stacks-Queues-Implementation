#include "DynamicStack.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

typedef DynamicStack::StackItem StackItem;  // for simplicity
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
  capacity_ = 16;
  init_capacity_ = 16;
  size_ = 0;
  items_ = new StackItem[init_capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity)
{
  if(capacity == 0)
  	init_capacity_ = capacity_ = 16;
  else
    init_capacity_ = capacity_ = capacity;

  size_ = 0;
  items_ = new StackItem[init_capacity_];

}

DynamicStack::~DynamicStack()
{
  delete[] items_;
  items_ = NULL;
}

bool DynamicStack::empty() const
{
  return size_ == 0;
}

int DynamicStack::size() const
{
  return size_;
}

void DynamicStack::push(StackItem value)
{

  if( size_ >= capacity_)
  {
    StackItem* temp = items_;

    items_ = new StackItem[capacity_*2];
    for( int i = 0; i < size_; ++i )
      items_[i] = temp[i];

    delete[] temp;
    capacity_ *= 2;
  }

  items_[size_] = value;
  ++size_;
}

StackItem DynamicStack::pop()
{
  if(empty())
    return EMPTY_STACK;


  StackItem top = items_[size_-1];
  items_[size_-1] = 0;
  size_--;

  if(size_ <= (capacity_/4) && capacity_/2 >= init_capacity_)
/* Original it Condition checked for capacity_/4 >= init_capacity
	instead of: capacity_/2 >= init_capacity
*/
  {
    StackItem* temp = items_;
    items_ = new StackItem[capacity_/2];
    //Original Code quartered the capacity instead of halving it
    for(int i = 0; i < size_; i++)
      items_[i] = temp[i];
    delete[] temp;
    capacity_ /= 2;
    //Original Code quartered capacity instead of halving it
  }
  return top;
}

StackItem DynamicStack::peek() const
{
  if(empty())
    return 	EMPTY_STACK;

  return items_[size_-1];
}

void DynamicStack::print() const
{
  if(empty())
  	cout << "Empty Stack!";

  for(int i = 0; i <size_; ++i)
    cout << items_[i] << " ";
}