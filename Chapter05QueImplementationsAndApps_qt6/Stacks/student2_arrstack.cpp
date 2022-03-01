#include "student2_arrstack.h"
#include <assert.h>
#include <iostream>

const char* nameOfStudentAStack(){
    return "Albin Forsberg";
}



AStack::AStack() {
    m_size = 0;
    m_capacity = 10;
    m_pArr = new float[m_capacity];

}

AStack::~AStack() {
    delete [] m_pArr;
}

void AStack::pushBack(float value) {
    if(m_size < m_capacity){
        m_pArr[m_size] = value;
        m_size++;
    } else {
        m_capacity *= 2;
        float *arr = new float[m_capacity];
        for(int i = 0; i < m_size; i++){
            arr[i] = m_pArr[i];
        }
        arr[m_size] = value;
        m_size++;
        m_pArr = arr;
    }
}


float &AStack::back() {
    return m_pArr[m_size-1];
}

void AStack::popBack(){
    m_size--;
}

int AStack::size() const
{
    return m_size;
}




void studentTest2(){
    AStack stack;

    for(int i = 0; i < 11; i++) {
        stack.pushBack(i);
    }

    std::cout << "Front: " << stack.back() << " size: " << stack.size() << std::endl;
}

/******** kommentar som efterfrågades i "öka istället linjärt"

  blev det någon skillnad när du ökade arraystorleken med 10 istället för med dubbleing?



 ***********************************************************************/
