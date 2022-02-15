#include "student2stackl.h"
#include <assert.h>
#include <iostream>

using namespace std;

const char* nameOfStudent2(){
    return "Albin Forsberg";
}

StackL::StackL(){
    m_pTop = nullptr;
    m_size = 0;
}


StackL::StackL(const StackL& theOther){
    m_size = theOther.m_size;

    Link *pPreviousLink = nullptr;
    for (const Link *pOthLnk= theOther.m_pTop; pOthLnk!=nullptr ; pOthLnk=(*pOthLnk).m_pNext) {
        Link *pCopy = new Link;
        (*pCopy).m_data = (*pOthLnk).m_data; (*pCopy).m_pNext = nullptr;
        if (pPreviousLink==nullptr)
            m_pTop = pCopy;
        else (*pPreviousLink).m_pNext = pCopy; pPreviousLink = pCopy;
    }
}

StackL::~StackL(){
    while(m_pTop != nullptr){
        this->pop();
    }
}

void StackL::push(float value){
    m_size++;
    Link *pLink = new Link;
    Link *pOld = m_pTop;
    pLink->m_pNext = pOld;
    pLink->m_data = value;
    m_pTop = pLink;
}

void StackL::pop(){
    Link *pOld = m_pTop;
    m_pTop = pOld->m_pNext;
    m_size--;
    delete pOld;
}


float StackL::top() const {
    return m_pTop->m_data;
}

int StackL::size() const {
    return m_size;
}

void StackL::print(){
    Link *pCurrent = m_pTop;
    while(pCurrent != nullptr) {
        std::cout << pCurrent->m_data << " ";
        pCurrent = pCurrent->m_pNext;
    }

    std::cout << std::endl;
}


void studentTest2(){

     cout << endl << endl <<  "studentTest2..." << endl;

     StackL stack;

     stack.push(1);
     stack.push(2);
     stack.push(3);
     stack.push(4);
     stack.pop();
     assert(stack.size()==3);
     stack.print();

     std::cout << "Size: " << stack.size() << " Data top: " << stack.top() << std::endl;

     StackL stack2 = stack;
     std::cout << "Stack 2 skapad\n";
     assert(stack2.size() == 3);

    // Skriv din egen testkod här
}

