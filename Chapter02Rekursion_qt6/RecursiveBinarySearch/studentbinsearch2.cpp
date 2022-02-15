#include "studentbinsearch2.h"

#include <iostream>

using namespace std;


const char* nameOfStudent2(){
    return "Albin Forsberg";
}


// Returnerar pekare till det första tal som är >= x, eller
// pEnd om inget sådant tal finns.
const float* pointerToFirstElementGreaterOrEqualToX(float x, const float* pBegin, const float* pEnd){
    // TODO denna implementering är felaktig

    int size = pEnd - pBegin;
    float const *pMid = pBegin + (size/2);

    if(size <= 0){
        return pEnd;
    }

    if(size == 1){
        if(*pMid == x){
            return pMid;
        }
        return pEnd;
    }

    if(*pMid < x){
        pointerToFirstElementGreaterOrEqualToX(x, pMid, pEnd );
    } else if(*pMid >= x){
        pointerToFirstElementGreaterOrEqualToX(x, pBegin, pMid) ;
    }

    return pMid;
}


void studentsTest2(){

   cout << "Har borde studentens testresultat synas\n\n";

   float arr[] = {1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.9};

   float x = 1.3;
   float y = *pointerToFirstElementGreaterOrEqualToX(x, &arr[0], &arr[6]);

   std::cout << "Search: " << x << std::endl;
   std::cout << "Found: " << y << std::endl;
//   std::cout << y << std::endl;


   // TODO din egen testkod som anropar contains här
}
