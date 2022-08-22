//
// Created by DELL on 8/6/2022.
//
#include "List.h"
#include <cstring>
#include "error.h"

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<class T>
class ArrayList : public List<T> {
private:
  T* data;
  int count;
  int capacity;

  void ensureCapacity(int _capacity);
  void checkIndex(int index, bool isAddFunc = false) const;
public:
  ArrayList();
  void add(const T& element);
  void addAt(int index, const T& element);
  int size() const;
  bool checkEmpty() const;
  bool checkFull() const;
  T removeAt(int index);
  bool removeItem(const T& element);
  T getAt(int index) const;
  void setAt(int index, const T& element);
  int indexOf(const T& item) const;
  bool contains(const T& item) const;
  void getInfo() const;
  void clear();
};

template<class T>
void ArrayList<T>::checkIndex(int index, bool isAddFunc) const {
  if (isAddFunc) {
    if (index < 0 || index > this->count)
      throw IndexOutOfRangeException();
  }
  else if (index < 0 || index >= this->count)
    throw IndexOutOfRangeException();
}

template<class T>
void ArrayList<T>::ensureCapacity(int _capacity) {
  if (this->capacity < _capacity) {
    int newCapacity = this->capacity * 3/2;
    int* newData = new T[newCapacity];
    std::memmove(newData, this->data, this->count * sizeof(T)); // move memory from data to newData
    delete [] this->data;
    this->data = newData; // assign new address
    this->capacity = newCapacity;
  }
}

template<class T>
ArrayList<T>::ArrayList() {
  this->capacity = 10;
  this->data = new T[this->capacity];
  this->count = 0;
}

template<class T>
void ArrayList<T>::add(const T& element) {
  this->ensureCapacity(this->count+1);
  this->data[this->count] = element;
  this->count++;
}

template<class T>
void ArrayList<T>::addAt(int index, const T &element) {
  this->checkIndex(index, true);

  if (index == this->count) { // add at end
    this->add(element);
  }
  else if (index < this->count) {
    this->ensureCapacity(this->count+1);
    std::memmove(this->data+index+1, this->data+index, sizeof(T) * (this->count-index));
    this->data[index] = element;
    this->count++;
  } 
  else {
    throw std::out_of_range("Index is out of range");
  }
}

template<class T>
int ArrayList<T>::size() const {
  return this->count;
}

template<class T>
bool ArrayList<T>::checkEmpty() const {
  return (this->count == 0);
}

template<class T>
bool ArrayList<T>::checkFull() const {
  return (this->capacity == this->count);
}

template<class T>
T ArrayList<T>::removeAt(int index) {
  this->checkIndex(index);
  T res = this->data[index];
  std::memmove(this->data+index, this->data+index+1, sizeof(T) * (this->count-index-1)); // move to left one ele
  this->count--;

  return res;
}

template<class T>
bool ArrayList<T>::removeItem(const T& element) {
  for (int i = 0; i < this->count; ++i)
    if (data[i] == element) {
      this->removeAt(i);
      return true;
    }
  return false;
}

template<class T>
T ArrayList<T>::getAt(int index) const {
  this->checkIndex(index);
  return this->data[index];
}

template<class T>
void ArrayList<T>::setAt(int index, const T& element) {
  this->checkIndex(index);
  this->data[index] = element;
}

template<class T>
int ArrayList<T>::indexOf(const T &item) const {
  for (int i = 0; i < this->count; ++i)
    if (this->data[i] == item) {
      return i;
    }

  return -1;
}

template<class T>
bool ArrayList<T>::contains(const T& item) const {
  return (this->indexOf(item) != -1);
}

template<class T>
void ArrayList<T>::clear() {
  delete [] this->data;
  this->count = 0;
}

template<class T>
void ArrayList<T>::getInfo() const {
  std::cout << "Size of list: " << this->count << '\n'
            << "Capacity of list: " << this->capacity << '\n'
            << "Elements of list: \n";
  for (int i = 0; i < this->count; ++i)
      std::cout << this->data[i] << ' ';
}

#endif 
