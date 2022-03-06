#include "student1drawgraph.h"
#include <iostream>

const char* nameOfStudent1(){
    return  "Albin Forsberg";
}


void studentsDrawGraph(QPainter& painter,  const std::vector<Node>& graph){
    for(unsigned long int i = 0; i < graph.size(); i++){
        painter.fillRect(graph[i]._point.x(), graph[i]._point.y(), 1, 1, Qt::black);
        for(unsigned long int j = 0; j < graph[i]._outputs.size(); j++){
            Ixnode dest = graph[i]._outputs[j].m_ixDestination;
            painter.drawLine(graph[i]._point, graph[dest]._point);
        }
    }


}



