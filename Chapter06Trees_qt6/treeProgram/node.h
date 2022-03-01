// Copyright (c) by Ragnar Nohre

#ifndef NODE_H
#define NODE_H
#include "visualnode.h"


struct Node : VisualNode
{
    int   m_key;
    Node *m_pLeft;
    Node *m_pRight;

    void flash();
    bool isTarget();
    void makeRed();

    Node(int key, Node *pLeft=nullptr, Node *pRight=nullptr);
    ~Node();
};

#endif // NODE_H
