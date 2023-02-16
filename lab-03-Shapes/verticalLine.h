#pragma once

/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include "shape.h"

// TODO: Declare your VerticalLine class here.

/**
 * A class representing a vertical line.
 */
class VerticalLine : public Shape {
  public:
    VerticalLine(int x, int y, int length, char symbol);

    /**
     * Draws this shape on the provided grid.
     * @param grid The grid onto which to draw the shape.
     */

    void draw(Grid* grid);

  private:
    int x;
    int y;
    int length;
    char symbol;

};

// need to have this move downwards
