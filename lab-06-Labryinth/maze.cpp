/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {

  this->width = width;
  this->height = height;

  this->positions = new Position **[width];
  
  int i, j, k;

  for (k = 0; k < width; k++) {
    this->positions[k] = new Position *[height];
  }

  for (i = 0; i < width; i++) {
    for (j = 0; j < height; j++) {
      this->positions[i][j] = new Position(i, j);
    }
  }

}

Maze::~Maze() {

  int i, j;
  for (i=0; i < width; i++) {
    for (j=0; j < height; j++) {
      delete this->positions[i][j];
    }
  }
  for (i = 0; i<width; i++) {
    delete[] this->positions[i];
  }
  delete[] this->positions;
}

int Maze::getWidth() {

  return this->width;
}

int Maze::getHeight() {

  return this->height;
}

bool Maze::isWall(int x, int y) {

  return this->positions[x][y]->isWall();
}

void Maze::setWall(int x, int y) {

  this->positions[x][y]->setWall();
}

List<Position*>* Maze::getNeighbors(Position* position) {

  List<Position*>* neighbor_list = new STLList<Position*>();

  int x = position->getX();
  int y = position->getY();

  int i, z;
  for (i = -1; i < 2; i = i + 2) {
    z = x+i;
    if ((0 <= (z)) && (z < this->width)) {
      if (position->isWall() == false) {
        neighbor_list->insertLast(this->positions[z][y]);
      }
    }
    
    z = y+i;
    if ((0 <= (z)) && (z < this->height)) {
      if (position->isWall() == false) {
        neighbor_list->insertLast(this->positions[x][z]);
      }
    }
  }  

  return neighbor_list;
}

List<Position*>* Maze::solveBreadthFirst() {

  OrderedCollection<Position*>* exploration = new LinkedQueue<Position*>;
  return solve(exploration);
}

List<Position*>* Maze::solveDepthFirst() {

  OrderedCollection<Position*>* exploration = new LinkedStack<Position*>;
  return solve(exploration);
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {

  Position* start = this->positions[0][0];
  Position* current = nullptr;
  
  exploration->insert(start);
  start->setVisited();
  while (exploration->getSize() != 0) {
    current = exploration->remove();
    if ((current->getX() == (width-1)) and (current->getY() == (height-1))){
      break;
    } else {
      List<Position*>* neighbor_list = getNeighbors(current);
      int size = neighbor_list->getSize();
      for (int i = 0; i < size; i++) {
        if (neighbor_list->get(i)->isVisited() == false) {
          neighbor_list->get(i)->setVisited();
          neighbor_list->get(i)->setPrevious(current);
          exploration->insert(neighbor_list->get(i));
        }
      }
    delete neighbor_list;
    }
  }
  delete exploration;
  List<Position*>* solve_list = new STLList<Position*>();
  current = this->positions[this->width-1][this->height-1];
  if (current->isVisited() == true) {
    solve_list->insertFirst(current);
    while (current->getPrevious() != nullptr) {
      solve_list->insertFirst(current->getPrevious());
      current = current->getPrevious();
    }
    return solve_list;
  }
  
  return nullptr;
}


