// studentsFile.cpp

#include "towers.h"
#include "studentsTreTorn1.h"
#include <iostream>

extern Towers TOWERS;

const char* nameOfStudent(){
    return "Albin Forsberg";
}


// Returnerar den 3:e pinnen som varken är pinFrom eller pinTo
int otherPin(int pinFrom, int pinTo){
    return 0+1+2 - pinFrom - pinTo;
}


void moveDiscs(int numberOfDiscs, int pinFrom, int pinTo){
    // 1 > 3 - 2
    // 1 > 2 - 3
    // 3 > 2 - 1
    // 1 > 3 - 2
    // 2 > 1 - 3
    // 2 > 3 - 1
    // 1 > 3 - 2
    // 1 > 2 - 3

    if(otherPin(pinFrom, pinTo) == 0){
        moveDiscs(numberOfDiscs,0,2);
    } else {
        moveDiscs(numberOfDiscs, 2,1);
    }

    return;
}


