/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(int x, int y, int width, int height, char symbol) {
  this ->x = x;
  this ->y = y;
  this ->width = width;
  this ->height = height;
  this ->symbol = symbol;
}

void Rectangle::draw(Grid* grid) {
  for (int x = this-> x; x < (this->x + width); x++) {
      for (int y = this-> y; y<(this->y + height); y++) {
        grid->placeSymbol(x, y, symbol);
      }
  }
  grid->toString();

}