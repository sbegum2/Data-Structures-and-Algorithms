/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include "inroadsGUI.h"
#include "adjacencyListUndirectedGraph.h"
#include "graphAlgorithms.h"
#include "adts/edge.h"

/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */
class InroadsGame {
  public:
    
    /*
     * Creates a new Inroads game. A graph object gets passed into
     * this constructor so that we can play the game. 
    */
    InroadsGame(Graph<std::string, bool, int>* graph);

    /*
     * Destructs an Inroads game and releases the memory it is using
    */
    ~InroadsGame();

    /*
     * Takes in an edge and determines if the edge is improved or not
     * by getting the label and seeing if it is true.
     * Returns true is improved; false otherwise. 
    */
    bool isImproved(Edge<std::string, bool, int> edge);

    /*
     * Returns the current turn of the Inroads Game that the user is playing
    */
    int getTurn();

    /*
     * Returns the current score as a string. To be called to update
     * the gui score text. 
    */
    std::string updateScore();
  
    /*
     * Returns the current turn as a string. To be called to update
     * the gui turn text. 
    */
    std::string updateTurn();

    /*
     * Returns the updated string that the GUI should print out. to
     * be called to update the gui text box. 
    */
    std::string updateText();

    /*
     * Removes the edge that the player clicked on, and then re-inserts
     * the same edge with a "true" value label. 
    */
    void updateEdge(Edge<std::string, bool, int> edge);

    /*
     * Returns the current state of the graph to update the GUI image
    */
    Graph<std::string, bool, int>* updateGUI();
    
    /*
     * This is the method that will be called to score points.
     * Calls several helper methods that use the graphing algorithms 
     * to score points based on the location types. Assigns the various 
     * score fields accordingly. 
    */
    void scorePoints();

    /*
     * This methods will be called to score the hospital points 
     * using the sssp and reachableDFS graph algorithms. Returns 
     * the points scored as an int value. 
    */
    int scoreHospital();

    /*
     * This method will be called to score the library points
     * using the reachableDFS graph algorithm. Returns the points
     * scored as an int value.
    */
    int scoreLibrary();

    /*
     * This method will be called to score the store points
     * using the reachableDFS and shortestLengthPathBFS graph 
     * algorithms. Returns the points scored as an int value. 
    */
    int scoreStore();

  private:
            //Private Helper Methods//
    
    /*
     * Methods for the constructor to call. It will create the vectors
     * for each type of location. Takes no parameters, returns nothing
    */
    void findLocations();

    /*
     * Creates a copy of the parameter graph. The returned graph only contains
     * the improved edges from the argument graph. 
    */
    Graph<std::string, bool, int>* create_copy(Graph<std::string, bool, int>* graph);

    
            //Private Fields//

    int score; // main score variable that will be used to determine the current score
    int lib_score; // score variable that will be used to keep track of points earned from libraries
    int hosp_score; // score variable that will be used to keep track of points earned from hospitals
    int str_score; // score variable that will be used to keep track of points earned from stores

    //turn variable that will be used to determine the current turn
    int turn;

    std::vector<std::string> hospitals; //vector that stores hospitals vertices
    std::vector<std::string> residences; //vector that stores residence vertices
    std::vector<std::string> libraries; //vector that stores library vertices
    std::vector<std::string> stores; //vector that stores store vertices

    //the graph field that we will use to play the game
    Graph<std::string, bool, int>* graph;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  private:
    InroadsGame(const InroadsGame& other) = delete;
    InroadsGame& operator=(const InroadsGame& other) = delete;
};
