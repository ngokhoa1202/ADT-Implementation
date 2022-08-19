#ifndef QUEUE_SLL_H
#define QUEUE_SLL_H

#include <iostream>
#include "SinglyLinkedList_iteration.h"
#include "error.h" 

template<class T>
class Queue_SLL : public std::exception { // add tail, remove head
private:
  SinglyLinkedList<T> list;
public:
  Queue_SLL();
  void enqueue(const T& element);
  T dequeue();
  T front() const;
  T rear() const;
  bool isEmpty() const; 
  int size() const; 
  void getInfo() const;
  bool contains(const T& element) const;
  void clear();
  ~Queue_SLL(); 
};

template<class T>
Queue_SLL<T>::Queue_SLL() : list{SinglyLinkedList<T>()} {}

template<class T>
void Queue_SLL<T>::enqueue(const T& element) {
  this->list.addAt(list.size(), element);
}

template<class T>
T Queue_SLL<T>::dequeue() {
  if (this->isEmpty()) {
    throw StackUnderflowException();
  }
  return list.removeAt(0);
}

template<class T>
T Queue_SLL<T>::front() const {
  return this->list.getAt(0);
}

template<class T>
T Queue_SLL<T>::rear() const {
  return this->list.getAt(list.size()-1);
}

template<class T>
bool Queue_SLL<T>::isEmpty() const {
  return (list.size() == 0);
}

template<class T>
int Queue_SLL<T>::size() const {
  return this->list.size();
}

template<class T>
void Queue_SLL<T>::getInfo() const {
  this->list.getInfo();
}

template<class T>
bool Queue_SLL<T>::contains(const T& element) const {
  return this->list.contains(element);
}

template<class T>
void Queue_SLL<T>::clear() {
  this->list.clear();
}

template<class T>
Queue_SLL<T>::~Queue_SLL() {
  this->list.clear();
}

#endif