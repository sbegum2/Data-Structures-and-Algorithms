/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>

#include "adts/list.h"
#include "asciimationFunctions.h"
#include "linkedList.h"

using namespace std;

List<pair<int, string>>* loadMovie(string filename) {
    
    ifstream myFile;
    string data2;
    string data = "";
    string frames;  
    List<pair<int,string>>* movie_list = new LinkedList<pair<int,string>>;

    myFile.open(filename);
    if (!myFile.is_open()) {
      throw runtime_error("File " + filename + " failed to open");
    }
    getline(myFile, frames);
    while (!myFile.eof()) {
      data = "";
      for (int i = 0; i<13; i++){
        getline(myFile, data2);
        data = data + data2 + "\n";
      }
      pair<int,string> p1;
      p1.first = stoi(frames); 
      p1.second = data;
      movie_list->insertLast(p1);
      getline(myFile, frames);
    }
    myFile.close();

    return movie_list;
    
}

void playMovie(List<pair<int, string>>* list) {
    
    for (int i = 0; i< (list->getSize()); i++) {
      cout << list->get(i).second << endl;
      int value = (1000000/15) * list->get(i).first;
      usleep(value);
      system("clear");
    }

    delete list;
    
}

void reverse_play(List<pair<int, string>>* list) {
  
  int size = list->getSize();
  for (int i = size-1; i >= 0; i--) {
      cout << list->get(i).second << endl;
      int value = (1000000/15) * list->get(i).first;
      usleep(value);
      system("clear");
    }

    delete list;
}