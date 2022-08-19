#ifndef STACK_DLL_H
#define STACK_DLL_H

#include <iostream>
#include "error.h"
#include "DoublyLinkedList.h"

template<class T>
class Stack_DLL {
private:
  DoublyLinkedList<T> list;
public:
  Stack_DLL();
  void push(const T& element);
  T pop();
  bool isEmpty() const;
  T top() const;
  int size() const;
  bool contains(const T& element) const;
  void clear();
  void getInfo() const;
  ~Stack_DLL();
};

template<class T>
Stack_DLL<T>::Stack_DLL() : list{DoublyLinkedList<T>()} {}

template<class T>
void Stack_DLL<T>::push(const T& element) {
  this->list.add(element);
}

template<class T>
T Stack_DLL<T>::pop() {
  return this->list.removeAt(list.size()-1);
}

template<class T>
bool Stack_DLL<T>::isEmpty() const {
  return this->list.checkEmpty();
}

template<class T>
T Stack_DLL<T>::top() const {
  return this->list.getAt(list.size()-1);
}

template<class T>
int Stack_DLL<T>::size() const {
  return this->list.size();
}

template<class T>
bool Stack_DLL<T>::contains(const T& element) const {
  return list.contains(element);
}

template<class T>
void Stack_DLL<T>::clear() {
  this->list.clear();
}

template<class T>
void Stack_DLL<T>::getInfo() const {
  this->list.getInfo();
}

template<class T>
Stack_DLL<T>::~Stack_DLL() {
  this->list.clear();
}

#endif