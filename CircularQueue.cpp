#include <cstring>
#include <iostream>
#include "CircularQueue.hpp"
using namespace std;


typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
	items_ = new QueueItem[16];
	head_ = tail_ = size_= 0;
  capacity_ = 16;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
	if(capacity == 0)
		capacity_ = 16;
	else
		capacity_ = capacity;

/* Original code had this line here: capacity_ = capacity;
 * Omitted this line of code because it would make the
 * 'if' statement on line 19 useless because the capacity would
 * still be set to zero
 */

  items_ = new QueueItem[capacity_];
	head_ = tail_ = size_= 0;

}

CircularQueue::~CircularQueue()
{
  delete[] items_;
  items_ = NULL;
}

bool CircularQueue::empty() const
{
	return size_==0;
/*
 * Original return statement was: return head_== tail_;
 * This is wrong because this case would be satisfied if the
 * circular queue was full
 */
}

bool CircularQueue::full() const
{
  return size_ == capacity_;
}

int CircularQueue::size() const
{
  return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
  if( full() )
    return false;

  items_[tail_] = value;
  tail_=(tail_+1)% capacity_;

  /*Removed

   if( tail_ >= capacity_ )
    tail_ = 0;

  items_[tail_] = value;
  ++tail_;
  */
  ++size_;
  return true;

}

QueueItem CircularQueue::dequeue()
{
  if(empty())
  {
    return EMPTY_QUEUE;
  }

  QueueItem returnItem = items_[head_];

  head_ = (head_+1)%capacity_;

 /*Removed
  if(head_ + 1 >= capacity_)
    head_ = 0;
  else
    ++head_;
    */
  size_--;
  return returnItem;
}

QueueItem CircularQueue::peek() const
{
  if( empty() )
    return EMPTY_QUEUE;

  QueueItem item = items_[head_];

  return item;
}

void CircularQueue::print() const
{
  if( empty() )
    cout << "Empty Queue!";
  else
	  for( int i = 0; i < size(); i++)
		  cout << items_[(head_+i)%capacity_] << endl;

}
