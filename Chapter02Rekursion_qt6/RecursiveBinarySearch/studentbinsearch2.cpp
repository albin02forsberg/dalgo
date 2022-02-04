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

    const float *pMid = pBegin - (size/2);

//    for(float *i = pBegin; i < pMid; i++){
//        if()
//    }

}


void studentsTest2(){

   cout << "Har borde studentens testresultat synas\n\n";

   // TODO din egen testkod som anropar contains här
}
