/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "helpers.h"

template <typename T> vector<T> dynamicListToStaticVector(List<T>* list) {
    //throw runtime_error("Not yet implemented: dynamicListToStaticVector");

  vector<T> vector1;
  int i;
  for (i = 0; i < list->getSize(); i++) {
    vector1.push_back(list->get(i));
    //vector1[i] = list->get(i); optional code for this
  }
  delete list;
  return vector1;

}
