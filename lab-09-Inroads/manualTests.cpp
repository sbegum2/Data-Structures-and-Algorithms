/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include <UnitTest++/UnitTest++.h>

#include "adjacencyListGraph.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/dictionary.h"
#include "adts/graph.h"
#include "graphAlgorithms.h"
#include "ioUtils.h"

using namespace std;

Graph<string, int, int>* readGraphFile(string filename) {
    ifstream file(filename);
    string line;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    Graph<string, int, int>* graph =
        new AdjacencyListUndirectedGraph<string, int, int>();
    try {
        getline(file, line);
        while (line != "end") {
            if (line == "vertex") {
                string vertex;
                getline(file, vertex);
                graph->insertVertex(vertex);
            } else if (line == "edge") {
                string location1;
                getline(file, location1);
                string location2;
                getline(file, location2);
                int weight;
                getline(file, line);
                weight = stoi(line);
                graph->insertEdge(location1, location2, 0, weight);
            } else {
                throw std::runtime_error("Unexpected line in map file: " +
                                         line);
            }
            getline(file, line);
        }
    } catch (std::exception& e) {
        throw;
    }
    return graph;
}

int main(int argc, char** argv) {
    // You can use this main to experiment with the code you have written


    string filename = argv[1];
    int i; 

    Graph<string, int, int>* graph = readGraphFile(filename);

    vector<string> vertices = graph->getVertices();

    vector<string> path = shortestLengthPathBFS(string("Sam Curlytail"), string("Kevin Bacon"), graph);
    
    cout << "Test 1:" << endl;
    for (i = 0; i < path.size(); i++) {
      cout << path[i] << endl;
    }

/*
    path = shortestLengthPathBFS(vertices[18], vertices[9], graph);

    cout << "\nTest 2:" << endl;
    for (i = 0; i < path.size(); i++) {
      cout << path[i] << endl;
    }

    path = shortestLengthPathBFS(vertices[22], vertices[12], graph);

    cout << "\nTest 3:" << endl;
    for (i = 0; i < path.size(); i++) {
      cout << path[i] << endl;
    }

    path = shortestLengthPathBFS(vertices[1], vertices[18], graph);

    cout << "\nTest 4:" << endl;
    for (i = 0; i < path.size(); i++) {
      cout << path[i] << endl;
    }
*/
    delete graph;
    return 0;
}

