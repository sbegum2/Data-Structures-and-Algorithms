#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

/**
 * Performs the main quick sort algorithm to sort the provided array.
 * @param array The array to sort.
 * @param startIndex The leftmost index (inclusive) of the part of the array
 *                   to sort.
 * @param endIndex The rightmost index (inclusive) of the part of the array
 *                 to sort.
 */
void quickSort(int* array, int startIndex, int endIndex);

/**
 * Wrapper function around the main quickSort function.
 * This function should get called once, then call quickSort
 *   with indices 0, size-1.
 * @param array The array to sort.
 * @param size  The size of the array.
 */
void qSort(int *array, int size);

/*
* This function uses the endIndex as the pivot point, reads through the array and
makes necessary swaps, and puts the pivot in the correct place.
* @param array: the array being sorted
* @param startIndex: the index to start reading the array at
* @param endIndex: the index to stop reading the array at
* returns k: the index of the pivot value
*/
int partition(int *array, int startIndex, int endIndex);

/*
*This function swaps two numbers in an array
*@param array: the array being sorted
*@param i: the index of the first number to swap
*@param j: the index of the second number to swap
*returns: none
*/
void swap(int* array, int i, int j);

/*
*This function prints out an array neatly, which was helpful for debugging
*@param array: the array to print
*@param size: the size of the array
*/
void print(int* array, int size);
