/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "dataWriter.h"

class InroadsDataWriter : public DataWriter {
  public:
    InroadsDataWriter(ostream& output, bool debug = false);

    /**
     * Writes a point as an X-Y coordinate pair.
     */
    void writePoint(std::pair<int, int> point);

    /**
     * Writes a new game state message.
     */
    void writeGameMessage(std::string gameMessage);

    /**
     * Writes a new game graph.
     */
    void writeInroadsGraph(Graph<std::string, bool, int>* graph);

    /**
     * Writes the path of the map file.
     */
    void writeMapPath(std::string mapPath);

    /**
     * Writes text representing the current score.
     */
    void writeScoreText(std::string scoreText);

    /**
     * Writes text representing the current turn.
     */
    void writeTurnText(std::string turnText);

    /**
     * Writes new vertex positions.
     */
    void
    writeVertexPositions(Dictionary<std::string, pair<int, int>>* positions);
};
