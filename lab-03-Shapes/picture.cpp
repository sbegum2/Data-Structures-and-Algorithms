/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <stdexcept>

#include "picture.h"
#include "grid.h"

using namespace std;

Picture::Picture() {
    this->numberOfShapes = 0;
    this->shapes = new Shape*[50];
}


Picture::~Picture() {
    for(int i=0; i<this->numberOfShapes; i++) {
        delete shapes[i];
    }
    delete [] this->shapes;
}


string Picture::toString() {
    Grid* grid = new Grid();
    for(int i=0; i<this->numberOfShapes; i++) {
        this->shapes[i]->draw(grid);
    }

    string grid_point = grid->toString();
    delete grid;

    return grid_point;
}


void Picture::print() {
    cout << this->toString() << endl;
}


void Picture::addShape(Shape* shape) {
    shapes[numberOfShapes] = shape;
    this->numberOfShapes = numberOfShapes+1;

}



