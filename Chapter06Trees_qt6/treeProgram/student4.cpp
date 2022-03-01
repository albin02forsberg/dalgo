
#include "node.h"
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <QDebug>
#include <iostream>

#include "students.h"


const char* nameOfStudent4(){
    return "Albin Forsberg";
}

/**************************************************************************
 * Fler uppgifter.
 **************************************************************************/

bool hasPathToTarget(Node *pTree){
    if(pTree == nullptr){
        return false;
    }

    pTree->flash();

    if(pTree->isTarget()){
        pTree->makeRed();
        return true;
    }


    if(hasPathToTarget(pTree->m_pLeft)){
        pTree->makeRed();
        return true;
    }
    if(hasPathToTarget(pTree->m_pRight)){
        pTree->makeRed();
        return true;
    }


    return false;
}


bool didFind500(Node *pTree){
    // Detta är ingen uppgift!
  return true;
}

void testfunktion4(Node *pTree){
    qDebug() << "testfunktion4";

    // frivilligt att skriva kod här

}





