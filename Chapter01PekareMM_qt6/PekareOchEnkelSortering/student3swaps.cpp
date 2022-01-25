#include "student3swaps.h"
#include "dalgorandom.h"

#include <iostream>
using namespace std;

const char* nameOfTheStudent3(){
    return "Albin Forsberg";  // Byt ut denna sträng mot ditt eget namn!
}


// ################ Implementera swap med pekar- och referensanrop #################



// ANROP:   swap(a,b); eller swap( (&a), (&b) );
// UPPGIFT: Byter värden mellan a och b.
void swap(float* pA, float* pB){
    // TODO
    float temp = *pB;
    *pB = *pA;
    *pA = temp;

}

// ANROP:   swap(a,b); eller swap((a), (b));
// UPPGIFT: Byter värden mellan a och b.
void swap(float &a, float &b){
    float a0 = a;
    a = b;
    b = a0;
}

// För att öva på referenser ger jag här en
// lite annorluna implementerting av max.
float& max(float &a, float &b){
    if (a>b)
        return a;
    return b;
}



void testaMax(){
    float a = 42;
    float b = 108;

    cout << "maximum is " << max(a,b) << endl;

    max(a,b) = 1;

    cout << "a=" << a << " , b=" << b << endl;

    /* OBS! Förklara vad ovanstående max(a,b) = 1 gör, och varför!
     *
     * max kollar vilket det största värdet av a och b är, och retunerar detta talet.
     * I detta fallet är b störst, i och med att vi skriver max(a,b) = 1, kommer värdet
     * som retuneras bli 1. dvs a = 42, b = 1. Hade det varit a = 108 och b = 42,
     * hade a = 1 och b = 42.
     *
     */

}


void studentsTest3(){
  // TODO! Skriv din testkod här
  // Testa båda dina swap versioner

    float a = 5;
    float b = 9;
    float a0 = 5;
    float b0 = 9;

    std::cout << "Swap med pekare: \n";

    swap(&a, &b);

    assert(a == b0 && b == a0);

    std::cout << "Swap med referens: \n";

    a0 = 9;
    b0 = 5;

    swap(a, b);

    assert(a == b0 && b == a0);
}



void mainFunctionInStudent3(){

    cout << "\n\n\n################ testingCode3 #################\n\n";

    studentsTest3();
    testaMax();
}
