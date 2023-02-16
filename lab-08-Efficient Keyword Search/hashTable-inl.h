/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "hashFunctions.h"
#include "linearDictionary.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {

    this->MLF = .75;
    this->capacity = 4;
    this->size = 0;
    this->table = new LinearDictionary<K, V>[this->capacity];
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {

    this->MLF = maxLoadFactor;
    this->capacity = 4;
    this->size = 0 ;
    this->table = new LinearDictionary<K, V>[this->capacity];
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {

    delete[] this->table;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {

    return this->size;
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {

    if (getSize() <= 0) {
        return true;
    }
    return false;
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {

    int index;
    index = hash(key, this->capacity);
    this->table[index].insert(key, value);
    this->size = this->size + 1;
    float load = float(this->size) / this->capacity;
    if (load > this->MLF) {
        ensureCapacity();
    }
}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {

    int index;
    index = hash(key, this->capacity);
    this->table[index].update(key, value);
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {

    int index = hash(key, this->capacity);
    return this->table[index].get(key);
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {

    int index = hash(key, this->capacity);
    return this->table[index].contains(key);
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {

    int index = hash(key, this->capacity);
    this->table[index].remove(key);
    
    this->size = this->size -1;
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {

    int i;
    vector<K> kvec, tvec;
    for (i = 0; i < this->capacity; i++) {
        tvec = this->table[i].getKeys();
        for (int j = 0; j < tvec.size(); j++) {
            kvec.push_back(tvec[j]);
        }
    }

    return kvec;
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {

    int i, j;
    vector<pair<K, V>> kvec, tvec;
    for (i = 0; i < this->capacity; i++) {
        tvec = this->table[i].getItems();
        for (j = 0; j < tvec.size(); j++) {
            kvec.push_back(tvec[j]);
        }
    }
    return kvec;
}

template <typename K, typename V> void HashTable<K, V>::ensureCapacity() {

    LinearDictionary<K, V> *temp = new LinearDictionary<K, V>[this->capacity*2];
    vector<pair<K, V>> svec = getItems();
    int i, index;
    K tempkey;
    V tempval;
    this->capacity = this->capacity * 2;
    for (i = 0; i < svec.size(); i++) {
        tempkey = svec[i].first;
        tempval = svec[i].second;
        index = hash(tempkey, this->capacity);
        temp[index].insert(tempkey, tempval);
    }
    delete[] this->table;
    this->table = temp;
}
