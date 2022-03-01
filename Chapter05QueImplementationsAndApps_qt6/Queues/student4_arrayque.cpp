#include "student4_arrayque.h"
#include "assert.h"
#include <iostream>

const char* nameOfStudentAQue(){
    return "Albin Forsberg";
}



AQue::AQue() {
    m_capacity = 10;
    m_pArr = new float[m_capacity];
    m_size = 0;
    m_indexOfFront = 0;
}

AQue::~AQue() {
    delete [] m_pArr;
}


void AQue::pushBack(float value) {
    int back = (m_indexOfFront + m_size) % m_capacity;
    m_pArr[back] = value;
    m_size++;
}

float &AQue::back() {
    int back = (m_indexOfFront + m_size) % m_capacity;

    if(back == 0){
        back = (m_indexOfFront + m_size-1) % m_capacity;
        return m_pArr[back];
    }
    return m_pArr[back-1];
}

void AQue::popFront() {
    m_indexOfFront++;
    if(m_indexOfFront == m_capacity){
        m_indexOfFront = 0;
    }

    m_size--;
}

float &AQue::front() {
    return m_pArr[m_indexOfFront];
}


int AQue::size() const {
    return m_size;
}

