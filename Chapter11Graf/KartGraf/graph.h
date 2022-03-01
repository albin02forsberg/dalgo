#ifndef GRAPH_H
#define GRAPH_H

#include <QPoint>
#include <vector>

typedef int Ixnode;


struct Arc{
    Arc(Ixnode ixNode, bool isVisible, float cost)
        : m_ixDestination(ixNode), m_isVisible(isVisible), m_cost(cost) {}

    Ixnode  m_ixDestination;
    bool    m_isVisible;
    float  m_cost;
};


struct Node{
    QPoint           _point;
    std::vector<Arc> _outputs;
};

typedef std::vector<Node> Graph;

#endif // GRAPH_H
