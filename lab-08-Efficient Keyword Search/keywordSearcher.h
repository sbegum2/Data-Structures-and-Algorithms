#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>
#include <vector>
#include <fstream>
#include "hashTable.h"

/**
 * This class represents a tool which can be used to perform a keyword search on
 * a document.  The user of this class instantiates it, updates it with words
 * from a document, and can then use it to identify the pages on which specific
 * words appear most frequently.
 */
class KeywordSearcher {
  public:
    /**
     * Creates a new keyword searcher with no data.
     */
    KeywordSearcher();

    /**
     * Destructs a KeywordSearcher and releases the memory it is using.
     */
    ~KeywordSearcher();

    /**
     * Loads the words from a given file into this searcher.
     * @param filename The name of the text file to use.
     */
    void loadWords(std::string filename);

    /**
     * Searches this object to find the pages on which a particular word most
     * frequently appeared.
     * @param word The word to find.
     * @return A vector of pairs between page numbers and occurrences.  The top
     *         ten pages are returned, ordered from most to least occurrences.
     *         All pairs have a positive (non-zero) number of occurrences; if a
     *         word appears on fewer than ten pages, the returned vector
     *         contains fewer than ten elements.
     */
    std::vector<std::pair<int, int>> search(std::string word);

  private:
    
    HashTable<std::string, HashTable<int, int>*>* table;
    std::ifstream string_file;
    
    /*
      Swaps the pair keys and values in a vector. For example, if the vector that is passed
      in is [(2,3) , (4,5)], this function would return [(3,2) , (5,4)]. 
    */
    std::vector<std::pair<int, int>> swap_vector_pairs(vector<pair<int, int>> vector1);
};
