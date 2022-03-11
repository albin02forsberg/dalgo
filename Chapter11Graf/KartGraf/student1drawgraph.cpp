#include "student1drawgraph.h"
#include <iostream>

const char* nameOfStudent1(){
    return  "Albin Forsberg";
}


void studentsDrawGraph(QPainter& painter,  const std::vector<Node>& graph){
    for(const Node& node : graph){
        painter.fillRect(node._point.x(), node._point.y(), 1, 1, Qt::black);
        for(const Arc& arc : node._outputs){
            painter.drawLine(node._point, graph[arc.m_ixDestination]._point);
        }
    }


}



