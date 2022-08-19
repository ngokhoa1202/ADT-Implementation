//
// Created by DELL on 8/12/2022.
//

#ifndef SINGLYCIRCULARLINKEDLIST_H
#define SINGLYCIRCULARLINKEDLIST_H

#include <iostream>
#include "List.h"

template<class T>
class SinglyCircularLinkedList : public List<T>{
private:
  class Node;
private:
  Node* head;
  Node* tail;
  int count;

  void checkIndex(int index, bool isAddFunc = false) const;
  Node* getNodeAt(int index) const;
  T removeHead();
public:
  SinglyCircularLinkedList();
  void add(const T& element); // O(1)
  void addAt(int index, const T& element); // n/2 => O(n)
  T getAt(int index) const; // O(n)
  T operator [](int index) const; // O(n)
  void setAt(int index, const T& element);// O(n)
  int size() const;
  bool checkEmpty() const;
  int indexOf(const T& element) const;
  bool contains(const T& element) const;
  T removeAt(int index); // O(n)
  bool removeItem(const T& element); // O(n)
  void clear(); // O(n)
  void getInfo() const;
private:
  class Node {
  public:
    T data;
    Node* next;
    explicit Node(const T& data, Node* next = NULL);
  };
};

template<class T>
SinglyCircularLinkedList<T>::SinglyCircularLinkedList() : head(NULL), tail(NULL), count(0) {}

template<class T>
void SinglyCircularLinkedList<T>::checkIndex(int index, bool isAddFunc) const {
  if (isAddFunc) {
    if (index < 0 || index > this->count) {
      throw std::out_of_range("Index is out of range");
    }
  }
  else if (index < 0 || index >= this->count)  {
    throw std::out_of_range("Index is out of range");
  }
}

template<class T>
typename SinglyCircularLinkedList<T>::Node* SinglyCircularLinkedList<T>::getNodeAt(int index) const {
  this->checkIndex(index);

  if (index == 0) return this->head;
  if (index == this->count-1) return this->tail;

  Node* curr = this->head;
  while (index > 0) {
    index--;
    curr = curr->next;
  }

  return curr;
}

template<class T>
T SinglyCircularLinkedList<T>::removeHead() {
  T res = this->head->data;

  Node* deletedNode = this->head;
  this->tail->next = this->head->next;
  this->head = this->head->next;

  if (this->head == NULL) // when delete the only one element
    this->tail = NULL;

  delete deletedNode;
  this->count--;

  return res;
}

template<class T>
void SinglyCircularLinkedList<T>::add(const T& element) { // add at Tail
  if (this->head == NULL) { // If list is empty
    this->head = this->tail = new Node(element);
    this->head->next = this->tail->next = this->head;
  }
  else {
    Node* newNode = new Node(element, this->head);
    this->tail->next = newNode;
    this->tail = newNode;
  }
  this->count++;
}

template<class T>
void SinglyCircularLinkedList<T>::addAt(int index, const T& element) {
  this->checkIndex(index, true);

  if (index == this->count) { // solve this case first because line 89: this->tail->next will cause error if list is empty
    this->add(element); // add at tail
  }
  else if (index == 0) { // add at head
    Node* newNode = new Node(element, this->head);
    this->tail->next = newNode; // only for circular linked list
    this->head = newNode;
    this->count++;
  }
  else { // add at middle
    Node* prev = this->getNodeAt(index-1);
    Node* newNode = new Node(element, prev->next);
    prev->next = newNode;
    this->count++;
  }
}

template<class T>
T SinglyCircularLinkedList<T>::getAt(int index) const {
  return this->getNodeAt(index)->data;
}

template<class T>
T SinglyCircularLinkedList<T>::operator[](int index) const {
  return this->getAt(index);
}

template<class T>
void SinglyCircularLinkedList<T>::setAt(int index, const T& element) {
  this->getNodeAt(index)->data = element;
}

template<class T>
int SinglyCircularLinkedList<T>::size() const {
  return this->count;
}

template<class T>
bool SinglyCircularLinkedList<T>::checkEmpty() const {
  return (this->count == 0);
}

template<class T>
int SinglyCircularLinkedList<T>::indexOf(const T& element) const {
  Node* curr = this->head;
  for (int i = 0; i < this->count; i++) {
    if (curr->data == element)
      return i;
    curr = curr->next;
  }
  return -1;
}

template<class T>
bool SinglyCircularLinkedList<T>::contains(const T& element) const {
  return (this->indexOf(element) != -1);
}

template<class T>
T SinglyCircularLinkedList<T>::removeAt(int index) {
  this->checkIndex(index);

  if (index == 0) {
    return this->removeHead();
  }
  else { // otherwise: index = count-1 or in range (0, count-1)
    Node* prev = this->getNodeAt(index-1);
    T res = prev->next->data;
    Node* deletedNode = prev->next;
    prev->next = prev->next->next;

    if (prev == this->tail) {
      this->tail = prev;
    }
    delete deletedNode;
    this->count--;

    return res;
  }
}

template<class T>
bool SinglyCircularLinkedList<T>::removeItem(const T& element) {
  if (this->checkEmpty()) return false;

  if (this->head->data == element) { 
  // if we merge this case in general case, because the list we are implementing is ciruclar, when list has only one ele, next of head is head 
  // => we don't know whether we can delete head or not
    this->removeHead();
  }
  else {
    Node* prev = this->head;
    while (prev != this->tail && prev->next->data != element) {
      prev = prev->next;
    }
    if (prev != this->tail) { // if found ele
      Node* deletedNode = prev->next;
      prev->next = prev->next->next;
      if (deletedNode == this->tail)
        this->tail = prev;

      delete deletedNode;
      this->count--;
      return true;
    }
  }
  return false;
}

template<class T>
void SinglyCircularLinkedList<T>::clear() {
  Node* curr = this->head;
  while (curr->next != this->head) {
    Node* next = curr->next;
    delete curr;
    curr = next;
  }
  this->head = NULL;
  this->count = 0;
}

template<class T>
void SinglyCircularLinkedList<T>::getInfo() const {
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

template<class T>
SinglyCircularLinkedList<T>::Node::Node(const T& _data, Node* _next) : data(_data), next(_next) {}

#endif //LIST_IMPLEMENTATION_BYARRAY_SINGLYCIRCULARLINKEDLISTIMPLEMENTATION_H
