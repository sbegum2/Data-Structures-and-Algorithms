/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <fstream>
#include <string>

#include "image.h"
#include "ppmio.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 4) {
      cout << "Please include 4 arguments" << endl;
      return 1;
    }
    
  // creates vars for each arg
    string old_file = argv[1];
    string transformation = argv[2];
    string new_file = argv[3];

  // reads the dimensions of the old_file arg and stores this info in an array
  int *ppm = read_ppm(old_file);

  int width = ppm_width(old_file);

  int height = ppm_height(old_file);

  // matches transformation call to transformation; accounts for error
  if(transformation == "noRed") {
    noRed(width, height, ppm);

  } else if(transformation == "noGreen") {
      noGreen(width, height, ppm);

  } else if(transformation == "noBlue") {
      noBlue(width, height, ppm);

  } else if(transformation == "invert") {
      invert(width, height, ppm);

  } else if(transformation == "grayscale") {
      grayscale(width, height, ppm);

  } else if(transformation == "flipHorizontally") {
      flipHorizontally(width, height, ppm);

  } else if(transformation == "flipVertically") {
      flipVertically(width, height, ppm);
 
  } else {
      cout << "Error, please enter a valid transformation argument" << endl;
  }

  write_ppm(new_file, width, height, ppm);


  // cleans up file; saves space
  delete[] ppm;
  ppm = nullptr;
  
}