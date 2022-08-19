#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include <iostream>
#include "List.h"
#include "error.h"

template<class T>
class DoublyCircularLinkedList : public List<T> {
private:
  class Node;
private:
  Node* head;
  Node* tail;
  int count;

  Node* getNodeAt(int index) const;
  T removeHead();
  void removeNode(Node*& deletedNode);
public:
  DoublyCircularLinkedList();
  void add(const T& element);
  void addAt(int index, const T& element);
  int size() const;
  T removeAt(int index);
  bool removeItem(const T& item);
  T getAt(int index) const;
  void setAt(int index, const T& element);
  int indexOf(const T& element) const;
  bool contains(const T& item) const;
  bool checkEmpty() const;
  void checkIndex(int index, bool isAddFunc = false) const;
  void getInfo() const;
  void clear();
  ~DoublyCircularLinkedList();
private:
  class Node {
  public:
    T data;
    Node* prev;
    Node* next;
    Node(const T& data, Node* prev = NULL, Node* next = NULL);  
  };      
};

template<class T>
typename DoublyCircularLinkedList<T>::Node* DoublyCircularLinkedList<T>::getNodeAt(int index) const {
  this->checkIndex(index);

  Node* curr = this->head;
  while (index > 0) {
    curr = curr->next;
    index--;
  }

  return curr;
}

template<class T>
T DoublyCircularLinkedList<T>::removeHead() {
  T res = this->head->data;
  Node* deletedNode = this->head;
  if (this->count == 1) {
    this->head = this->tail = NULL;
  }
  else { // count >= 2
    this->head->next->prev = this->tail;
    this->tail->next = this->head->next;
    this->head = this->head->next;
  }

  delete deletedNode;
  this->count--;

  return res;
}

template<class T>
void DoublyCircularLinkedList<T>::removeNode(Node*& deletedNode) {
  deletedNode->prev->next = deletedNode->next;
  deletedNode->next->prev = deletedNode->prev;
  if (deletedNode == this->tail) {
    this->tail = deletedNode;
  }
  delete deletedNode;
  this->count--;
}

template<class T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() : head{NULL}, tail{NULL}, count{0} {}

template<class T>
void DoublyCircularLinkedList<T>::add(const T& element) {
  if (this->checkEmpty()) {
    this->head = this->tail = new Node(element, NULL, NULL);
    this->tail->next = this->head;
    this->head->prev = tail;
  }
  else {
    this->tail->next = new Node(element, this->tail, this->head);
    this->head->prev = this->tail->next;
    this->tail = this->tail->next;
  }

  this->count++;
}

template<class T>
void DoublyCircularLinkedList<T>:: addAt(int index, const T& element) {
  this->checkIndex(index, true);

  if (index == this->count) {
    this->add(element);
  }
  else if (index == 0) { // add at head when list is certainly not empty
    this->head->prev = new Node(element, this->tail, this->head);
    this->tail->next = this->head->prev;
    this->head = this->head->prev;
    this->count++;
  }
  else { // add at Middle
    Node* curr = this->getNodeAt(index);
    curr->prev = new Node(element, curr->prev, curr); // assign pre of curr new node
    curr->prev->prev->next = curr->prev; // pre of new node is pre of curr before adding
    this-count++;
  }
}

template<class T>
bool DoublyCircularLinkedList<T>::checkEmpty() const {
  return (this->head == NULL);
}

template<class T>
int DoublyCircularLinkedList<T>::size() const {
  return this->count;
}

template<class T>
T DoublyCircularLinkedList<T>::removeAt(int index) {
  this->checkIndex(index);

  if (index == 0) {
    return this->removeHead();
  }
  else { // when count >= 2
    Node* deletedNode = this->getNodeAt(index);
    T res = deletedNode->data;
    this->removeNode(deletedNode);
    return res;
  }
}

template<class T>
bool DoublyCircularLinkedList<T>::removeItem(const T& item) {
  if (this->checkEmpty()) return false; 

  if (this->head->data == item) { // avoid the case when list has only one ele
    this->removeHead();
    return true;
  }

  Node* deletedNode = this->head;
  for (int i = 0; i < this->count && deletedNode->data != element; ++i) {
    deletedNode = deletedNode->next;
  }
  this->removeNode(deletedNode);

  return true;
}

template<class T>
T DoublyCircularLinkedList<T>::getAt(int index) const {
  this->checkIndex(index);
  return this->getNodeAt(index)->data;
}

template<class T>
void DoublyCircularLinkedList<T>::setAt(int index, const T& element) {
  this->checkIndex(index);
  this->getNodeAt(index)->data = element;
}

template<class T>
int DoublyCircularLinkedList<T>::indexOf(const T& element) const {
  Node* curr = this->head;
  for (int i = 0; i < this->count && deletedNode->data != element; ++i) {
    deletedNode = deletedNode->next;
  }
}

template<class T>
void DoublyCircularLinkedList<T>::checkIndex(int index, bool isAddFunc) const {
  if (isAddFunc) {
    if (index < 0 || index > this->count) {
      throw std::out_of_range("Index out of range");
    }
  }
  else if (index < 0 || index >= this->count) {
    throw std::out_of_range("Index out of range");
  }
}

template<class T>
void DoublyCircularLinkedList<T>::getInfo() const {
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
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
  this->clear();
}
template<class T>
DoublyCircularLinkedList<T>::Node::Node(const T& _data, Node* _prev, Node* _next) : data{_data}, prev{NULL}, next{NULL} {}

#endif