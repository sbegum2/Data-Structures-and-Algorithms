/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

//Tests for the amount of command line arguments, and sets variables accordingly.
//Throws error if invalid amount of command line arguments have been provided. 
//If there are 3 cmd line args, and the correct order/input has been provided, 
// (--reverse), main will run the additional function reverse_play to play the 
//asciimation in reverse. Otherwise, it will run the playMovie function given
//that the provided file name is valid.
// returns 0
int main(int argc, char** argv) {

    string if_reverse = "";
    string filename;

    if (argc == 2) {
      filename = argv[1];
    } else if (argc == 3) {
      filename = argv[2];
      if_reverse = argv[1];      
    } else {
      throw runtime_error("Invalid amount of command line arguments, must enter \
      1 or 2 arguments");
    }

    List<pair<int, string>>* movie_list = loadMovie(filename);
    if (if_reverse != ""){
      if (if_reverse == "--reverse"){
        reverse_play(movie_list);
      } else {
        throw runtime_error("Invalid method call. Valid method is '--reverse'. ");
      }
    } else {
      playMovie(movie_list);
    }

    return 0;
}
