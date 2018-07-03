#ifndef QUEUE
#define QUEUE

#include <algorithm>
#include <iostream>

namespace Queue_ADT{

template <typename T>
class Queue{

  public:
   Queue();
   Queue(const Queue &queue_to_copy);
   Queue(Queue &&queue_to_move);
   Queue & operator=(const Queue &queue_to_copy);
   Queue & operator=(Queue &&queue_to_move);
   ~Queue();
   bool isEmpty() const;
   int size() const;
   void enqueue(const T &item);
   const T & front() const;
   const T & back() const;
   void clear();
   T dequeue();
   void QueueSwap(Queue &rhs);
   void PrintQueue() const;

  private:
   struct node{
     T data;
     node *next_node;
     node(){
       next_node = nullptr;
     }
     node(T item) : data(item), next_node(nullptr) {}
   };
   node *head_;
   node *tail_;
   int size_;
   void DeleteNode();
};

template <typename T>
Queue<T>::Queue(){
  tail_ = new node();
  head_ = new node();
  tail_->next_node = head_;
  head_->next_node = tail_;
  size_ = 0;
  --size_;
}

template <typename T>
Queue<T>::~Queue(){
  for(int i = 0; i < size(); ++i){
    DeleteNode();
  }
  head_->next_node = tail_->next_node = nullptr;
  delete head_;
  delete tail_;
}

template <typename T>
Queue<T>::Queue(const Queue<T> & queue_to_copy){
  head_ = new node();
  tail_ = new node();
  tail_->next_node = head_;
  head_->next_node = tail_;
  size_ = 0;
  node *itr = queue_to_copy.head_->next_node;
  for(int i = 0; i < queue_to_copy.size(); ++i){
    enqueue(itr->data);
    itr = itr->next_node;
  }
}

template <typename T>
Queue<T>::Queue(Queue<T> && queue_to_move){
  head_ = new node();
  tail_ = new node();
  size_ = queue_to_move.size_;
  head_ = queue_to_move.head_;
  tail_ = queue_to_move.tail_;
  queue_to_move.head_->next_node = nullptr;
  queue_to_move.tail_->next_node = nullptr;
}

template <typename T>
Queue<T> & Queue<T>::operator=(const Queue<T> & queue_to_copy){
  Queue<T> copy = queue_to_copy;
  swap(*this, copy);
  return *this;
}

template <typename T>
Queue<T> & Queue<T>::operator=(Queue<T> && queue_to_move){
  swap(*this, queue_to_move);
  return *this;
}

template <typename T>
void Queue<T>::enqueue(const T &item){
  node *new_node = new node(item);
  new_node->next_node = tail_;
  tail_->next_node->next_node = new_node;
  tail_->next_node = new_node;
  ++size_;
}

template <typename T>
T Queue<T>::dequeue(){
  node *node_to_pop = head_->next_node;
  head_->next_node = node_to_pop->next_node;
  node_to_pop->next_node = nullptr;
  T item = node_to_pop->data;
  --size_;
  delete node_to_pop;
  return item;
}

template <typename T>
const T & Queue<T>::back() const{
  return tail_->next_node->data;
}

template <typename T>
const T & Queue<T>::front() const{
  head_->next_node->data;
}

template <typename T>
bool Queue<T>::isEmpty() const{
  return size_ == 0;
}

template <typename T>
int Queue<T>::size() const{
  return size_;
}

template <typename T>
void Queue<T>::DeleteNode(){
  node *node_to_delete = head_->next_node;
  head_->next_node = node_to_delete->next_node;
  node_to_delete->next_node = nullptr;
  delete node_to_delete;
}

template <typename T>
void Queue<T>::clear(){
  for(int i = 0; i < size(); ++i){
    DeleteNode();
  }
  head_->next_node = tail_;
  tail_->next_node = head_;
}

template <typename T>
void Queue<T>::PrintQueue() const{
  if(isEmpty()){
    std::cout << "Queue is empty.\n";
    return;
  }
  node *itr = head_->next_node;
  for(int i = 0; i < size_; ++i){
    std::cout << itr->data << " ";
    itr = itr->next_node;
  }
}

template <typename T>
void Queue<T>::QueueSwap(Queue<T> & rhs){
  std::swap(size_, rhs.size_);
  std::swap(head_, rhs.head_);
  std::swap(tail_, rhs.tail_);
}

template <typename T>
void swap(Queue<T> & lhs, Queue<T> & rhs){
  lhs.QueueSwap(rhs);
}

}

#endif
