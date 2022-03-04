#include "student3_listque.h"
#include "assert.h"
#include <iostream>


const char* nameOfStudentLQue(){
    return "Albin Forsberg";
}



LQue::LQue() {
    m_pFront = nullptr;
    m_pBack = nullptr;
    m_size = 0;
}

LQue::~LQue() {
    while(m_pFront != nullptr){
        popFront();
    }
}

void LQue::pushBack(float value) {
    Link *pLink = new Link();
    pLink->m_value = value;

    if(m_size == 0){
        m_pFront = pLink;
        m_pBack = pLink;
    }

    m_pBack->m_pNext = pLink;
    m_pBack = m_pBack->m_pNext;
    m_size++;
}

float &LQue::back() {
    assert( m_size>0 );
    return m_pBack->m_value;

}

void LQue::popFront() {
     assert( m_size>0 );
     m_size--;

     Link *pLink = m_pFront->m_pNext;
     delete m_pFront;
     m_pFront = pLink;
}

float &LQue::front() {
    assert( m_size> 0);
    return m_pFront->m_value;
}

int LQue::size() const {
    return m_size;
}

void LQue::print() {
    Link *pCurrent = m_pFront->m_pNext;

    std::cout << "Que size: " << m_size << std::endl;

    while(pCurrent != m_pBack){
        std::cout << pCurrent->m_value << " " ;
        pCurrent = pCurrent->m_pNext;
    }
    std::cout << std::endl;
}
