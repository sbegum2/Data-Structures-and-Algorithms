/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

#include "inroadsGame.h"
#include "stringUtils.h"

using namespace std;

InroadsGame::InroadsGame(Graph<std::string, bool, int>* graph) {

  this->graph = graph;
  this->score = 0;
  this->lib_score = 0;
  this->hosp_score = 0;
  this->str_score = 0;
  this->turn = 1;
  findLocations();
}

InroadsGame::~InroadsGame() {
}

void InroadsGame::findLocations() {

  vector<string> vertices = this->graph->getVertices();

  int i;
  for (i = 0; i < vertices.size(); i++) {
    if (vertices[i][0] == 'M') {
      this->hospitals.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'R') {
      this->residences.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'S') {
      this->stores.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'L') {
      this->libraries.push_back(vertices[i]);
    }
  }
}

bool InroadsGame::isImproved(Edge<std::string, bool, int> edge) {
  
  bool label = edge.getLabel();
  return label;
}

int InroadsGame::getTurn() {

  return this->turn;
}

string InroadsGame::updateScore() {
  
  string text = "Score: " + to_string(this->score);
  return text;
}

string InroadsGame::updateTurn() {
  
  this->turn = this->turn +1;
  if (this->turn > 20) {
    return "Game Over";
  }
  
  string text = "Turn: " + to_string(this->turn);
  return text;
}

string InroadsGame::updateText() {
 
  int round_score = this->lib_score + this->str_score + this->hosp_score;
  string text = "Your score this turn: \n \t+ " + 
    to_string(this->lib_score) + " from the library \n \t+ " + 
    to_string(this->str_score) + " from stores\n \t+ " + 
    to_string(this->hosp_score) + " from medical access \n Total points this turn: " + 
    to_string(round_score);
  return text;
}

void InroadsGame::updateEdge(Edge<std::string, bool, int> edge) {

  graph->removeEdge(edge.getSource(), edge.getDestination());
  graph->insertEdge(edge.getSource(), edge.getDestination(), true, edge.getWeight());
  
}

Graph<std::string, bool, int>* InroadsGame::updateGUI() {
 
  return this->graph;
}

void InroadsGame::scorePoints() {

  this->hosp_score = scoreHospital(); 
  this->lib_score = scoreLibrary();
  this->str_score = scoreStore();
  this->score = this->score + this->hosp_score + this->lib_score + this->str_score;
}

int InroadsGame::scoreHospital() {

  Graph<std::string, bool, int>* graph2 = create_copy(this->graph);
  Dictionary<string, int>* weights;
  int score = 0, k, l;
  
  for (k = 0; k < this->hospitals.size(); k++) {
    weights = singleSourceShortestPath(this->hospitals[k], graph2);
    for (l = 0; l < this->residences.size(); l++) {
      if (reachableDFS(this->hospitals[k], this->residences[l], graph2)) {
        score += 420/(weights->get(this->residences[l]));
      }
    }
    delete weights;
  }  

  delete graph2;
  return score;
}

int InroadsGame::scoreLibrary() {

  Graph<std::string, bool, int>* graph2 = create_copy(this->graph);
  
  bool yes;
  int score = 0, i;
  
  for (i = 0; i < this->residences.size(); i++) {
    yes = reachableDFS(this->libraries[0], this->residences[i], graph2);
    if (yes == true) {
      score += 15;
    }
  }
  
  delete graph2;
  return score;
}

int InroadsGame::scoreStore() {

  int score = 0, j, i;
  vector<string> short_path; 
  Graph<std::string, bool, int>* graph2 = create_copy(this->graph);

  for (i = 0; i < this->residences.size(); i++) {
    for (j = 0; j < this->stores.size(); j++) {
      if (reachableDFS(this->residences[i], this->stores[j], graph2)) {
        short_path = shortestLengthPathBFS(this->residences[i], this->stores[j], graph2);
        if (short_path.size() < 4) {
          score += 10;
        }
      }        
    }
  }
  
  delete graph2;
  return score;
}

Graph<std::string, bool, int>* InroadsGame::create_copy(Graph<std::string, bool, int>* graph) {

  Graph<std::string, bool, int>* graph2 = new AdjacencyListUndirectedGraph<std::string, bool, int>();
  vector<string> vertices = graph->getVertices();
  int esize, i, k, l;

  for (k = 0; k < vertices.size(); k++) {
    graph2->insertVertex(vertices[k]);
  }
  
  vector<Edge<string, bool, int>> edges = graph->getEdges();
  for (l = 0; l < edges.size(); l++) {
    graph2->insertEdge(edges[l].getSource(), edges[l].getDestination(), edges[l].getLabel(), edges[l].getWeight());
  }
  
  esize = edges.size();
  for (i = 0; i < esize; i++) {
    if (edges[i].getLabel() == false) {
      graph2->removeEdge(edges[i].getSource(), edges[i].getDestination());
    }
  }

  return graph2; //caller is responsible for cleanup
}