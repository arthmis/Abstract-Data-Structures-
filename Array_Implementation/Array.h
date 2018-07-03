#ifndef Array
#define Array

#include <utility>
#include <stdexcept>

namespace Array{

  template <typename T>
  class MyArray {
    private:
      int size_;
      int capacity_;
      T *array;

    public:
        MyArray();
        MyArray(int new_size);
        MyArray(const MyArray &old_array);
        MyArray operator=(const MyArray &copied_object);
        MyArray(MyArray && rhs);
        MyArray operator=(MyArray && rhs);
        ~MyArray();
        const T & operator[](int index) const;
        T & operator[](int index);
        int size() const;
        int capacity() const;
        bool isEmpty();
        void insert_back (const T &object);
        void insert(const T & item, const int index);
        int find(const T & item);
        void pop_back();
        T pop();
        void deleteItem(const T & value);
        void resize_array(int new_size);
        void reserve_space(int new_capacity);
        void vectorSwap(MyArray<T>& rhs);
   };

   template <typename T>
   MyArray<T>::MyArray(){
     array = new T [16];
     size_ = 0;
     capacity_ = 16;
   }
   template <typename T>
   MyArray<T>::MyArray(int new_size){
     array = new T[new_size];
     size_ = new_size;
     capacity_ = new_size;
   }
   template <typename T>
   MyArray<T>::MyArray(const MyArray &old_array){
     size_ = old_array.size_;
     capacity_ = old_array.capacity_;
     array = nullptr;
     array = new T[capacity_];
     for(int i = 0; i < size_; i++){
       array[i] = old_array[i];
     }
   }

   template <typename T>
   MyArray<T> MyArray<T>::operator=(const MyArray &copied_object){
     MyArray temp = copied_object;
     swap(*this, temp);
     return *this;
   }

   template <typename T>
   MyArray<T> MyArray<T>::operator=(MyArray && rhs){
       std::swap(size_, rhs.size_);
       std::swap(capacity_, rhs.capacity_);
       std::swap(array, rhs.array);

       return *this;
   }

   template <typename T>
   MyArray<T>::MyArray(MyArray && rhs){
     size_ = rhs.size_;
     capacity_ = rhs.capacity_;
     array = rhs.array;
     rhs.array = nullptr;
     rhs.size_ = 0;
     rhs.capacity_ = 0;
   }


    template <typename T>
   MyArray<T>::~MyArray(){ delete [] array; }

   template <typename T>
   const T & MyArray<T>::operator[](int index) const {
     if(index >= size_){
       throw std::out_of_range ("out of bounds");
     }

     return array[index];
   }

   template <typename T>
   T & MyArray<T>::operator[](int index) {
      if(index >= size_){
        throw std::out_of_range ("out of bounds");
      }
       return array[index];
   }

   template <typename T>
   int MyArray<T>::size() const { return size_; }

   template <typename T>
   int MyArray<T>::capacity() const { return capacity_; }

   template <typename T>
   bool MyArray<T>::isEmpty() { return size_ == 0; }

   template <typename T>
   void MyArray<T>::insert_back (const T &object){
     if (size_ == capacity_)
       reserve_space(size_ * 2);

     array[size_] =  object;
     size_++;
   }

   template <typename T>
   void MyArray<T>::pop_back () {
     size_--;
   }

   template <typename T>
   T MyArray<T>::pop(){
     T temp = std::move(array[size_-1]);
     --size_;
     return temp;
   }

   template <typename T>
   void MyArray<T>::resize_array(int new_size){
     if (new_size > capacity_){
       reserve_space(new_size);
       size_ = new_size;
       capacity_  = new_size;
     }
     else if (new_size == size_){
         reserve_space(new_size);
         size_ = new_size;
     }

   }


   template <typename T>
   void MyArray<T>::reserve_space(int new_capacity){
     if (new_capacity < size_)
       return;

     T *new_array = new T [new_capacity];
     for (int i = 0; i < new_capacity; ++i){
       new_array[i] = std::move(array[i]);
     }
     capacity_ = new_capacity;
     std::swap(array, new_array);
     delete [] new_array;
   }

   template <typename T>
   void MyArray<T>::vectorSwap(MyArray<T>& rhs){
      std::swap(size_, rhs.size_);
      std::swap(capacity_, rhs.capacity_);
      std::swap(array, rhs.array);
  }

  template <typename T>
    int MyArray<T>::find(const T & item){
        for(int i = 0; i < size_; ++i){
            if (array[i] == item){
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    void MyArray<T>::insert(const T & item, const int index){
        if(capacity_ - size_ > 0){
            for(int i = size_-1; i >= index ; --i){
                array[i+1] = array[i];
                // array[i+1] = std::move(array[i]);
            }
            array[index] = item;
            ++size_;
        }
        else{
            reserve_space(size_ * 2);
            for(int i = size_-1; i >= index ; --i){
                array[i+1] = array[i];
                // array[i+1] = std::move(array[i]);
            }
            array[index] = item;
            ++size_;
        }
    }

    template <typename T>
    void MyArray<T>::deleteItem(const T & value){
        int index_to_delete = this->find(value);
        if(index_to_delete == -1){
            return;
        }
        for(int i = index_to_delete + 1; i < size_; ++i){
            array[i - 1] = array[i];
        }
        --size_;

    }

   template <typename T>
   void swap(MyArray<T>& lhs, MyArray<T>& rhs){
     lhs.vectorSwap(rhs);
   }


}

#endif
