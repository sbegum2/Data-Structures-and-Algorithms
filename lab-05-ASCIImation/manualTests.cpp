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

int main() {
    // TODO: write any tests you want here; this is your sandbox

    /*    
    List<int>* linked_list = new LinkedList<int>;
    linked_list->insertFirst(21);
    linked_list->insertFirst(12);
    linked_list->insertLast(30);

    int first = linked_list->getFirst();
    int last = linked_list->getLast();    
    int index = linked_list->get(1);
    int size = linked_list->getSize();
    bool empty = linked_list->isEmpty();
    
    cout << "First: " << first << endl;
    cout << "Middle: " << index << endl;
    cout << "Last: " << last << endl;
    cout << "Size: " << size << endl;
    cout << "Empty: " << empty << endl;
    
    int firstRVal = linked_list->removeFirst();
    int LastRVal = linked_list->removeLast();
    first = linked_list->getFirst();
    last = linked_list->getLast();
    size = linked_list->getSize();

    cout << "First: " << first << endl;
    cout << "Last: " << last << endl;
    cout << "size: " << size << endl;

    firstRVal = linked_list->removeFirst();
    size = linked_list->getSize();

    cout << "Size: " << size << endl;

    //LastRVal = linked_list->removeLast(); //should produce runtime error
    
    delete linked_list;
    */
    
    List<pair<int, string>>* movie_list = loadMovie("test_data/scene3.asciimation");
    cout << movie_list->getFirst().first << endl;
    cout << movie_list->get(1).second << endl;
    cout << movie_list->get(2).first << endl;


        
    return 0;}
