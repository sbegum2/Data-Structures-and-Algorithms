/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {

    if (current == nullptr) {
        cout << "The key you are looking for could not be found." << endl;
        exit(0);
    }
    else if (current->getKey() == key) {
        return current->getValue();
    }
    else if (key < current->getKey()) {
        return findInSubtree(current->getLeft(), key);
    }
    else {
        return findInSubtree(current->getRight(), key);
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {

    if (current == nullptr) {
        return false;
    }
    else if (current->getKey() == key) {
        return true;
    }
    else if (key <= current->getKey()) {
        return containsInSubtree(current->getLeft(), key);
    }
    else {
        return containsInSubtree(current->getRight(), key);
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key,
                                      V value) {

    if (current == nullptr) {
        cout << "There is not a node with that key" << endl;
        exit(0);
    }
    else if (key == current->getKey()) {
        current->setValue(value); 
    }
    else if (key < current->getKey()) { 
        updateInSubtree(current->getLeft(), key, value);
    }
    else {
        updateInSubtree(current->getRight(), key, value);
    }
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {    
    
    if (current == nullptr) {
        return -1;
    }
    else {
        int LeftHeight = getHeightInSubtree(current->getLeft());
        int RightHeight = getHeightInSubtree(current->getRight());
        if (LeftHeight >= RightHeight) {
            return (LeftHeight +1);
        }
        else {
            return (RightHeight +1);
        }
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
    
    pair<K, V> node_pair;
    
    if (current->getLeft() == nullptr) {
        node_pair.first = current->getKey();
        node_pair.second = current->getValue();
        return node_pair;
    }
    else {
        return this->getMinInSubtree(current->getLeft());
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {

    if (isEmpty()) {
        exit(0);
    }
    else if (current->getRight() == nullptr) {
        pair<K, V> node_pair(current->getKey(), current->getValue());
        return node_pair;
    }
    else {
        return this->getMaxInSubtree(current->getRight());
    }
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {

    if (current == nullptr) {
        LinkedBSTNode<K, V>* node = new LinkedBSTNode<K, V>(key, value);
        return node;
    }
    else if (key == current->getKey()) {
        cout << "Trying to insert a key that already exists" << endl;
        exit(0);
    }
    else if (key < current->getKey()) { 
        current->setLeft(insertInSubtree(current->getLeft(), key, value));
        return current;
    }
    else {
        current->setRight(insertInSubtree(current->getRight(), key, value));
        return current;
    }
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {

    if (current == nullptr) {
        cout << "There is not a node with that key to remove." << endl;
        exit(0);
    }
    else if (key < current->getKey()) {
        current->setLeft(removeFromSubtree(current->getLeft(), key));
        return current;
    }
    else if (key > current->getKey()) {
        current->setRight(removeFromSubtree(current->getRight(), key));
        return current;
    }
    else if ((current->getLeft() == nullptr) && (current->getRight() == nullptr)) {
        delete current;
        return nullptr;
    }
    else if ((current->getLeft() != nullptr) && (current->getRight() == nullptr)) {
        return current->getLeft();
    }
    else if ((current->getLeft() == nullptr) && (current->getRight() != nullptr)) {
        return current->getRight();
    }
    else {
        K smallkey;
        smallkey = getMinInSubtree(current->getRight()).first;
        V val = get(key);
        current->setKey(smallkey);
        current->setValue(val);
        current->setRight(removeFromSubtree(current->getRight(), smallkey));
        return current;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {

    if (current != nullptr) {
        deleteSubtree(current->getLeft());
        deleteSubtree(current->getRight());
        delete current;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {

    if (current == nullptr) {
        return;
    }
    else {
        pair<K, V> new_pair(current->getKey(), current->getValue());
        list->insertLast(new_pair);
        buildPreOrderTraversal(current->getLeft(), list);
        buildPreOrderTraversal(current->getRight(), list);
    }

}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {

    if (current == nullptr) {
        return;
    }        
    buildInOrderTraversal(current->getLeft(), list);
    pair<K, V> new_pair(current->getKey(), current->getValue());
    list->insertLast(new_pair);
    buildInOrderTraversal(current->getRight(), list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
    //throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildPostOrder");

    if (current == nullptr) {
        return;
    }
    buildPostOrderTraversal(current->getLeft(), list);
    buildPostOrderTraversal(current->getRight(), list);
    pair<K, V> new_pair(current->getKey(), current->getValue());
    list->insertLast(new_pair);
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
