/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

using std::runtime_error;

// This file defines the methods for two classes: LinkedListNode and LinkedList.
// The LinkedListNode methods have been defined for you.  You are responsible
// for defining the LinkedList methods.

// //////// LinkedListNode /////////////////////////////////////////////////////

template <typename T>
LinkedListNode<T>::LinkedListNode(T val, LinkedListNode<T>* next) {
    this->value = val;
    this->next = next;
}

// //////// LinkedList /////////////////////////////////////////////////////////

template <typename T> LinkedList<T>::LinkedList() {
    
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename T> LinkedList<T>::~LinkedList() {
    
    LinkedListNode<T>* current;
    for (int i = 0; i<this->size; i++) {
        current = this->head->next;
        delete this->head;
        this->head = current;
    }
}

template <typename T> void LinkedList<T>::checkInvariants() {
    
    int count = 0;
    for (int i = 0; i<this->size; i++) {
        count += 1;
    }
    if (count != this->size){
        throw runtime_error("Invariant Size showing incorrect size");
    }
}

template <typename T> int LinkedList<T>::getSize() {
    return this->size;
}

template <typename T> bool LinkedList<T>::isEmpty() {
    if (this->size <= 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T> T LinkedList<T>::getFirst() {
    
    if (this->size <= 0) {
        throw runtime_error("List currently has no values");
    }
    
    return this->head->value;
}

template <typename T> T LinkedList<T>::getLast() {
    
    if (this->size <= 0) {
        throw runtime_error("List currently has no values");
    }
    
    return this->tail->value;
}

template <typename T> T LinkedList<T>::get(int index) {
    
    if (index < 0) {
        throw runtime_error("Index value out of left-side bound (Too small)");
    } else if (index >= this->size) {
        throw runtime_error("Index value out of right-side bound (Too large)");
    }
    
    LinkedListNode<T>* current = this->head;
    for (int i = 0; i<index; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T> void LinkedList<T>::insertFirst(T value) {
    
    if (this->size <= 0) {
        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, nullptr);
        this->head = newNode;
        this->tail = newNode;
        this->size += 1;
    } else {
        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, this->head);
        this->size += 1;
        this->head = newNode;
    }     
}

template <typename T> void LinkedList<T>::insertLast(T value) {
    
    if (this->size <= 0) {
        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, nullptr);
        this->head = newNode;
        this->tail = newNode;
        this->size += 1;
    } else {
        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, nullptr);
        this->size += 1;
        this->tail->next = newNode;
        this->tail = newNode;
    }
}

template <typename T> T LinkedList<T>::removeFirst() {
    
    if (this->size > 1) {
        LinkedListNode<T>* current;
        current = this->head->next;
        T rval = this->head->value;
        delete this->head;
        this->head = current;
        this->size -= 1;
        return rval;
    } 
    if (this->size == 1) {
        T rval = this->head->value;
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
        this->size -= 1;
        return rval;
    } else {
        throw runtime_error("No values in list to remove. Try adding some values first.");
    }
}

template <typename T> T LinkedList<T>::removeLast() {
    
    if (this->size > 1) {
        LinkedListNode<T>* value = this->head;
        while (value->next->next != nullptr) {
            value = value->next;
        }
        value->next = nullptr;
        T rval = this->tail->value;
        delete this->tail;
        this->tail = value;
        this->size -= 1;
        return rval;
    } 
    if (this->size == 1) {
        T rval = this->tail->value;
        delete this->tail;
        this->head = nullptr;
        this->tail = nullptr;
        this->size -= 1;
        return rval;
    } else {
        throw runtime_error("No values in list to remove. Try adding some values first.");
    }
}
