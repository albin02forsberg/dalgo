#ifndef STUDENTSDRAWGRAPH_H
#define STUDENTSDRAWGRAPH_H

#include "graph.h"

#include <QPainter>

const char* nameOfStudent1();

void studentsDrawGraph(QPainter& painter,  const std::vector<Node>& graph );


#endif // STUDENTSDRAWGRAPH_H
