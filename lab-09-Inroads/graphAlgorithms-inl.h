/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include "adjacencyListGraph.h"

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    
    OrderedCollection<V>* exploration = new STLQueue<V>;
    exploration->insert(src);
    Dictionary<V, bool>* visited = new STLHashTable<V, bool>;
    visited->insert(src, true);
    V current;
    vector<V> neighbors;
    int i;
    while (!exploration->isEmpty()) {
        current = exploration->remove();
        if (current == dest) {
            delete exploration;
            delete visited;
            return true;
        }
        neighbors = g->getNeighbors(current);
        for (i = 0; i < neighbors.size(); i++) {
            if (!visited->contains(neighbors[i])) {
                exploration->insert(neighbors[i]);
                visited->insert(neighbors[i], true);
            }
        }
    }
    delete exploration;
    delete visited;
    return false;

}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    
    OrderedCollection<V>* exploration = new STLQueue<V>;
    exploration->insert(src);
    Dictionary<V, V>* previous = new STLHashTable<V, V>;
    previous->insert(src, src);
    V current;
    vector<V> path;
    vector<V> neighbors;
    int i, size;
    while (!exploration->isEmpty()) {
        current = exploration->remove();
        if (current == dest) {
            while (current != src) {
                path.push_back(current);
                current = previous->get(current);
            }
            path.push_back(src);
            size = path.size();
            for (i = 0; i < size/2; i++) {
                V temp = path[i];
                path[i] = path[size-1-i];
                path[size-1-i] = temp;
            }
            delete exploration;
            delete previous;
            return path;
        }
        neighbors = g->getNeighbors(current);
        for (i = 0; i < neighbors.size(); i++) {
            if (!previous->contains(neighbors[i])) {
                exploration->insert(neighbors[i]);
                previous->insert(neighbors[i], current);
            }
        }
    }
    delete exploration;
    delete previous;
    throw runtime_error("Path not found");
}

template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {

    PriorityQueue<W, V>* exploration = new STLMinPriorityQueue<W, V>;
    exploration->insert(0, src);
    Dictionary<V, W>* costs = new STLHashTable<V, W>;
    costs->insert(src, 0);
    V current;
    vector<Edge<V, E, W>> edges;
    V neighbor;
    W currentCost;
    W newCost;
    int i;
    while (!exploration->isEmpty()) {
        current = exploration->remove();
        currentCost = costs->get(current);
        edges = g->getOutgoingEdges(current);
        for (i = 0; i < edges.size(); i++) {
            neighbor = edges[i].getDestination();
            newCost = currentCost + edges[i].getWeight();
            if (!costs->contains(neighbor)) {
                costs->insert(neighbor, newCost);
                exploration->insert(newCost, neighbor);
            }
            else if (costs->get(neighbor) > newCost) {
                costs->update(neighbor, newCost);
                exploration->insert(newCost, neighbor);
            }
        }
    }
    delete exploration;
    return costs; // caller function needs to handle this deletion after use.
}
