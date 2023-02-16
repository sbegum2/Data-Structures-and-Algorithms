/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <UnitTest++/UnitTest++.h>
#include <iostream>

#include "quickSort.h"

using namespace std;

TEST(threeElements) {
  // Create a static array containing the numbers 4, 8, 6.
  int array[3] = {4, 8, 6};
  quickSort(array, 0, 2);
  CHECK_EQUAL(4, array[0]);
  CHECK_EQUAL(6, array[1]);
  CHECK_EQUAL(8, array[2]);
}

TEST(reverseSorted) {
  int size = 20;
  // Create a dynamically-allocated array
  int *array = new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = size - 1 - i;
  }
  quickSort(array, 0, size - 1);
  for (int i = 0; i < size; i++) {
    CHECK_EQUAL(i, array[i]);
  }
  // de-allocate array
  delete[] array;
  array = nullptr;
}

TEST(singleSort) {
  int array[1] = {0};
  // Create a static array of size 1

  int size = 1;
  quickSort(array, 0, size-1);
    CHECK_EQUAL(size-1, array[size-1]);
}


TEST(staySort) {
  int array[5] = {1,3,5,6,9};
  // Creates a sorted static array containing the numbers 1, 3, 5, 6, 9

  int size = 5;
  int store_array[5] = {1,3,5,6,9};
  quickSort(array, 0, 4);
  for(int i=0; i<5; i++) {
    CHECK_EQUAL(array[i], store_array[i]);
  }
}

TEST(dupeSort) {
  // Creates a static array containing some duplicate values
  int array[7] = {4,1,1,9,6,9,8};
  

  int size = 7;

  quickSort(array,0,7);
  CHECK_EQUAL(array[0], array[1]);
  CHECK_EQUAL(array[5], array[6]);

}


TEST(midpointSort) {
  /*
  Creates a dynamically-allocated array of size 100. 
  Indexes through array[i] and either leaves the value in place or 
  swaps it to back or front of the array (whose size is diminishing by 1 
  until the midpoint is reached), depending on the condition of array[i]
  and array[i+1]. 
  
  If array[i+1] is smaller than array[i], array[i+1]
  swaps places with the value at the minimum index. If array[i+1] is 
  larger than array[i], array[i+1] swaps places with the value at the 
  maximum index. 
  */

  int min = 0;
  int max = 101;
  int* array = new int[101];
  for(int i=min; i<max; i+=2) {
     array[i] = i/2;
     array[i+1] = 100 - i/2;
  }
  quickSort(array, 0, 100);
  int* array_sorted = new int[101];
  for(int i=min; i<max; i++) {
    array_sorted[i] = i;
  }
  for(int i=0; i<max; i++) {
    CHECK_EQUAL(array[i], array_sorted[i]);
  }
  delete[] array;
  array = nullptr;
  delete[] array_sorted;
  array_sorted = nullptr;
  }

TEST(debugSort) {
  /* 
  Creates a large static array to test program under
  different variations of numbers and conditions.
  */
  
  int array[11] = {4,1,1,5,6,10,5,9,8,9,11};
  quickSort(array, 0, 10);
  int array_sorted[11] = {1,1,4,5,5,6,8,9,9,10,11};
  for(int i=0; i<11; i++) {
    CHECK_EQUAL(array[i], array_sorted[i]);
  }

}

/* no need to modify main */
int main() {
  return UnitTest::RunAllTests();
}
