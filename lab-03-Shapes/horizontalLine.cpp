/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "horizontalLine.h"

HorizontalLine::HorizontalLine(int x, int y, int length, char symbol) {
  this ->x = x;
  this ->y = y;
  this ->length = length;
  this ->symbol = symbol;
}

void HorizontalLine::draw(Grid* grid) {
  for (int x = this-> x; x<(this->x + length); x++) {
        grid->placeSymbol(x, y, symbol);
  }
  grid->toString();
}