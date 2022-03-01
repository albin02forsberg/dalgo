#ifndef STUDENTSSHORTESTPATH_H
#define STUDENTSSHORTESTPATH_H

#include "graph.h"


const char* nameOfStudent2();

struct IVisualFeedback {
    virtual void knownDistanceToNode(Ixnode ixNode, float distane) = 0;
    virtual void nodeWasPlacedInPriorityQueue(Ixnode ixNode) = 0;
    virtual void nodeWasPoppedFromPriorityQueue(Ixnode ixNode) = 0;


};

std::vector<Ixnode> shortestPathBetweenNodes(const std::vector<Node>& graph, Ixnode ixStart, Ixnode ixStop, IVisualFeedback* pFeedback);
std::vector<Ixnode> shortestPathBetweenNodes2(const std::vector<Node>& graph,
                                        Ixnode ixStart, Ixnode ixStop, IVisualFeedback* pFeedback);

#endif // STUDENTSSHORTESTPATH_
