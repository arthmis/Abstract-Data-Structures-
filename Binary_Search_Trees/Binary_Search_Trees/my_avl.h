#include <iostream>
#include <utility>

template <typename T>
class AVL
{
public:
  AVL()
  {
    root = nullptr;
  }
  void insert(const T &item);
  bool deleteItem(const T &item);
  bool searchFor(const T &item) const;
  void inorderTraversal();
  void preOrderTraversal();
  bool isEmpty();

private:
  struct Node
  {
    T data;
    Node *left;
    Node *right;
    int height;

    Node() {}
    Node(const T &item, Node *left_child = nullptr, Node *right_child = nullptr)
    {
      data = item;
      left = left_child;
      right = right_child;
    }
  };

  Node *root;
  const int MAX_ALLOWED_DIFFERENCE = 1;

  void insert(Node *&tree_root, const T &item);
  bool deleteItem(Node *&tree_root, const T &item);
  bool searchFor(Node *tree_root, const T &item) const;
  Node *findMin(Node *tree_root) const;
  void inorderTraversal(Node *tree_root);
  void preOrderTraversal(Node *tree_root);
  void balance(Node *&tree_root);
  void leftRotate(Node *&tree_root);
  void rightRotate(Node *&tree_root);
  void doubleRotateWithLeftChild(Node *&tree_root);
  void doubleRotateWithRightChild(Node *&tree_root);
  int height(Node *tree_root);
  bool isEmpty(Node *tree_root);
};

template <typename T>
bool AVL<T>::isEmpty()
{
  return isEmpty(root);
}

template <typename T>
bool AVL<T>::isEmpty(Node *tree_root)
{
  return tree_root == nullptr;
}

template <typename T>
void AVL<T>::insert(const T &item)
{
  insert(root, item);
}

template <typename T>
void AVL<T>::insert(Node *&tree_root, const T &item)
{
  if (tree_root == nullptr)
  {
    tree_root = new Node(item);
  }
  if (item < tree_root->data)
  {
    insert(tree_root->left, item);
  }
  if (item > tree_root->data)
  {
    insert(tree_root->right, item);
  }

  balance(tree_root);
}

template <typename T>
bool AVL<T>::deleteItem(const T &item)
{
  return deleteItem(root, item);
}

template <typename T>
bool AVL<T>::deleteItem(Node *&tree_root, const T &item)
{
  if (tree_root == nullptr)
    return false;
  if (item < tree_root->data)
    return deleteItem(tree_root->left, item);
  if (item > tree_root->data)
    return deleteItem(tree_root->right, item);

  if (tree_root->left == nullptr && tree_root->right == nullptr)
  {
    delete tree_root;
    return true;
  }

  if (tree_root->left == nullptr && tree_root->right != nullptr)
  {
    Node *old_node = tree_root;
    tree_root = old_node->right;
    delete old_node;
    return true;
  }

  if (tree_root->left != nullptr && tree_root->right == nullptr)
  {
    Node *old_node = tree_root;
    tree_root = old_node->left;
    delete old_node;
    return true;
  }
  else
  {
    std::cout << findMin(tree_root->right)->data << "\n";
    tree_root->data = findMin(tree_root->right)->data;
    return deleteItem(tree_root->right, tree_root->data);
  }
  balance(tree_root);
  return true;
}

template <typename T>
typename AVL<T>::Node *AVL<T>::findMin(Node *tree_root) const
{
  if (tree_root == nullptr)
  {
    return nullptr;
  }
  if (tree_root->left == nullptr)
    return tree_root;

  return findMin(tree_root->left);
}

template <typename T>
bool AVL<T>::searchFor(const T &item) const
{
  return searchFor(root, item);
}

template <typename T>
bool AVL<T>::searchFor(Node *tree_root, const T &item) const
{
  if (tree_root == nullptr)
  {
    return false;
  }
  if (item < tree_root->data)
  {
    return searchFor(tree_root->left, item);
  }
  if (item > tree_root->data)
  {
    return searchFor(tree_root->right, item);
  }
  return true;
}

template <typename T>
void AVL<T>::inorderTraversal()
{
  inorderTraversal(root);
}

template <typename T>
void AVL<T>::inorderTraversal(Node *tree_root)
{
  if (isEmpty())
  {
    std::cout << "Tree is empty\n";
    return;
  }

  if (tree_root->left != nullptr)
    inorderTraversal(tree_root->left);

  std::cout << tree_root->data << " ";

  if (tree_root->right != nullptr)
    inorderTraversal(tree_root->right);
}

template <typename T>
void AVL<T>::preOrderTraversal()
{
  preOrderTraversal(root);
}

template <typename T>
void AVL<T>::preOrderTraversal(Node *tree_root)
{
  if (isEmpty())
  {
    std::cout << "Tree is empty\n";
    return;
  }

  std::cout << tree_root->data << " ";

  if (tree_root->left != nullptr)
    preOrderTraversal(tree_root->left);

  if (tree_root->right != nullptr)
    preOrderTraversal(tree_root->right);
}

template <typename T>
void AVL<T>::balance(Node *&tree_root)
{
  if (height(tree_root->left) - height(tree_root->right) > MAX_ALLOWED_DIFFERENCE)
  {
    if (height(tree_root->left->left) >= height(tree_root->left->right))
      rightRotate(tree_root);
    else
      doubleRotateWithLeftChild(tree_root);
  }
  if (height(tree_root->right) - height(tree_root->left) > MAX_ALLOWED_DIFFERENCE)
  {
    if (height(tree_root->right->right) >= height(tree_root->right->left))
      leftRotate(tree_root);
    else
      doubleRotateWithRightChild(tree_root);
  }
  tree_root->height = std::max(height(tree_root->right),
                               height(tree_root->left)) +
                      1;
}

template <typename T>
void AVL<T>::leftRotate(Node *&tree_root)
{
  Node *temp_node = tree_root->right;
  tree_root->right = temp_node->left;
  temp_node->left = tree_root;
  tree_root->height = std::max(height(tree_root->right), height(tree_root->left)) + 1;
  temp_node->height = std::max(height(temp_node->right), height(temp_node->left)) + 1;
  tree_root = temp_node;
}

template <typename T>
void AVL<T>::doubleRotateWithLeftChild(Node *&tree_root)
{
  leftRotate(tree_root->left);
  rightRotate(tree_root);
}

template <typename T>
void AVL<T>::rightRotate(Node *&tree_root)
{
  Node *temp_node = tree_root->left;
  tree_root->left = temp_node->right;
  temp_node->right = tree_root;
  tree_root->height = std::max(height(tree_root->right), height(tree_root->left)) + 1;
  temp_node->height = std::max(height(temp_node->right), height(temp_node->left)) + 1;
  tree_root = temp_node;
}

template <typename T>
void AVL<T>::doubleRotateWithRightChild(Node *&tree_root)
{
  rightRotate(tree_root->right);
  leftRotate(tree_root);
}

template <typename T>
int AVL<T>::height(Node *tree_root)
{
  if (tree_root == nullptr)
    return -1;
  else
  {
    return tree_root->height;
  }
}
