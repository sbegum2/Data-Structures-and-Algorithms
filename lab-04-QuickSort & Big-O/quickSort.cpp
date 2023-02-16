/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/
#include <iostream>
#include "quickSort.h"
using namespace std;
// TODO: you will need to write an appropriate "partition" function here
// It does not need to be in your header file because no one else will call it.

void swap(int* array, int i, int j) {
    int store_i = array[i];
    int store_j = array[j];

    array[i] = store_j;
    array[j] = store_i;

}
void print(int* array, int size) {
  cout << "[";
  for(int i=0; i<size; i++) {
    cout << array[i] << ", ";
  }
  cout << "]\n";

}

int partition(int *array, int startIndex, int endIndex) {

  int i = startIndex;
  int j = (endIndex);
  int pivot = array[endIndex];

  while(i<j) {

    while((i<j) and (array[i]<=pivot)) {
      i = i + 1;

    }
    while((i<j) and (array[j]>=pivot)) {
      j = j - 1;

    }
    if(i!=j) {
        swap(array, i, j);
    }
  }


  while((array[i] <= array[endIndex]) and (i<endIndex)) {
    i++;
  }


  if (i!=endIndex){
    swap(array, i, endIndex);
  }
  return i;
     }


void qSort(int *array, int size) {
  quickSort(array, 0, size-1);
}

void quickSort(int* array, int i, int j) {
    int size = j-i+1;

    if(size > 1) {

        int k = partition(array, i, j);

    quickSort(array, i, k-1);
    quickSort(array, k+1, j);

    }
}
