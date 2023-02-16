/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <fstream>

using namespace std;

/* average
 * A function that takes the sum of all values in an array and finds their averages
 *  @param length: the amount of data values stored in the text file / 
    the first line in the text file
 *  @return average: the average of the values in the array
*/

float average(int length, int *array) { // 
  float sum = 0.0;
  float avg = 0.0;
  for (int i=0; i<length; i++) {
      sum += array[i];
  }

  avg = sum/length;
  return avg;
}

/* count_ten
 * An accumulator function that checks to see if a value in the array is less then 10.
   If the observed value is less than 10, the function adds 1 to an accumulator variable. 
 * @param length: the amount of data values stored in the text file / 
    the first line in the text file 
 * @param array: the values in the text file stored in one location
 * @return count: the amount of values in the array less than 10
*/

int count_ten(int length, int *array) {

  int count = 0;
  for (int i=0; i<length; i++) {
    if(array[i] < 10) {
      count += 1; 
    }
  }
  return count;
}

/* largest_number
 * An function that indexes through and compares each value in the array to find the largest value.
 * @param length: the amount of data values stored in the text file / 
    the first line in the text file 
 * @param array: the values in the text file stored in one location
 * @return largest: the maximum value in the array
*/

int largest_number(int length, int *array) {

  int large =-1;
  for (int i=0; i<length; i++) {
      if(array[i] > large) {
        large = array[i];
      }
  }
  return large;
}

/* last_number
 * An function that indexes through and compares each value in the array to find the largest value.
 * @param length: the amount of data values stored in the text file / 
    the first line in the text file 
 * @param array: the values in the text file stored in one location
 * @return last: the value stored in the final index of the array
*/

int last_number(int l, int *a) {

    int last;
    last = a[l-1];

  return last;

}

int main() {
  ifstream openfile;
  string file_name;
  int length;

  cout << "Enter a file name: ";
  cin >> file_name;
  string file;

  openfile.open(file_name);

  int *array = new int[length];
  openfile >> length;
  
  for (int i=0; i<length; i++) {
    openfile >> array[i];
  }
  
  int last = last_number(length, array);
  cout << "The last number is " << last << "." << endl;

  int large = largest_number(length, array);
  cout << "The largest number is " << large << "." << endl;

  int count = count_ten(length,array);
    cout << "There are " << count << " numbers less than 10 in the sequence" << "." << endl;

  float avg = average(length, array);
    cout << "The average is " << avg << "." << endl;

}
