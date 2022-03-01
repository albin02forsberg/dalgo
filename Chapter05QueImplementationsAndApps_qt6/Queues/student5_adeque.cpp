#include "student5_adeque.h"
#include <iostream>


const char* nameOfStudentADeque(){
    return "Albin Forsberg";
}



ADeque::ADeque() {
    m_capacity = 10;
    m_indexOfBack = 0;
    m_indexOfFront = 0;
    m_size = 0;
    m_pArr = new float[m_capacity];
}

ADeque::~ADeque() {
    delete [] m_pArr;
}

void ADeque::pushBack(float value) {
    m_size++;
    if(m_size > m_capacity){
        m_capacity *= 2;
        float *arr = new float[m_capacity];

        for(int i = 0; i < m_size; i++){
            arr[i] = m_pArr[i];
        }

        delete [] m_pArr;
        m_pArr = arr;
    }

    m_indexOfBack = (m_indexOfFront + m_size) % m_capacity;
    m_pArr[m_indexOfBack] = value;
}

void ADeque::pushFront(float value) {
    if(m_size > m_capacity){
        m_capacity *= 2;
        float *arr = new float[m_capacity];

        for(int i = m_size; i > m_indexOfFront; i--){
            arr[i+1] =m_pArr[i];
        }

        delete [] m_pArr;
        m_pArr = arr;
    }

//    for(int i = 0; i > m_size; i--){
//       m_pArr[i+1] = m_pArr[i];
//    }

    m_indexOfFront = (m_indexOfBack + m_size) % m_capacity;
    m_pArr[m_indexOfFront] = value;
    m_size++;
}

void ADeque::popBack() {
    m_indexOfBack--;
    if(m_indexOfBack <= 0){
        m_indexOfFront = m_capacity;
    }

    m_size--;
}

void ADeque::popFront() {
    m_indexOfFront++;
    if(m_indexOfFront == m_capacity){
        m_indexOfFront = 0;
    }

    m_size--;
}

float &ADeque::back() {
    return m_pArr[m_indexOfBack];
    int m_indexOfBack = (m_indexOfFront + m_size) % m_capacity;

    if(m_indexOfBack == 0){
        m_indexOfBack = (m_indexOfFront + m_size-1) % m_capacity;
        return m_pArr[m_indexOfBack];
    }
    return m_pArr[m_indexOfBack-1];
}

float &ADeque::front() {
    return m_pArr[m_indexOfFront];
}

int ADeque::size() const {
    return m_size;
}

void ADeque::print(){
    for(int i = m_indexOfFront-1; i <= m_indexOfBack; i++){
        std::cout << m_pArr[i] << " ";
    }
    std::cout << std::endl;
}


