/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include <utility>
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"
#include "helpers.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {

  this->root = nullptr;
  this->size = 0; 
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {

  deleteSubtree(this->root);
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {

  return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {

  if (this->size == 0) {
    return true;
  }
  return false;
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {

  this->root = insertInSubtree(this->root, key, value);
  this->size = this->size + 1;
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {

  updateInSubtree(this->root, key, value);
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {

  return findInSubtree(this->root, key);
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {

  return containsInSubtree(this->root, key);
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {

  this->root = removeFromSubtree(this->root, key);
  this->size = this->size -1;
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {

  vector<K> new_vector;
  vector<pair<K, V>> vector1;
  vector1 = traversePreOrder();
  int i;
  for (i = 0; i < vector1.size(); i++) {
    new_vector.push_back(vector1[i].first);
  }
  return new_vector;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {

  vector<pair<K, V>> vector1;
  vector1 = traversePreOrder();

  return vector1;
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {

  return getHeightInSubtree(this->root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {

  return getMaxInSubtree(this->root).first;
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {

  return getMinInSubtree(this->root).first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {

  List<pair<K, V>>* list = new STLList<pair<K, V>>();
  buildPreOrderTraversal(this->root, list);
  vector<pair<K, V>> new_vector;
  new_vector = dynamicListToStaticVector(list);
  return new_vector;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {

  List<pair<K, V>>* list = new STLList<pair<K, V>>();
  buildInOrderTraversal(this->root, list);
  vector<pair<K, V>> new_vector;
  new_vector = dynamicListToStaticVector(list);
  return new_vector;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {

  List<pair<K, V>>* list = new STLList<pair<K, V>>();
  buildPostOrderTraversal(this->root, list);
  vector<pair<K, V>> new_vector;
  new_vector = dynamicListToStaticVector(list);
  return new_vector;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {

  vector<pair<K, V>> vector1;
  pair<K, V> new_pair;
  Queue<LinkedBSTNode<K, V>*>* queue = new STLQueue<LinkedBSTNode<K, V>*>;
  queue->enqueue(this->root);
  LinkedBSTNode<K, V>* current;
  
  while (queue->getSize() != 0) {
    
    current = queue->dequeue();
    new_pair.first = current->getKey();
    new_pair.second = current->getValue();
    vector1.push_back(new_pair);
    
    if (current->getLeft() != nullptr) {
      queue->enqueue(current->getLeft());
    }
    if (current->getRight() != nullptr) {
      queue->enqueue(current->getRight());
    }
  }

  delete queue;
  return vector1;
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false
        // arguments indicate that they do not apply.  But we need a
        // value of type K to fill this parameter since we don't have
        // globally min/max K values generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
