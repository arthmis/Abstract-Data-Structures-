#ifndef STACK_ADT
#define STACK_ADT

#include <algorithm>

namespace stackADT{

template <typename T>
class Stack {

  private:
    struct node {
        T data;
        node *next_node = nullptr;
        node(){}
        node(T value){
            data = value;
          }
    };
  node *head_;
  int size_;
  void DeleteNode();

  public:
   Stack();
   Stack(Stack &stack_to_copy);
   Stack &operator=(Stack &stack_to_copy);
   Stack(Stack &&stack_to_move);
   Stack &operator=(Stack &&stack_to_move);
   ~Stack();
   void push(const T &value);
   T pop();
   const T top() const;
   inline int size();
   void PrintStack() const;
   void StackSwap(Stack &stack_to_swap);
   bool isEmpty() const;
};

template <typename T>
Stack<T>::Stack(){
  size_ = 0;
  head_ = new node();
  head_->next_node = nullptr;
}

template <typename T>
Stack<T>::Stack(Stack<T> &stack_to_copy){
  Stack<T> temporary_copy;
  head_ = new node();
  head_->next_node = nullptr;
  size_ = 0;
  while(stack_to_copy.size() > 0){
    T item = stack_to_copy.pop();
    temporary_copy.push(item);
  }
  while(temporary_copy.size() > 0){
    T item = temporary_copy.pop();
    push(item);
  }
}

template <typename T>
Stack<T>::Stack(Stack &&stack_to_move){
  head_ = stack_to_move.head_;
  size_ = stack_to_move.size_;
  stack_to_move.head_ = nullptr;
  stack_to_move.size_ = 0;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack &stack_to_copy){
  Stack<T> temp = stack_to_copy;
  swap(*this, temp);
  return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack &&stack_to_move){
  swap(*this, stack_to_move);
  return *this;
}

template <typename T>
Stack<T>::~Stack(){
  if(isEmpty()){
    delete head_;
    return;
  }
  while(size_ > 0){
    DeleteNode();
  }
  delete head_;
}

template <typename T>
void Stack<T>::push(const T &value){
  node *new_node = new node(value);
  new_node->next_node = head_->next_node;
  head_->next_node = new_node;
  ++size_;
}

template <typename T>
inline int Stack<T>::size(){
  return size_;
}

template <typename T>
T Stack<T>::pop(){
  node *node_to_pop = head_->next_node;
  head_->next_node = node_to_pop->next_node;
  node_to_pop->next_node = nullptr;
  T data_value = std::move(node_to_pop->data);
  delete node_to_pop;
  --size_;

  return data_value;
}

template <typename T>
void Stack<T>::DeleteNode(){
  node *node_to_pop = head_->next_node;
  head_->next_node = node_to_pop->next_node;
  node_to_pop->next_node = nullptr;
  delete node_to_pop;
  --size_;
}

template <typename T>
const T Stack<T>::top() const{
  return head_->next_node->data;
}

template <typename T>
bool Stack<T>::isEmpty() const{
  return size_ == 0;
}

template <typename T>
void Stack<T>::StackSwap(Stack<T> &stack_to_swap){
  std::swap(size_, stack_to_swap.size_);
  std::swap(head_, stack_to_swap.head_);
}

template <typename T>
void swap(Stack<T> &lhs, Stack<T> &rhs){
  lhs.StackSwap(rhs);
}

}

#endif
