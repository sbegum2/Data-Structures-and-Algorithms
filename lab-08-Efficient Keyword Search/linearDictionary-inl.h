/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
using std::runtime_error;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {

    return this->vector1.size();
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {

    if (getSize() <= 0) {
        return true;
    }
    return false;
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {

    int i;
    for (i = 0; i < getSize(); i++) {
        if (this->vector1[i].first == key) {
            throw runtime_error("Key already exists");
        }
    }
    pair<K, V> new_pair(key, value); 
    this->vector1.push_back(new_pair);
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {

    int i;
    for (i = 0; i < getSize(); i++) {
        if (this->vector1[i].first == key) {
            this->vector1[i].second = value;
            return;
        }
    }
    throw runtime_error("Key not found");
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {

    int i;
    for (i = 0; i < getSize(); i++) {
        if (this->vector1[i].first == key) {
            return this->vector1[i].second;
        }
    }
    throw runtime_error("Key not found");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {

    int i;
    for (i = 0; i < getSize(); i++) {
        if (this->vector1[i].first == key) {
            return true;
        }
    }
    return false;
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {

    int i;
    for (i = 0; i < getSize(); i++) {
        if (this->vector1[i].first == key) {
            this->vector1.erase(vector1.begin() + i, vector1.begin() + i + 1);
            return;
        }
    }
    throw runtime_error("Key not found");
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {

    vector<K> kvec;
    int i;
    for (i = 0; i < getSize(); i++) {
        kvec.push_back(this->vector1[i].first);
    }

    return kvec;
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {

    return this->vector1;
}
