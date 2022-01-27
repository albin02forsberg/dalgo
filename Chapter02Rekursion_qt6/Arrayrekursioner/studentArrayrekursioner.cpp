
#include "studentArrayrekursioner.h"
#include <cassert>
#include <iostream>
#include <random>

using namespace std;


std::string nameOfStudent(){
    return "Albin Forsberg";  // TODO andra till ditt namn!
}



float sum(const float *pBegin, const float *pEnd){
    if(pBegin == pEnd){
        return 0;
    }

    return (sum(pBegin + 1, pEnd) + *pBegin);
}


void fillValue(float value,  float *pBegin,  float *pEnd){
    if(pBegin != pEnd){
        *pBegin = value;
        fillValue(value, pBegin + 1, pEnd);
    }
}
bool hasValueInRange(float min, float max, const float *pBegin, const float *pEnd){
    if(*pBegin >= min && *pBegin < max){
        return true;
    }

    return (hasValueInRange(min, max, pBegin + 1, pEnd));
}

int numberOfValuesInRange(float min, float max, const float *pBegin, const float *pEnd){
    if(pBegin == pEnd){
        return 0;
    } else if (*pBegin >= min && *pBegin < max) {
        return numberOfValuesInRange(min, max, pBegin + 1, pEnd) + 1;
    }
    return numberOfValuesInRange(min, max, pBegin + 1, pEnd);
}



void studentTest(){
    std::cout << "Testing sum: ";

    float arr[] = {1,2,3,4};

    assert(sum(&arr[0], &arr[4]) == 10);

    std::cout << "Passed!\n";

    std::cout << "Testing valueInRange: ";

    assert(hasValueInRange(1, 3, &arr[0], &arr[4]));

    std::cout << "Passed!\n";

    std::cout << "Testing numbers of Values in range: ";

    assert(numberOfValuesInRange(1,3, &arr[0], &arr[4]) == 2);

    std::cout << "Passed!\n";

    std::cout << "Testing fillValue: ";

    fillValue(2, &arr[0], &arr[4]);

    for(int i = 0; i < 4; i++){
        assert(arr[i] == 2);
    }

    std::cout << "Passed!\n";
}


// ------------


