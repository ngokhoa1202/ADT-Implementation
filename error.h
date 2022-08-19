#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

class StackUnderflowException : public std::exception {
private:
  std::string message;
public:
  StackUnderflowException() : message("Stack underflow exception") {}
  const char *what() const throw() {
    return message.c_str();
  }
};

class IndexOutOfRangeException : public std::exception {
private:
  std::string message;
public:
  IndexOutOfRangeException() : message("Index out of range exception") {} 
  const char *what() const throw() {
    return message.c_str();
  }  
};



#endif