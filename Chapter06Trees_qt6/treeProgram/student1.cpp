#include "node.h"
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <QDebug>

#include "students.h"

const char* nameOfStudent1(){
    return "Albin Forsberg";
}




/**************************************************************************
 * Trädklättring.
 *
 *
 **************************************************************************/

Node* testTree1(){
//    Node* Node4 = new Node(4, nullptr, nullptr);
//    Node *Node2 = new Node(2, Node4, nullptr);

//    Node *Node6 = new Node(6, nullptr, nullptr);
//    Node *Node5 = new Node(5, nullptr, nullptr);

//    Node *Node3 = new Node(3, Node5, Node6);

//    Node *Node1 = new Node(1, Node2, Node3);

    Node *Node4 = new Node(4, nullptr, nullptr);
    Node *Node5 = new Node(5, nullptr, nullptr);
    Node *Node3 = new Node(3, nullptr, nullptr);

    Node *Node2 = new Node(2, Node4, Node5);
    Node *Node1 = new Node(1, Node2, Node3);

    return Node1;
}


void flashPreOrder(Node *pTree){
    if(pTree == nullptr){
        return;
    }

    pTree->flash();
    flashPreOrder(pTree->m_pLeft);
    flashPreOrder(pTree->m_pRight);
}

void flashInOrder(Node *pTree){
    if(pTree == nullptr){
        return;
    }

    flashInOrder(pTree->m_pLeft);
    pTree->flash();
    flashInOrder(pTree->m_pRight);
}

void flashPostOrder(Node *pTree){
    if(pTree == nullptr){
        return;
    }

    flashPostOrder(pTree->m_pLeft);
    flashPostOrder(pTree->m_pRight);
    pTree->flash();
}


// Nedanstående funktion skall inte vara rekursiv.
// implementera den med hjälp av en FIFO-kö.
// Så här kan du deklarera fifo-kön:
// std::deque<Node*> que;
// så här stoppar du in ett värde i kön
// que.push_back( nodepekare );
// så här läser du det värde som ligger främst
// Node *p = que.front();
// så här avlägsnar du det främsta värdet från kön
// que.pop_front();

void flashNodesAtIncreasingDepth(Node *pTree){
    std::deque<Node*> que;

    que.push_back(pTree);

    while(!que.empty()){
        if(que.front()->m_pLeft != nullptr){
            que.push_back(que.front()->m_pLeft);
        }

        if(que.front()->m_pRight != nullptr){
            que.push_back(que.front()->m_pRight);
        }

        que.front()->flash();
        que.front()->makeRed();
        que.pop_front();
    }
}


// Nedanstående funktioner bör vara rekursiva.
// De kan då implementeras med några få raders kod.

int numberOfNodes(Node *pTree){
    if(pTree == nullptr){
        return 0;
    }

    return numberOfNodes(pTree->m_pLeft) + numberOfNodes(pTree->m_pRight) + 1;
}

int height(Node *pTree){
    int h1, h2;
    if(pTree == nullptr){
        return -1;
    } else {
        h1 = height(pTree->m_pLeft);
        h2 = height(pTree->m_pRight);
    }

    return (h1 > h2 ? h1 : h2) + 1;
}

void testfunktion1(Node *pTree){
    // frivilligt att skriva kod här
    qDebug() << "testfunktion1";
}

