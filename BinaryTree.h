#ifdef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class BinaryTree {
protected:
  class Node;
protected:
  Node* root;
  int getHeightHelper(Node* root) const;
  int getSizeHelper(Node* root) const;
  T maxHelper() const;
  T minHelper() const;
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
int BinaryTree<T>::getHeightHelper(Node* root) const {
  if (root == NULL) return 0;
  int heightOfLeft = this->getHeightHelper(root->left);
  int heightOfRight = this->getHeightHelper(root->right);
  return 1 + std::max(heightOfLeft, heightOfRight);
}

template<class T>
int BinaryTree<T>::getSizeHelper(Node* root) const {
  if (root == NULL) return 0;
  int sizeOfLeft = this->getSizeHelper(root->left);
  int sizeOfRight = this->getSizeHelper(root->right);
  return 1 + sizeOfLeft + sizeOfRight;
}

template<class T>
T BinaryTree<T>::maxHelper(Node* root) const {
  if (root == NULL) return T();
  T maxOfLeft = this->maxHelper(root->left);
  T maxOfRight = this->maxHelper(root->right);
  return std::max(root->data, std::max(maxOfLeft, maxOfRight));
}

template<class T>
T BinaryTree<T>::minHelper(Node* root) const {
  if (root == NULL) return T();
  T minOfLeft = this->minHelper(root->left);
  T maxOfRight = this->minHelper(root->right);
  return std::min(root->data, std::min(minOfLeft, maxOfRight));
}


//===========================Public functions================================
template<class T>
int BinaryTree<T>::getHeight() const {
  return this->getHeightHelper(this->root);
}

template<class T>
int BinaryTree<T>::getSize() const {
  return this->getSizeHelper(this->root);
}

template<class T>
T BinaryTree<T>::max() const {
  return this->maxHelper(this->root);
}

template<class T>
T BinaryTree<T>::min() const {
  return this->minHelper(this->root);
}


#endif