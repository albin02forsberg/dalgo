#include "student1cstackl.h"
#include <assert.h>
#include <iostream>

using namespace std;

const char* nameOfStudent1(){
    return "Albin Forsberg";
}

CStackL  CStackLConstruct(){
   // Jag lämnar kvar denna implementering
    CStackL theStack;
    theStack.m_pTop = nullptr;
    theStack.m_size = 0;
    return theStack;
}

CStackL  CStackLConstruct(const CStackL &other){
    CStackL theStack;
    theStack.m_size = other.m_size; theStack.m_pTop = nullptr;
    Link *pPreviousLink = nullptr;
    for (const Link *pOthLnk= other.m_pTop; pOthLnk!=nullptr ; pOthLnk=(*pOthLnk).m_pNext) {
    Link *pCopy = new Link;
    (*pCopy).m_data = (*pOthLnk).m_data; (*pCopy).m_pNext = nullptr;
    if (pPreviousLink==nullptr)
    theStack.m_pTop = pCopy;
    else (*pPreviousLink).m_pNext = pCopy; pPreviousLink = pCopy;
    }
    return theStack;
}



void CStackLDestruct(CStackL *pDettaObjekt){
    while(pDettaObjekt->m_pTop != nullptr){
        CStackLPop(pDettaObjekt);
    }
}

void CStackLPush(CStackL *pDettaObjekt, float data){
    pDettaObjekt->m_size++;
    Link *pLink = new Link;
    Link *pOld = pDettaObjekt->m_pTop;
    pLink->m_pNext = pOld;
    pLink->m_data = data;
    pDettaObjekt->m_pTop = pLink;
}


float CStackLTop(CStackL *pDettaObjekt){
    std::cout << pDettaObjekt->m_pTop->m_data << " Size: " << pDettaObjekt->m_size << std::endl;
    return pDettaObjekt->m_pTop->m_data;
}


void CStackLPop(CStackL *pDettaObjekt){
    pDettaObjekt->m_size--;
    Link *pLink = pDettaObjekt->m_pTop->m_pNext;
    delete pDettaObjekt->m_pTop;
    pDettaObjekt->m_pTop = pLink;
}

int CStackLSize(CStackL *pDettaObjekt){
    return pDettaObjekt->m_size;
}

void printStack(CStackL *pStack){
    Link *current = pStack->m_pTop;
    while(current != nullptr){
        std::cout << current->m_data << " -> ";
        current = current->m_pNext;
    }
    std::cout << std::endl;
}

// ----- Din testkod

void studentTest1(){

     cout << endl << endl << "studentTest1..." << endl ;
    // Skriv din egen testkod här

     CStackL stack = CStackLConstruct();

     CStackLPush(&stack, 1);
     CStackLPush(&stack, 2);
     CStackLPush(&stack, 3);
     CStackLPush(&stack, 4.5);

     printStack(&stack);

     std::cout << std::endl;

     CStackL stack2 = CStackLConstruct(stack);
     //CStackLPop(&stack2);

     printStack(&stack2);


}

