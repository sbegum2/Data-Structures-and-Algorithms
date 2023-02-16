/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <vector>

#include "keywordSearcher.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc < 2 || argc > 2) {
      cout << "\tError - Invalid number of arguments.." << endl;
      cout << "\tYou must provide exactly one argument: the file you wish to use" << endl;
      exit(0);
    }

    string filename;
    filename = argv[1];
    KeywordSearcher ks;
    
    try {
      ks.loadWords(filename);
    } catch (runtime_error e) {
      cout << "\tInvalid file name, please try again.." << endl;
      exit(0);
    }
    cout << "File Loaded" << endl;
    cout << endl;

    string user_input;
    cout << "Please enter a search word of '!' to quit: ";
    cin >> user_input; 

    vector<pair<int, int>> vector1;
    int i;
    while (user_input != "!") {
      vector1 = ks.search(user_input);
      if (vector1.size() == 0) {
        cout << "The word '" + user_input + "' does not appear in the file." << endl;
      }
      else {
        cout << "The word '" + user_input + "' appears in the file..." << endl;
        for (i = 0; i < vector1.size(); i++) {
          cout << "\ton page " << vector1[i].first << " (" << vector1[i].second 
            << " occurrences)" << endl;
        }
      }
      cout << endl;
      cout << "Please enter a search word of '!' to quit: ";
      cin >> user_input;
      cout << endl;
    }
    
    cout << "\nGoodbye!" << endl;

    return 0;
}
