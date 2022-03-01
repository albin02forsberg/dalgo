

#include "node.h"
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <QDebug>
#include "students.h"


const char* nameOfStudent2(){
    return "Albin Forsberg";
}

/**************************************************************************
 * Sökträd.
 *
 *
 **************************************************************************/

void insertKeyToSearchtree(Node*& pTree, int key){
    if(pTree == nullptr){
        pTree = new Node(key, nullptr, nullptr);
    }

    Node *pCurrent = pTree;
    Node *pNode;

    while(pCurrent != nullptr){
        pNode = pCurrent;

        if(pCurrent->m_key == key){
            return;
        }

        if(pCurrent->m_key < key){
            pCurrent = pCurrent->m_pRight;
        } else {
            pCurrent = pCurrent->m_pLeft;
        }
        pCurrent->flash();
    }

    Node *newNode = new Node(key, nullptr,nullptr);
    if(key < pNode->m_key){
        pNode->m_pLeft = newNode;
    } else {
        pNode->m_pRight = newNode;
    }

}

bool contains(Node *pTree, int key){
    if(pTree == nullptr){
        return false;
    }

    Node *pCurrent = pTree;

    while(pCurrent != nullptr){
        pCurrent->flash();
        if(pCurrent->m_key == key) {
            pCurrent->makeRed();
            return true;
        } else if(key < pCurrent->m_key){
            pCurrent = pCurrent->m_pLeft;
        } else {
            pCurrent = pCurrent->m_pRight;
        }
    }

    return false;
}


Node* nodeWithMinimumKey(Node *pTree){
    Node *pCurrent = pTree;

    while(pCurrent->m_pLeft != nullptr){
        pCurrent = pCurrent->m_pLeft;
        pCurrent->flash();
    }
    pCurrent->makeRed();

    return pCurrent;
}

void removeKeyFromSearchtree(Node* &pTree, int key){
    Node *pCurrent = pTree;
    Node *pParent = pCurrent;

    while(pCurrent != nullptr) {
        pCurrent->flash();

        // Stepping left or right in tree depending och
        // size of key

        if(key < pCurrent->m_key){
            pParent = pCurrent;
            pCurrent = pCurrent->m_pLeft;
        } else if(key > pCurrent->m_key){
            pParent = pCurrent;
            pCurrent = pCurrent->m_pRight;
        } else {
            // If both children are nullptr
            if(pCurrent->m_pLeft == nullptr && pCurrent->m_pRight == nullptr){

                if(pCurrent != pTree){
                    if(pParent->m_pLeft == pCurrent) {
                        pParent->m_pLeft = nullptr;
                    } else {
                        pParent->m_pRight = nullptr;
                    }
                } else {
                    pTree = nullptr;
                }

                delete pCurrent;

            } else if(pCurrent->m_pLeft == nullptr || pCurrent->m_pRight == nullptr){
                // Parent got one child

                Node *pChild = (pCurrent->m_pLeft)? pCurrent->m_pLeft: pCurrent->m_pRight;

                if(pCurrent != pTree){
                    if(pCurrent == pParent->m_pLeft){
                        pParent->m_pLeft = pChild;
                    } else {
                        pParent->m_pRight = pChild;
                    }
                    delete pCurrent;
                } else {
                    pCurrent = pChild;
                }


            } else if (pCurrent->m_pLeft && pCurrent->m_pRight){
                // If parent got two children

                Node *pSuc = nodeWithMinimumKey(pCurrent->m_pRight);
                int value = pSuc->m_key;

                removeKeyFromSearchtree(pTree, pSuc->m_key);

                pCurrent->m_key = value;
            } else {
                return;
            }
        }
    }

}

/*** redogörelse för experiment ***************************************

  Hur stort blir trädets höjd respektive genomsnittliga
   djup om man stoppar in 255 element (gör flera experiment om det går)?


  TODO...

  höjd = ..

  genomsnittligt djup = ...

  (gör flera experiment)

   OBS på Windowsmaskiner kan det vara svårt att utföra flera olika experiment.


  varför är det genomsnittliga djupet intressant? ...


 ******************************************************************************/



void testfunktion2(Node *pTree){
    qDebug() << "testfunktion2";

    // frivilligt att skriva kod här
}
