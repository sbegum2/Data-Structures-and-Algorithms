/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedStack.h"


using namespace std;

// NOTE: Most of the method bodies in this class will only require a
// single line of code!

template <typename T> LinkedStack<T>::LinkedStack() {
  this->list = new STLList<T>();
}

template <typename T> LinkedStack<T>::~LinkedStack() {
  delete this->list;
}

template <typename T> void LinkedStack<T>::push(T element) {
  this->list->insertFirst(element);
}

template <typename T> T LinkedStack<T>::pop() {
  return this->list->removeFirst();
}

template <typename T> void LinkedStack<T>::insert(T element) {
  this->push(element);
}

template <typename T> T LinkedStack<T>::remove() {
  return this->pop();
}

template <typename T> int LinkedStack<T>::getSize() {
  return this->list->getSize();
}

template <typename T> bool LinkedStack<T>::isEmpty() {
  return this->list->isEmpty();
}

template <typename T> T LinkedStack<T>::peek() {
  return this->list->getFirst();
}
