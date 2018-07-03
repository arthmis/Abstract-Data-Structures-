#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include "Murmurhash3.cc"
#include <iterator>

// template <typename K, typename T>
// using iterator_pair = const_iterator<std::pair<K, T>>;

// template <typename K, typename T>
// typedef std::list<std::pair<K, T>> list_of_pairs;

template <typename K, typename T>
class SeparateChaining
{
  public:
  SeparateChaining(int capacity = 101);
  SeparateChaining(const SeparateChaining<K, T> &table_to_copy);
  SeparateChaining<K, T> &operator=(const SeparateChaining<K, T> &other_table); void insert(const K key, const T data);
  bool contain(const K key) const;
  bool remove (const K key);
  int size() const;
  int get_collisions();

  private:
  std::vector<std::list<std::pair<K, T>>> table;
  int table_capacity; 
  int number_of_items; 
  int collisions;
  const float LOAD_FACTOR = 0.7;
  int hash(const std::string input_key, const int table_size) const;
  int hash(const int input_key, const int table_size) const;
  void check_load();
  void rehash();
};

template <typename K, typename T>
SeparateChaining<K, T>::SeparateChaining(int capacity)
{
  number_of_items = 0; 
  table_capacity = capacity; 
  table.resize(table_capacity);
  collisions = 0; 
}

template <typename K, typename T>
SeparateChaining<K, T>::SeparateChaining(const SeparateChaining<K, T> 
                                                          &table_to_copy)
{
  table = table_to_copy.table;
  number_of_items = table_to_copy.number_of_items;
  collisions = table_to_copy.collisions;
  table_capacity = table_to_copy.table_capacity;
}

template <typename K, typename T>
SeparateChaining<K, T> & SeparateChaining<K, T>::operator=(
                            const SeparateChaining<K, T> &other_table)
{
  table = other_table.table;
  number_of_items = other_table.number_of_items;
  collisions = other_table.collisions;
  table_capacity = other_table.table_capacity;
  return *this;
}

template <typename K, typename T>
int SeparateChaining<K, T>::get_collisions(){
  return collisions;
}

template <typename K, typename T>
void SeparateChaining<K, T>::insert(const K key, const T data)
{
  int position = hash(key, table_capacity);
  if(!table[position].empty())
    collisions++;

  auto list_begin = table[position].begin();
  auto list_end = table[position].end();
  auto iterator = std::find_if(
                        list_begin,
                        list_end,
                        [&key](const std::pair<K, T> element){
                          return element.first == key;
                        });
  if(iterator == list_end){
    std::pair new_element(key, data);
    table[position].push_front(new_element);
    number_of_items++;
  }
  check_load();
}

template <typename K, typename T>
bool SeparateChaining<K, T>::contain(const K key) const
{
  int position = hash(key, table_capacity);
  auto list_begin = table[position].begin();
  auto list_end = table[position].end();
  auto iterator = std::find_if(
                      list_begin,
                      list_end,
                      [&key](const std::pair<K, T> element){
                        return element.first == key;
                      });
  if (iterator == list_end)
    return true;
  else
    return false;
}

template <typename K, typename T>
bool SeparateChaining<K, T>::remove(const K key){
  int position = hash(key, table_capacity);
  auto list_begin = table[position].begin();
  auto list_end = table[position].end();
  auto iterator = std::find_if(
                        list_begin,
                        list_end,
                        [&key](const std::pair<K, T> element){
                          return element.first == key;
                        });
  if(iterator != list_end){
    table[position].erase(iterator); 
    number_of_items--;
    return true;
  }
  else
    return false;
}

template <typename K, typename T>
int SeparateChaining<K, T>::hash(const std::string input_key, const int table_size) const
{
  char *key = new char[input_key.size() + 1];
  std::strcpy(key, input_key.c_str());
  int len = static_cast<int>(sizeof(key));
  int seed = 0;
  uint32_t hash_value = MurmurHash3_x86_32(key, len, seed);
  return hash_value % table_size;
}

template <typename K, typename T>
int SeparateChaining<K, T>::hash(const int input_key, const int table_size) const
{
  int *key = new int(input_key);
  int len = static_cast<int>(sizeof(key));
  int seed = 0;
  uint32_t hash_value = MurmurHash3_x86_32(key, len, seed);
  return hash_value % table_size;
}

template <typename K, typename T>
int SeparateChaining<K, T>::size() const{
  return size(); 
}

template <typename K, typename T>
void SeparateChaining<K, T>::check_load(){
  float current_load = static_cast<float>(number_of_items)  /
                       static_cast<float>(table_capacity);
  if(current_load > LOAD_FACTOR)
    rehash();
}

template <typename K, typename T>
void SeparateChaining<K, T>::rehash(){
  SeparateChaining<K, T> old_hash_table = *this;
  int new_capacity = old_hash_table.table_capacity * 2;
  SeparateChaining<K, T> new_hash_table(new_capacity);
  for(int i = 0; i < old_hash_table.table_capacity; i++){
    auto iterator = old_hash_table.table[i].begin();
    auto list_end = old_hash_table.table[i].end();
    if(!old_hash_table.table[i].empty()){
      for(; iterator != list_end; iterator++){
        new_hash_table.insert(iterator->first, iterator->second);
      }
    }

  }
  *this = new_hash_table;
}
