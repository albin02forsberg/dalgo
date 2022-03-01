// Copyright (c) by Ragnar Nohre
#ifndef STUDENT1_H
#define STUDENT1_H


#include "node.h"
#include <fstream>

const char* nameOfStudent1();
const char* nameOfStudent2();
const char* nameOfStudent3();
const char* nameOfStudent4();

void testfunktion1(Node *pTree);
void testfunktion2(Node *pTree);
void testfunktion3(Node *pTree);
void testfunktion4(Node *pTree);



/**************************************************************************
 * Trädklättring.
 **************************************************************************/
Node* testTree1();

void flashPreOrder(Node *pTree);
void flashInOrder(Node *pTree);
void flashPostOrder(Node *pTree);

void flashNodesAtIncreasingDepth(Node *pTree);

int numberOfNodes(Node *pTree);
int height(Node *pTree);


/**************************************************************************
 * Sökträd.
 **************************************************************************/

void insertKeyToSearchtree(Node* &pTree, int key);
bool contains(Node *pTree, int key);
void removeKeyFromSearchtree(Node* &pTree, int key);



/**************************************************************************
 * Serialisering.
 **************************************************************************/
void saveTreeToStream(std::ofstream& utfil, Node *pTree);
Node* readTreeFromStream(std::ifstream& infil);




/**************************************************************************
 * Fler uppgifter.
 **************************************************************************/
bool hasPathToTarget(Node *pTree);




#endif // STUDENT1_H
