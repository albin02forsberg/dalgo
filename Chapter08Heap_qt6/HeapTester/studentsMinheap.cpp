#include "studentsMinheap.h"
#include "assert.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>



const char* nameOfStudent(){
    return "Albin Forsberg";
}

MinHeap::MinHeap(int sizeOfArray)
    :m_sizeOfArray(sizeOfArray)
{    
    n_theArray = new int[m_sizeOfArray];
    m_size = 0;
}

MinHeap::~MinHeap(){
    delete [] n_theArray;
}

void MinHeap::insert(int data){
    if (m_size == m_sizeOfArray){
           return;
       }

       m_size++;
       int i = m_size;
       n_theArray[i] = data;

        // If the parent is bigger than the child, switch child
        // and parent. Continue upwards.
       while (i != 0 && n_theArray[i / 2] > n_theArray[i])
       {
          std::swap(n_theArray[i], n_theArray[i / 2]);
          i = i / 2;
       }

}


int MinHeap::min()
{
    return n_theArray[1];
}


void MinHeap::deleteMin(){
    assert(!isEmpty());
    n_theArray[1] = n_theArray[m_size];
    m_size--;
    percolateDown(1);
}


void MinHeap::percolateDown(int ix){
    int value = n_theArray[ix];

    while(ix*2 <= m_size){
        int child = ix*2;

        // Checks if the left child is bigger than the right child
        // if it is, continue on right child.

        if(child != m_size && n_theArray[child + 1] < n_theArray[child]){
            child++;
        }

        if(n_theArray[child] >= value){
            break;
        }

        n_theArray[ix] = n_theArray[child];
        ix = child;
    }
    n_theArray[ix] = value;
}

int MinHeap::size(){
    return m_size;
}


// Fyller heapens array med data utan att organisera det i en heap-struktur.
// (detta gör man istället interaktiv)
void MinHeap::fillArrayWithData(int *newData, int size){
    assert( size<m_sizeOfArray);

    for (int i=1; i<=size ; i+=1)
        n_theArray[i] = newData[i];
    m_size = size;
}
