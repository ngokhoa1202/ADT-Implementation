#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T> {
private:
  static bool deleteNodeHelper(typename BinaryTree<T>::Node*& root, const T& item);
  static typename BinaryTree<T>::Node* predecessor(typename BinaryTree<T>::Node* root);
public:
  BinarySearchTree() : BinaryTree<T>() {}
  void add(const T& element) override;
  bool contains(const T& item) const override;
  bool deleteNode(const T& item) override;
};

//====================================Private methods===========================/
template<class T>
bool BinarySearchTree<T>::deleteNodeHelper(typename BinaryTree<T>::Node*& root, const T& item) {
  if (root == NULL) return false;

  if (item < root->data) { // go left
    return BinarySearchTree::deleteNodeHelper(root->left, item);
  }
  else if (item > root->data) { // go right
    return BinarySearchTree::deleteNodeHelper(root->right, item);
  }

  // if deleted node is found
  // Case 1 & 2: leaf node or has only one subtree
  if (root->left == NULL) {
    typename BinaryTree<T>::Node* deletedNode = root;
    root = root->right;
    delete deletedNode;
    return true;
  }
  if (root->right == NULL) {
    typename BinaryTree<T>::Node* deletedNode = root;
    root = root->left;
    delete deletedNode;
    return true;
  }
  // Case 3: has two subtrees
  typename BinaryTree<T>::Node* deletedNode = root->left;
  while (deletedNode->right != NULL) {
    deletedNode = deletedNode->right;
  }
  root->data = deletedNode->data;
  return BinarySearchTree::deleteNodeHelper(root->left, deletedNode->data);
}
/**
 * @brief Find the predecessor of root: the rightmost/largest node in the leftsubtree of root
 */
template<class T>
typename BinaryTree<T>::Node* BinarySearchTree<T>::predecessor(typename BinaryTree<T>::Node* root) {
  root = root->left;
  while (root->right != NULL) {
    root = root->right;
  }
  return root;
}
//====================================Public methods============================/
template<class T>
void BinarySearchTree<T>::add(const T& element) {
  if (this->isEmpty()) {
    this->root = new typename BinaryTree<T>::Node(element, NULL, NULL);
  }
  else {
    typename BinaryTree<T>::Node* curr = this->root;
    typename BinaryTree<T>::Node* parent = curr;
    while (curr != NULL) {
      parent = curr;
      if (element < curr->data) {
        curr = curr->left;
      }
      else curr = curr->right;
    }

    if (element < parent->data) {
      parent->left = new typename BinaryTree<T>::Node(element, NULL, NULL);
    }
    else {
      parent->right = new typename BinaryTree<T>::Node(element, NULL, NULL);
    }
  }

}

template<class T>
bool BinarySearchTree<T>::contains(const T& item) const {
  if (this->isEmpty()) return false;

  typename BinaryTree<T>::Node* curr = this->root;
  do {
    if (curr->data == item) return true;

    if (item < curr->data) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  } while (curr != NULL);
  
  return false;
}

/**
 * @brief When deleted node has two subtree, find the predecessor
 */
template<class T>
bool BinarySearchTree<T>::deleteNode(const T& item) {
  return BinarySearchTree::deleteNodeHelper(this->root, item);
}
#endif