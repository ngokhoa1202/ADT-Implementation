#ifndef STACK_SLL_H
#define STACK_SLL_H

#include <iostream>
#include "error.h"
#include <stdexcept>
#include "SinglyLinkedList_iteration.h"

template<class T>
class Stack_SLL { // add head, remove head
private:
  SinglyLinkedList<T> list;
public:
  Stack_SLL();
  void push(const T& element);
  T pop();
  bool isEmpty() const;
  T top() const;
  int size() const;
  bool contains(const T& element) const;
  void clear();
  void getInfo() const;
  ~Stack_SLL();
};

template<class T>
Stack_SLL<T>::Stack_SLL() : list{SinglyLinkedList<T>()} {}

template<class T>
void Stack_SLL<T>::push(const T& element) {
  this->list.addAt(0, element);
}

template<class T>
T Stack_SLL<T>::pop() {
  if (this->isEmpty()) {
    throw StackUnderflowException();
  }

  return this->list.removeHead();
}

template<class T>
bool Stack_SLL<T>::isEmpty() const {
  return (list.checkEmpty());
}

template<class T>
T Stack_SLL<T>::top() const {
  return this->list.getAt(0);
}

template<class T>
int Stack_SLL<T>::size() const {
  return this->list.size();
}

template<class T>
bool Stack_SLL<T>::contains(const T& element) const {
  return this->list.contains(element);
}

template<class T>
void Stack_SLL<T>::clear() {
  this->list.clear();
}

template<class T>
void Stack_SLL<T>::getInfo() const {
  this->list.getInfo();

}

template<class T>
Stack_SLL<T>::~Stack_SLL() {
  this->list.clear();
}
#endif