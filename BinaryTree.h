#ifdef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <algorithm>

template<class T>
class BinaryTree {
protected:
  class Node;
protected:
  Node* root;
  static int getHeightHelper(Node* root);
  static int getSizeHelper(Node* root);
  static T maxHelper(Node* root);
  static T minHelper(Node* root);
public:
  BinaryTree() : root{NULL} {}
  int getHeight() const;
  int getSize() const;
  T max() const;
  T min() const;
protected:
  class Node {
  public:
    T data;
    Node* left;
    Node* right;
    explicit Node(const T& _data, Node* _left = NULL, Node* _right = NULL) : data{_data}, left{_left}, right{_right} {}
  };      
};

//=============================Protected functions================================

template<class T>
int BinaryTree<T>::getHeightHelper(Node* root) {
  if (root == NULL) return 0;
  int heightOfLeft = BinaryTree::getHeightHelper(root->left);
  int heightOfRight = BinaryTree::getHeightHelper(root->right);
  return 1 + std::max(heightOfLeft, heightOfRight);
}

template<class T>
int BinaryTree<T>::getSizeHelper(Node* root) {
  if (root == NULL) return 0;
  int sizeOfLeft = BinaryTree::getSizeHelper(root->left);
  int sizeOfRight = BinaryTree::getSizeHelper(root->right);
  return 1 + sizeOfLeft + sizeOfRight;
}

template<class T>
T BinaryTree<T>::maxHelper(Node* root) {
  if (root == NULL) return T();
  T maxOfLeft = BinaryTree::maxHelper(root->left);
  T maxOfRight = BinaryTree::maxHelper(root->right);
  return std::max(root->data, std::max(maxOfLeft, maxOfRight));
}

template<class T>
T BinaryTree<T>::minHelper(Node* root) {
  if (root == NULL) return T();
  T minOfLeft = BinaryTree::minHelper(root->left);
  T maxOfRight = BinaryTree::minHelper(root->right);
  return std::min(root->data, std::min(minOfLeft, maxOfRight));
}


//===========================Public functions================================
template<class T>
int BinaryTree<T>::getHeight() const {
  return BinaryTree::getHeightHelper(this->root);
}

template<class T>
int BinaryTree<T>::getSize() const {
  return BinaryTree::getSizeHelper(this->root);
}

template<class T>
T BinaryTree<T>::max() const {
  return BinaryTree::maxHelper(this->root);
}

template<class T>
T BinaryTree<T>::min() const {
  return BinaryTree::minHelper(this->root);
}


#endif