/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "inroadsGUI.h"
#include "ioUtils.h"
#include "inroadsGame.h"

using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument: name of map file." << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line argument.
    string mapFilename = string(argv[1]);

    // Read the Inroads map file.
    pair<Graph<string, bool, int>*, Dictionary<string, pair<int, int>>*>
        mapFileContents;
    try {
        mapFileContents = readInroadsMap(mapFilename);
    } catch (exception e) {
        cout << "Could not read Inroads map file " << mapFilename << ": "
             << e.what() << endl;
    }
    // The map file contained the graph representing the map.  It also contained
    // the vertex positions (so we know where each vertex goes on the map).
    Graph<string, bool, int>* graph = mapFileContents.first;
    Dictionary<string, pair<int, int>>* vertexPositions =
        mapFileContents.second;

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object; do NOT change the type of this variable.
    InroadsGUI gui(vertexPositions, mapFilename);

    // Tell the GUI about the graph we have.
    gui.updateInroadsMap(graph);
    gui.updateScoreText("Score: 0");
    gui.updateTurnText("Turn: 1");

    pair<string, string> move;
    InroadsGame game(graph);
    while (game.getTurn() <= 21) {
        move = gui.getNextMove();
        
        if (move.first == "" || move.second == "") {
            break;
        }
        Edge<string, bool, int> edge = graph->getEdge(move.first, move.second);
                
        if (game.isImproved(edge)) {
            continue;
        }
        game.updateEdge(edge);
        game.scorePoints();
        graph = game.updateGUI();
        gui.updateInroadsMap(graph);
        gui.updateScoreText(game.updateScore());
        gui.updateTurnText(game.updateTurn());
        gui.updateMessage(game.updateText());
        
    }

    // Finally, clean up and exit successfully.
    delete graph;
    delete vertexPositions;
    return 0;
}
