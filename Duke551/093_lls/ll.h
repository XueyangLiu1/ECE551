#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
class OOB : public std::exception {
 public:
  const char * what() const throw() { return "Out of boundary"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d) : data(d), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * traverse = rhs.head;
    while (traverse != NULL) {
      addBack(traverse->data);
      traverse = traverse->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList l(rhs);
      std::swap(l.head, head);
      std::swap(l.tail, tail);
      std::swap(l.size, size);
    }
    return *this;
  }
  ~LinkedList() {
    Node * traverse = head;
    Node * temp = NULL;
    while (traverse != NULL) {
      temp = traverse->next;
      delete traverse;
      traverse = temp;
    }
  }
  void addFront(const T & item) {
    Node * n = new Node(item);
    n->next = head;
    if (head != NULL) {
      head->prev = n;
    }
    else {
      tail = n;
    }
    head = n;
    size += 1;
  }
  void addBack(const T & item) {
    Node * n = new Node(item);
    n->prev = tail;
    if (tail != NULL) {
      tail->next = n;
    }
    else {
      head = n;
    }
    tail = n;
    size += 1;
  }
  bool remove(const T & item) {
    Node * traverse = head;
    while (traverse != NULL && traverse->data != item) {
      traverse = traverse->next;
    }
    if (traverse == NULL) {
      return false;
    }
    Node * nextN = traverse->next;
    Node * prevN = traverse->prev;
    if (nextN != NULL) {
      nextN->prev = prevN;
    }
    else {
      tail = prevN;
    }
    if (prevN != NULL) {
      prevN->next = nextN;
    }
    else {
      head = nextN;
    }
    size -= 1;
    delete traverse;
    return true;
  }
  T & operator[](int index) {
    try {
      if (index < 0 || index > size - 1) {
        throw OOB();
      }
    }
    catch (OOB & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * traverse = head;
    for (int i = 0; i < index; i++) {
      traverse = traverse->next;
    }
    return traverse->data;
  }
  const T & operator[](int index) const {
    try {
      if (index < 0 || index > size - 1) {
        throw OOB();
      }
    }
    catch (OOB & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * traverse = head;
    for (int i = 0; i < index; i++) {
      traverse = traverse->next;
    }
    return traverse->data;
  }
  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  int getSize() const { return size; }
  friend void testList(void);
};

#endif
