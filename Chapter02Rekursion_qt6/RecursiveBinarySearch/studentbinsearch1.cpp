#include "studentbinsearch1.h"

#include "ragnarstest.h"
#include <cassert>

#include <iostream>
using namespace std;


const char* nameOfStudent1(){
    return "Albin Forsberg";
}


/****************************************************************
ANROP:    bool exist = containedInSortedarray(x, pBegin, pEnd);
VERSION:  ...
UPPGIFT:  Returnerar true omm *p==x för något p i
          intervallet [pBegin, pEnd), dvs pBegin <= p < pEnd
          (observera att pEnd skall peka på första elementet efter arrayen)
OBS:      Alla tal mellan pBegin och pEnd måste vara sorterade i
          stigande ordning
*****************************************************************/
bool containedInSortedarray(int x, const int* pBegin, const int* pEnd){
    int size = pEnd - pBegin;
    int const *pMid = pBegin + (size/2);
//    std::cout << *pMid << std::endl;

    if(size <= 0){
        return false;
    }

    if(size == 1) {
        if(*pBegin == x){
            return true;
        }
        return false;
    }


    if(x < *pMid){
        return containedInSortedarray(x, pBegin , pMid);
    } else if (x > *pMid){
        return containedInSortedarray(x, pMid, pEnd);
    }

    return true;
}// contains




void studentsTest1(){

//    cout << "Har borde studentens testresultat synas" << endl << endl;

//   // TODO din egen testkod som anropar contains här

//    int arr[] = {1,2,3,4,5,6};


//    std::cout << "Testing binary search:\n";

//    for(int i = 0; i < 6; i++){
//        assert(containedInSortedarray(arr[i], &arr[0], &arr[6]));
//        std::cout << i << " exsists\n";
//    }

//    for(int i = 7; i < 13; i++){
//        assert(!containedInSortedarray(i, &arr[0], &arr[6]));
//        std::cout << i <<  " does not exsist\n";
//    }

//    int arr2[] = {1,3,5};

//    assert(!containedInSortedarray(5, &arr2[0], &arr2[1]));

//    assert(!containedInSortedarray(2, &arr2[0], &arr2[1]));

//    assert(!containedInSortedarray(5, &arr2[1], &arr2[1]));
//    assert(!containedInSortedarray(5, &arr2[1], &arr2[2]));
//    assert(containedInSortedarray(3, &arr2[1], &arr2[2]));

//    std::cout << "Passed!\n";

}
