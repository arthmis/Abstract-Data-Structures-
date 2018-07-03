#include <iostream>
#include <utility>

template <typename T>
class BST{
  public:
    BST(){
      root = nullptr;
    }
    void insert(const T &item);
    bool deleteItem(const T &item);
    bool searchFor(const T &item) const;
    void inorderTraversal();

  private:

    struct Node{
      T data;
      Node *left;
      Node *right;

      Node(){}
      Node(const T &item, Node *left_child = nullptr, Node *right_child = nullptr){
        data = item;
        left = left_child;
        right = right_child;
      }
    };

    Node *root;

    void insert(Node * & tree_root, const T &item);
    bool deleteItem(Node * & tree_root, const T &item);
    bool searchFor(Node *tree_root, const T &item) const;
    Node * findMin(Node *tree_root) const;
    void inorderTraversal(Node *tree_root);

};

template <typename T>
void BST<T>::insert(const T & item){
  insert(root, item);
}

template <typename T>
void BST<T>::insert(Node * & tree_root, const T & item){
  if(tree_root == nullptr){
    tree_root = new Node(item);
  }
  if(item < tree_root->data){
    insert(tree_root->left, item);
  }
  if(item > tree_root->data){
    insert(tree_root->right, item);
  }
}

template <typename T>
bool BST<T>::deleteItem(const T &item){
  return deleteItem(root, item);
}

template <typename T>
bool BST<T>::deleteItem(Node *&tree_root, const T &item){
  if(tree_root == nullptr)
    return false;
  if(item < tree_root->data)
    return deleteItem(tree_root->left, item);
  if(item > tree_root->data)
    return deleteItem(tree_root->right, item);

  if(tree_root->left == nullptr && tree_root->right == nullptr){
    delete tree_root;
    return true;
  }

  if(tree_root->left == nullptr && tree_root->right != nullptr){
    Node *old_node = tree_root;
    tree_root = old_node->right;
    delete old_node;
    return true;
  }

  if(tree_root->left != nullptr && tree_root->right == nullptr){
    Node *old_node = tree_root;
    tree_root = old_node->left;
    delete old_node;
    return true;
  }
  else{
    std::cout << findMin(tree_root->right)->data << "\n";
    tree_root->data = findMin(tree_root->right)->data;
    return deleteItem(tree_root->right, tree_root->data);
  }
  return true;
}

template <typename T>
typename BST<T>::Node* BST<T>::findMin(Node *tree_root) const{
  if(tree_root == nullptr){
    return nullptr;
  }
  if(tree_root->left == nullptr)
    return tree_root;

  return findMin(tree_root->left);
}

template <typename T>
bool BST<T>::searchFor(const T &item) const{
  return searchFor(root, item);
}

template <typename T>
bool BST<T>::searchFor(Node *tree_root, const T &item) const{
  if(tree_root == nullptr){
    return false;
  }
  if(item < tree_root->data){
    return searchFor(tree_root->left, item);
  }
  if(item > tree_root->data){
    return searchFor(tree_root->right, item);
  }
  return true;
}

template <typename T>
void BST<T>::inorderTraversal(){
  inorderTraversal(root);
}

template <typename T>
void BST<T>::inorderTraversal(Node *tree_root){
  if(tree_root == nullptr){
    std::cout << "Tree is empty\n";
    return;
  }

  if(tree_root->left != nullptr)
    inorderTraversal(tree_root->left);

  std::cout << tree_root->data << " ";

  if(tree_root->right!= nullptr)
    inorderTraversal(tree_root->right);
}
