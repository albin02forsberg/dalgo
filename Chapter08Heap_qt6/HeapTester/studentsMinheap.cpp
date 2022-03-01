#include "studentsMinheap.h"
#include "assert.h"



const char* nameOfStudent(){
    return "Homer Simpson";
}

MinHeap::MinHeap(int sizeOfArray)
    :m_sizeOfArray(sizeOfArray)
{    
    n_theArray = new int[m_sizeOfArray];
    m_size = 0;
}

MinHeap::~MinHeap(){
   // TODO
}

void MinHeap::insert(int data){
    // TODO

}


int MinHeap::min()
{
    // TODO
    return 0;// BUG
}


void MinHeap::deleteMin(){
    assert( !isEmpty() );
    // TODO

}


void MinHeap::percolateDown(int ix){
    // TODO
}

int MinHeap::size()
{
    return m_size;
}


// Fyller heapens array med data utan att organisera det i en heap-struktur.
// (detta gör man istället interaktiv)
void MinHeap::fillArrayWithData(int *newData, int size)
{
    assert( size<m_sizeOfArray);

    for (int i=1; i<=size ; i+=1)
        n_theArray[i] = newData[i];
    m_size = size;
}
