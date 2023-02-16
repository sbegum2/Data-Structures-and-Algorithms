/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "keywordSearcher.h"
#include "adts/stlMaxPriorityQueue.h"

#include <stdexcept>
#include <iostream>

using namespace std;

KeywordSearcher::KeywordSearcher() {

    this->table = new HashTable<string, HashTable<int, int>*>();
}

KeywordSearcher::~KeywordSearcher() {
    
    vector<pair<string, HashTable<int, int>*>> vector1;
    vector1 = this->table->getItems();

    int i, vsiz = vector1.size();
    for (i = 0; i < vsiz; i++) {
        delete vector1[i].second;
    }
    
    delete this->table;
}

void KeywordSearcher::loadWords(string filename) {

    string data;
    this->string_file.open(filename);
    if (!this->string_file.is_open()) {
        throw runtime_error("File " + filename + " not found");
    }

    int page = 0;
    this->string_file >> data;
    HashTable<int, int>* sectable;
    int curr; 
    while (!this->string_file.eof()) {
        //if we've seen this word before
        if (this->table->contains(data)) {
            //if pages are the same
            if (this->table->get(data)->contains(page)) {
                curr = this->table->get(data)->get(page);
                this->table->get(data)->update(page, curr+1);
            }
            //if pages are different
            else {
                this->table->get(data)->insert(page, 1);
            }
        }
        //if this word is the page identifier
        else if (data == "$$@@$$PAGE:") {
            this->string_file >> data;
            page = stoi(data);
        }
        //if new word and not page identifier
        else {
            sectable = new HashTable<int, int>();
            sectable->insert(page, 1);
            this->table->insert(data, sectable);
        }
        this->string_file >> data;
    }
}

vector<pair<int, int>> KeywordSearcher::search(string word) {
    
    vector<pair<int, int>> vector1;
    if (!this->table->contains(word)) {
        return vector1;
    }

    vector1 = this->table->get(word)->getItems();

    vector<pair<int, int>> vector2;
    vector2 = swap_vector_pairs(vector1);
    
    STLMaxPriorityQueue<int, int> pqueue(vector2);

    vector<pair<int, int>> vector3;
    int occ, page, i;
    if (pqueue.getSize() > 10) {
        for (i = 0; i < 10; i++) {
            occ = pqueue.peekPriority();
            page = pqueue.remove();
            pair<int, int> new_pair;
            new_pair.first = page;
            new_pair.second = occ;
            vector3.push_back(new_pair);
        }
    }
    else {
        while (!pqueue.isEmpty()) {
            occ = pqueue.peekPriority();
            page = pqueue.remove();
            pair<int, int> new_pair;
            new_pair.first = page;
            new_pair.second = occ;
            vector3.push_back(new_pair);
        }
    }

    return vector3;
}

vector<pair<int, int>> KeywordSearcher::swap_vector_pairs(vector<pair<int, int>> vector1) {
    
    int i, temp1, temp2;
    vector<pair<int, int>> vector2;

    for (i = 0; i < vector1.size(); i++) {
        temp1 = vector1[i].first;
        temp2 = vector1[i].second;
        pair<int, int> new_pair;
        new_pair.first = temp2;
        new_pair.second = temp1;
        vector2.push_back(new_pair);
    }

    return vector2; 

}
