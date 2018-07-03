#ifndef DoubleLinkedList
#define DoubleLinkedList

#include <iostream>

namespace DoubleLinkedList{

template <typename T>
class List{
  public:
   List();
   List(const List &list_to_copy);
   List &operator=(const List &list_to_copy);
   List(List &&list_to_move);
   List &operator=(List &&list_to_move);
   ~List();
   void push_back(const T &item);
   void push_front(const T &item);
   void insert(const T &item); // TODO implement insert anywhere, takes an index if less than size
   const T find(const T &item) const;
   bool write(const T &item, const T &new_item);
   T PopFront();
   T PopBack();
   void Remove(const T &item); // TODO implement remove from anywhere, takes a value to remove
   inline bool isEmpty() const;
   void PrintList() const;
   void ListSwap(List &list_to_swap);
  private:
   struct node{
     T data;
     node *next_node;
     node *previous_node;
     node(){
       next_node = nullptr;
       previous_node = nullptr;
     }
     node(const T &item){
       data = item;
       next_node = nullptr;
       previous_node = nullptr;
     }
   };
   int size_;
   node *head;
   node *tail;
};

template <typename T>
List<T>::List(){
  size_ = 0;
  head = new node();
  tail = new node();
  head->next_node = tail;
  head->previous_node = nullptr;
  tail->previous_node = head;
  tail->next_node = nullptr;
}

template <typename T>
List<T>::List(const List<T> &list_to_copy){
  size_ = 0;
  tail = new node();
  head = new node();
  head->next_node = tail;
  head->previous_node = nullptr;
  tail->previous_node = head;
  tail->next_node = nullptr;

  if(list_to_copy.isEmpty()){
    return;
  }
  node *itr_list_to_copy = list_to_copy.head->next_node;
  while(itr_list_to_copy->next_node){
    this->push_back(itr_list_to_copy->data);
    itr_list_to_copy = itr_list_to_copy->next_node;
  }
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list_to_copy){
  List<T> copy = list_to_copy;
  swap(*this, copy);
  return *this;
}

template <typename T>
List<T>::List(List<T> &&list_to_move){
  size_ = list_to_move.size_;
  head = list_to_move.head;
  tail = list_to_move.tail;
  list_to_move.tail = nullptr;
  list_to_move.head = nullptr;
  list_to_move.size_ = 0;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&list_to_move){
  std::swap(size_, list_to_move.size_);
  std::swap(head, list_to_move.head);
  std::swap(tail, list_to_move.tail);
  return *this;
}

template <typename T>
List<T>::~List(){
  if(size_ == 0){
    delete head;
    delete tail;
    return;
  }
  node *itr = head->next_node;
  node *node_to_delete;
  while(itr->next_node){
    node_to_delete = itr;
    itr = itr->next_node;
    delete node_to_delete;
  }
  delete head;
  delete tail;
}


template <typename T>
void List<T>::PrintList() const{
  if(this->isEmpty()){
    std::cout << "list is empty";
    return;
  }
  node *itr = head->next_node;
  while(itr->next_node){
    std::cout << itr->data << " ";
    itr = itr->next_node;
  }
}

template <typename T>
inline bool List<T>::isEmpty() const{ return size_ == 0; }

template <typename T>
void List<T>::push_back(const T &item){
  node *new_node = new node(item);
  tail->previous_node->next_node = new_node;
  new_node->previous_node = tail->previous_node;
  tail->previous_node = new_node;
  new_node->next_node = tail;
  ++size_;
}

template <typename T>
void List<T>::push_front(const T &item){
  node *new_node = new node(item);
  new_node->next_node = head->next_node;
  new_node->previous_node = head;
  new_node->next_node->previous_node = new_node;
  head->next_node = new_node;
  ++size_;
}

template <typename T>
T List<T>::PopFront(){
  node *node_to_pop = head->next_node;
  T first_value = std::move(node_to_pop->data);
  node_to_pop->next_node->previous_node = head;
  head->next_node = node_to_pop->next_node;
  node_to_pop->next_node = nullptr;
  node_to_pop->previous_node = nullptr;
  delete node_to_pop;
  --size_;
  return first_value;
}

template <typename T>
T List<T>::PopBack(){
  node *node_to_pop = tail->previous_node;
  T last_value = std::move(node_to_pop->data);
  node_to_pop->previous_node->next_node = tail;
  tail->previous_node = node_to_pop->previous_node;
  node_to_pop->next_node = nullptr;
  node_to_pop->previous_node = nullptr;
  delete node_to_pop;
  --size_;
  return last_value;
}

template <typename T>
const T List<T>::find(const T &item) const{
  node *itr = head->next_node;
  while(itr->next_node){
    if(itr->data == item){
      T *item_found = &itr->data;
      return item_found;
    }
    itr  = itr->next_node;
  }
  return nullptr;
}

template <typename T>
bool List<T>::write(const T &item, const T &new_item){
  node *itr = head->next_node;
  while(itr->next_node){
    if(itr->data == item){
      itr->data = new_item;
      return true;
    }
    itr  = itr->next_node;
  }
  return false;
}

template <typename T>
void List<T>::ListSwap(List<T> &list_to_swap){
  std::swap(this->size_, list_to_swap.size_);
  std::swap(this->head, list_to_swap.head);
  std::swap(this->tail, list_to_swap.tail);
}

template <typename T>
void swap(List<T> &lhs, List<T> &rhs){
  lhs.ListSwap(rhs);
}

}

#endif
