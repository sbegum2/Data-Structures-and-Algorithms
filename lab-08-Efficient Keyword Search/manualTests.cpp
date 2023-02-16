/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include "keywordSearcher.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // You can use this main to experiment with the code you have written

    KeywordSearcher ks;
    
    ks.loadWords("test_data/small.txt");

    vector<pair<int, int>> vector1 = ks.search("page");
    for (int i = 0; i < vector1.size(); i++) {
      cout << "(" << vector1[i].first << "," << vector1[i].second << ")" << endl;
    }

    

    return 0;
}
