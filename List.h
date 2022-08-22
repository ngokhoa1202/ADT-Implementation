//
// Created by DELL on 8/6/2022.
//

#ifndef LIST_H
#define LIST_H

template <class T>
class List {
public:
  virtual void add(const T& element) = 0;
  virtual void addAt(int index, const T& element) = 0;
  virtual int size() const = 0;
  virtual bool checkEmpty() const = 0;
  virtual T removeAt(int index) = 0;
  virtual bool removeItem(const T& element) = 0;
  virtual T getAt(int index) const = 0;
  virtual void setAt(int index, const T& element) = 0;
  virtual int indexOf(const T& item) const = 0;
  virtual bool contains(const T& item) const = 0;
  // virtual void merge(const List<T>& list) = 0;
  virtual void clear() = 0;
  virtual void getInfo() const = 0;
  //virtual ~List() = 0;
};

#endif 
