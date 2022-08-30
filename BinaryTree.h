#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>
#include <queue>
#include "error.h"

template<class T>
class BinaryTree {
protected:
  class Node;
public:
  Node* root;
  virtual void add(const T& element) = 0;
  virtual bool deleteNode(const T& item) = 0;
  static int getSize(Node* root); // O(n) n: numbers of nodes
  static int getHeight(Node* root); // O(n)
  static void getMax(Node* root, T& max); // O(n)
  static void getMin(Node* root, T& min); // O(n)
  static void printInOrderHelper(Node* root); // O(n)
  static void printPreOrderHelper(Node* root); // O(n)
  static void printPostOrderHelper(Node* root); // O(n)
  static void containsHelper(Node* root, const T& item, bool& containFlag); // O(n)
  static bool isBalancedHelper(Node* root);
public:
  BinaryTree() : root{NULL} {}
  int size() const;
  int height() const;
  int depth() const;
  void printInOrder() const;
  void printPreOrder() const;
  void printPostOrder() const;
  void printLevelOrder() const;
  virtual bool contains(const T& item) const;
  bool isEmpty() const;
  virtual T min() const;
  virtual T max() const;
  bool isBalanced() const;
  void display() const;
protected:
  class Node {
  public:
    T data;
    Node* left;
    Node* right;
    explicit Node(const T& _data, Node* _left = NULL, Node* _right = NULL) : data{_data}, left(_left), right(_right) {}
  };
};

//==============================Protected memeber functions=============================================================
template<class T>
int BinaryTree<T>::getSize(Node* root) {
  if (root == NULL) return 0;

  int sizeOfLeft = BinaryTree::getSize(root->left);
  int sizeOfRight = BinaryTree::getSize(root->right);

  return 1 + sizeOfLeft + sizeOfRight;
}

template<class T>
int BinaryTree<T>::getHeight(Node* root) {
  if (root == NULL) return 0;

  int heightOfLeft = BinaryTree::getHeight(root->left);
  int heightOfRight = BinaryTree::getHeight(root->right);

  return 1 + std::max(heightOfLeft, heightOfRight);
}

 /**
  * @brief: This function use pre-order traversal to find max of tree 
  * @param max: pass by reference from max function below
  */
template<class T>
void BinaryTree<T>::getMax(Node* root, T& max) {
  if (root == NULL) return;
  max = std::max(max, root->data);

  BinaryTree::getMax(root->left, max);
  BinaryTree::getMax(root->right, max);
}

template<class T>
void BinaryTree<T>::getMin(Node* root, T& min) {
  if (root == NULL) return;
  min = std::min(min, root->data);

  BinaryTree::getMin(root->left, min);
  BinaryTree::getMin(root->right, min);
}

template<class T>
void BinaryTree<T>::printInOrderHelper(Node* root) {
  if (root == NULL) return;

  BinaryTree::printInOrderHelper(root->left);
  std::cout << root->data << ' ';
  BinaryTree::printInOrderHelper(root->right);
}

template<class T>
void BinaryTree<T>::printPreOrderHelper(Node* root) {
  if (root == NULL) return;

  std::cout << root->data << ' ';
  BinaryTree::printPreOrderHelper(root->left);
  BinaryTree::printPreOrderHelper(root->right);
}

template<class T>
void BinaryTree<T>::printPostOrderHelper(Node* root) {
  if (root == NULL) return;

  BinaryTree::printPostOrderHelper(root->left);
  BinaryTree::printPostOrderHelper(root->right);
  std::cout << root->data << ' ';
}

/** @brief: this function use In-order traversal to search for an item in tree
  * @param containFlag: check if tree contains element or not. In order to break func early
  * */
template<class T>
void BinaryTree<T>::containsHelper(Node* root, const T& item,  bool& containsFlag) {
  if (root == NULL) return;
  
  if (root->data == item) {
    containsFlag = true;
    return;
  }

  BinaryTree::containsHelper(root->left, item, containsFlag);
  if (containsFlag) return; // use to break func early
  BinaryTree::containsHelper(root->right, item, containsFlag);
}

template<class T>  
bool BinaryTree<T>::isBalancedHelper(Node* root) {
  if (root == NULL) return true; 
  
  int heightOfLeft = BinaryTree::getHeight(root->left);
  int heightOfRight = BinaryTree::getHeight(root->right);

  if (std::abs(heightOfLeft-heightOfRight) <= 1 
      && BinaryTree::isBalancedHelper(root->left)
      && BinaryTree::isBalancedHelper(root->right)) 
      return true;
  
  return false;
}   

//==============================Public member functions===============================================================
template<class T>
int BinaryTree<T>::size() const { 
  return BinaryTree::getSize(this->root);
}

template<class T>
int BinaryTree<T>::height() const {
  return BinaryTree::getHeight(this->root);
}

template<class T>
int BinaryTree<T>::depth() const {
  return BinaryTree::getHeight(this->root);
}

template<class T>  
void BinaryTree<T>::printInOrder() const {
  std::cout << "In-order traversal result: ";
  BinaryTree::printInOrderHelper(this->root);
  std::cout << '\n';
}

template<class T>
void BinaryTree<T>::printPreOrder() const {
  std::cout << "Pre-Order Tranversal result: ";
  BinaryTree::printPreOrderHelper(this->root);
  std::cout << '\n';
}

template<class T>
void BinaryTree<T>::printPostOrder() const {
  std::cout << "Post-order traversal result: ";
  BinaryTree::printPostOrderHelper(this->root);
  std::cout << '\n';
}

template<class T>
void BinaryTree<T>::printLevelOrder() const {
  std::cout << "Level-order traversal result: ";

  if (this->isEmpty()) return;

  std::queue<Node*> nodeQueue;
  nodeQueue.push(this->root);
  while (!nodeQueue.empty()) {
    Node* curr = nodeQueue.front(); // to store after having popped front
    std::cout << curr->data << ' ';
    nodeQueue.pop();

    if (curr->left != NULL) {
      nodeQueue.push(curr->left);
    }
    if (curr->right != NULL) {
      nodeQueue.push(curr->right);
    }
  }
}

template<class T>
bool BinaryTree<T>::contains(const T& item) const {
  bool containFlag = false;
  BinaryTree::containsHelper(this->root, item, containFlag);
  return containFlag;
}

template<class T>
bool BinaryTree<T>::isEmpty() const {
  return (this->root == NULL);
}

template<class T>
T BinaryTree<T>::min() const {
  T min;
  BinaryTree::getMin(this->root, min);
  return min;
}

template<class T>
T BinaryTree<T>::max() const {
  T min;
  BinaryTree::getMin(this->root, min);
  return min;
}

template<class T>
bool BinaryTree<T>::isBalanced() const {
  return BinaryTree::isBalancedHelper(this->root);
}
#endif