//
// Created by DELL on 8/15/2022.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include "List.h"

template<class T>
class DoublyLinkedList : public List<T> {
private:
  class Node; // forward declaration
private:
  Node* head;
  Node* tail;
  int count;

  Node* getNodeAt(int index) const;
  T removeHead();
  T removeTail();
  T removeMiddleAt(const int& index);
public:
  DoublyLinkedList();
  void add(const T& element);
  void addAt(int index, const T& element);
  int size() const;
  bool checkEmpty() const;
  T removeAt(int index);
  bool removeItem(const T& element);
  T getAt(int index) const;
  void setAt(int index, const T &element);
  int indexOf(const T& item) const;
  bool contains(const T& item) const;
  void checkIndex(int index, bool isAddFunc = false) const;
  void clear();
  void getInfo() const;
private:
  class Node {
  public:
    T data;
    Node* prev;
    Node* next;
    explicit Node(const T& data, Node* prev = NULL, Node* next = NULL);
  };
};

template<class T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::getNodeAt(int index) const {
  this->checkIndex(index);

  Node* curr = this->head;
  while (index > 0) {
    curr = curr->next;
    index--;
  }

  return curr;
}

template<class T>
T DoublyLinkedList<T>::removeHead() {
  T res = this->head->data;
  Node* deletedNode = this->head;

  if (this->count == 1) { // list has only one ele
    this->head = this->tail = NULL;
  }
  else { // at least 2 ele
    this->head->next->prev = NULL;
    this->head = this->head->next;
  }

  delete deletedNode;
  this->count--;

  return res;
}

template<class T>
T DoublyLinkedList<T>::removeTail() {
  T res = this->tail->data;

  this->tail->prev->next = NULL;
  Node* deletedNode = this->tail; 
  this->tail = this->tail->prev;

  this->count--;
  delete deletedNode;
  
  return res;
}

template<class T>
T DoublyLinkedList<T>::removeMiddleAt(const int& index) {
  Node* deletedNode = this->getNodeAt(index);
  deletedNode->prev->next = deletedNode->next;
  deletedNode->next->prev = deletedNode->prev;

  T res = deletedNode->data;
  delete deletedNode;
  this->count--;

  return res;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : head{NULL}, tail{NULL}, count{0} {}

template<class T>
DoublyLinkedList<T>::Node::Node(const T& _data, Node* _prev, Node* _next) :
      data(_data), prev(_prev), next(_next) {}

template<class T>
void DoublyLinkedList<T>::add(const T& element) {
  if (this->checkEmpty()) {
    this->head = this->tail = new Node(element);
  }
  else {
    this->tail->next = new Node(element, this->tail, NULL);
    this->tail = this->tail->next;
  }

  this->count++;
}

template<class T>
void DoublyLinkedList<T>::addAt(int index, const T& element) {
  this->checkIndex(index, true);

  if (index == 0) { // add at head
    this->head->prev = new Node(element, NULL, this->head);
    this->head = this->head->prev;
    this->count++;
  }
  else if (index == this->count) { // add at Tail
    this->add(element);
  }
  else { // add at Middle
    Node* curr = this->getNodeAt(index);
    curr->prev->next = new Node(element, curr->prev, curr);
    curr->prev = curr->prev->next;
    this->count++;
  }
}

template<class T>
int DoublyLinkedList<T>::size() const {
  return this->count;
}

template<class T>
bool DoublyLinkedList<T>::checkEmpty() const {
  return (this->count == 0);
}

template<class T>
T DoublyLinkedList<T>::removeAt(int index) {
  this->checkIndex(index);

  if (index == 0) { // remove head
    return this->removeHead();
  }
  else if (index == this->count-1) { //remove tail
    return this->removeTail();
  }
  else { // remove specific position in range (0, count-1)
    return this->removeMiddleAt(index);
  }
}

template<class T>
void DoublyLinkedList<T>::checkIndex(int index, bool isAddFunc) const {
  if (isAddFunc) {
    if (index < 0 || index > this->count) {
      throw std::out_of_range("Index is out of range");
    }
  }
  else if (index < 0 || index >= this->count) {
    throw std::out_of_range("Index is out of range");
  }
}



template<class T>
bool DoublyLinkedList<T>::removeItem(const T& element) {
  if (this->checkEmpty()) return false;

  if (this->head->data == element) {
    this->removeHead();
    return true;
  }
  else {
    Node* deletedNode = this->head;
    while (deletedNode != NULL && deletedNode->data != element) {
      deletedNode = deletedNode->next;
    }
    if (deletedNode == NULL) return false;

    deletedNode->prev->next = deletedNode->next;
    if (deletedNode == this->tail) {
      this->tail = this->tail->prev;
    }
    else {
      deletedNode->next->prev = deletedNode->prev;
    }

    delete deletedNode;
    this->count--;
    return true;
  }

}

template<class T>
T DoublyLinkedList<T>::getAt(int index) const {
  this->checkIndex(index);
  
  if (index == 0) return this->head->data;
  if (index == this->count-1) return this->tail->data;

  return this->getNodeAt(index)->data;
}

template<class T>
void DoublyLinkedList<T>::setAt(int index, const T& element) {
  this->checkIndex(index);
  
  if (index == 0) {
    this->head->data = element;
    return;
  }
  if (index == this->count-1) {
    this->tail->data = element;
    return;
  }
  this->getNodeAt(index)->data = element; 
}

template<class T>
int DoublyLinkedList<T>::indexOf(const T& item) const {
  if (this->checkEmpty()) return -1;

  Node* curr = this->head;
  for (int i = 0; i < this->count; i++) {
    if (curr->data == item) return i;
    curr = curr->next;
  }
  return -1; // if not found item
}

template<class T>
bool DoublyLinkedList<T>::contains(const T &item) const {
  return (this->indexOf(item) != -1);
}

template<class T>
void DoublyLinkedList<T>::clear() {
  Node* curr = this->head;
  while (curr != NULL) {
    Node* next = curr->next;
    delete curr;
    curr = next;
  }

  this->head = NULL;
  this->tail = NULL;
  this->count = 0;
}

template<class T>
void DoublyLinkedList<T>::getInfo() const {
  std::cout << "Size of list: " << this->count << '\n'
            << "Elements of list: ";

  Node* curr = this->head;
  for (int i = 0; i < this->count-1; ++i) {
    std::cout << curr->data << +"-->";
    curr = curr->next;
  }
  if (curr != NULL) {
    std::cout << curr->data << "\n\n";
  }
}
#endif 
