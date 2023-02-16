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

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {
    
    try {
      if (argc != 3) {
        throw runtime_error("Invalid number of command line arguments");
      }
    } catch (runtime_error e) {
      cout << "The command line takes in 2 arguments. The first is " << 
      "the maze file\n that you want to usse, and the second is " <<
      "the search type (breadth or depth).\n" << "Try entering " <<
      "'./maze test_data/cycle.map breadth' to begin!" << endl;
      exit(0);
    }

    string file = argv[1];
    string search_type = argv[2];
    List<Position*>* solve_list;

    Maze* maze;
    try {
      maze = loadMap(file);
    } catch (runtime_error e) {  
        cout << "Please try again with a valid file name" << endl;
        exit(0);
      }  

    try {
      if ((search_type != "breadth") && (search_type != "depth")) {
        throw runtime_error("Invalid search type");
      }
    } catch (runtime_error e) {
      while ((search_type != "breadth") && (search_type != "depth")) {
        cout << "Please enter either 'breadth' or 'depth' for the search type" <<
        endl;
        cin >> search_type;
      }
    }
    
    if (search_type == "breadth") {
      solve_list = maze->solveBreadthFirst();
    } else {
      solve_list = maze->solveDepthFirst();
    }

    if (solve_list == nullptr) {
      cout << "There was no solution to the map!" << endl;
      cout << "Try again with a different map to see if it has a solution." << endl;
    } else {
      string solution_map = renderAnswer(maze, solve_list);
      cout << solution_map << endl;
    }

    delete maze;
    delete solve_list;

    return 0;
}
