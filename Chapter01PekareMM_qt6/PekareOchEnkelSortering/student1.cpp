#include "student1.h"
#include <cassert>
#include "ragnarstest1.h"
#include "dalgorandom.h"

#include <iostream>
using namespace std;


// Läs Detta!

// Pekaruppdragen går ut på att implementera nedastående funktioner
// Många funktioner skall implementeras på två olika sätt (I och P):
// Version I: Räkna ut size och använd arraynotation med hakparanteser och heltalsindex.
// Version P: Använd istället pekarnotation, dvs  *p,  p+=1,  etc.




// ************************************************************
// ANROP:   char* namn = nameOfStudent1();
// UPPGIFT: Returnerar ditt namn!
// ************************************************************
const char* nameOfTheStudent1(){
    return "Albin Forsberg";  // Byt ut denna sträng mot ditt eget namn!
}




// ################ version I, löses med [ ]  och indexnotation #############



// ************************************************************
// ANROP:   float value = minimumI(&arr[0], &arr[size]);
// UPPGIFT: Returnerar arrayens minsta värde
// ************************************************************
float minimumI(const float *pBegin, const float *pEnd){

    // Jag låter min egen lösnin ligga kvar.
    // Förstå denna! Lös de andra uppgifterna själv.

    assert( pBegin < pEnd );

    int size = pEnd - pBegin;
    float extreme = pBegin[0];
    for (int i=0; i<size ; i+=1)
        if (pBegin[i]<extreme)
            extreme = pBegin[i];
    return extreme;
}


// ************************************************************
// ANROP:   float value = maximumI( &arr[0], &arr[size] );
// UPPGIFT: Returnerar arrayens största värde
// ************************************************************
float maximumI(const float *pBegin, const float *pEnd){
    // TODO
    float max = pBegin[0];
    for(int i = 0; i < pEnd - pBegin; i++){
        if(pBegin[i] > max){
            max = pBegin[i];
        }
    }

    return max;
}


// ************************************************************
// ANROP:   float value = sumI( &arr[0], &arr[size] );
// UPPGIFT: Returnerar summan av alla element.
// ************************************************************
float sumI(const float *pBegin, const float *pEnd){
    float sum = 0;

    for(int i = 0; i < pEnd - pBegin; i++){
        sum += pBegin[i];
    }

    return sum;
}


// ************************************************************
// ANROP:   fillRandomI( &arr[0], &arr[size] );
// UPPGIFT: Fyller arrayen med oberoende slumpdata
// ************************************************************
void fillRandomI(float *pBegin, float *pEnd){
    // TODO

    for(int i = 0; i < pEnd - pBegin; i++){
        pBegin[i] = arc4random() % 10;
    }
}

// ************************************************************
// ANROP:   fillSortedRandomI( &arr[0], &arr[size] );
// UPPGIFT: Fyller arrayen med sorterat slumpdata. Minst först
// ************************************************************
void fillSortedRandomI(float *pBegin, float *pEnd){
    fillRandomI(pBegin, pEnd);
    sort(pBegin, pEnd);

}



// ************************************************************
// ANROP:   bool contains = hasValueInRangeI(min, max, &arr[0], &arr[size] );
// UPPGIFT: Returnerar true om arrayen ett värde i det halvt öppna intervallet min <= x < max.
// ************************************************************
bool  hasValueInRangeI(float min, float max, const float *pBegin, const float *pEnd){
    for(int i = 0; i < pEnd - pBegin; i++){
        if(pBegin[i] >= min && pBegin[i] < max){
            return true;
        }
    }

    return false;
}

// ************************************************************
// ANROP:   int number = numberOfValuesInRange(min, max,  &arr[0], &arr[size] );
// UPPGIFT: Returnerar antalet värden som ligger i det halvt öppna intervallet  min <= x < max.
// ************************************************************
int numberOfValuesInRangeI(float min, float max, const float *pBegin, const float *pEnd){
    int n = 0;

    for(int i = 0; i < pEnd - pBegin; i++){
        if(pBegin[i] >= min && pBegin[i] <= max){
            n++;
        }
    }

    return n;
}




// ################ version P, samma uppgifter löses nu med pekarnotation  ###############






float minimumP(const float *pBegin, const float *pEnd){
    // Jag låter min egen lösnin ligga kvar.
    // Förstå denna! Lös de andra uppgifterna själv.

    assert( pBegin < pEnd );
    float extreme = *pBegin;
    for (const float *p=pBegin ; p<pEnd; p+=1)
        if (*p<extreme)
            extreme = *p;
    return extreme;
}


float maximumP(const float *pBegin, const float *pEnd){
    float max = *pBegin;
    for(const float *p=pBegin; p<pEnd; p++){
        if(*p > max){
            max = *p;
        }
    }

    return max;
}

float sumP(const float *pBegin, const float *pEnd){
    float sum = 0;

    for(const float *p=pBegin; p<pEnd; p++){
        sum += *p;
    }

    return sum;
}

void fillRandomP(float *pBegin, float *pEnd){
    for(float *p=pBegin; p<pEnd; p++){
        *p = arc4random() % 10;
    }
}



void fillSortedRandomP(float *pBegin, float *pEnd){
    fillRandomP(pBegin, pEnd);
    sort(pBegin, pEnd);
}



bool hasValueInRangeP(float min, float max, const float *pBegin, const float *pEnd){
    for(const float *p = pBegin; p < pEnd; p++){
        if(*p >= min && *p < max){
            return true;
        }
    }

    return false;
}


int  numberOfValuesInRangeP(float min, float max, const float *pBegin, const float *pEnd){
    int n = 0;
    for(const float *p = pBegin; p < pEnd; p++){
        if(*p >= min && *p <= max){
            n++;
        }
    }
    return n;
}


// ################ Skriv din egen testkod här! #################

bool testSorted(float *pBegin, float *pEnd){
    for(int i = 1; i < pEnd - pBegin; i++){
        if(pBegin[i] < pBegin[i-1]){
            return false;
        }
    }

    return true;
}


void studentsTest1(){

    // Testa själv dina funktioner här!
    // Det är OBLIGATRORISKT att anropa varje funktion som du själv
    // implementeratrat,  så att labansvarig kan se att du förstått hur funktionerna skall
    // anropas!

    // Helst bör du också skriva kod som verifierar att dina funktioner
    // returnerar korrekta resultat för vissa exempeel på indata.
    // Istället för att skriva ut ett felmedelande på skärmen bör du se
    // till så att programmet kraschar om det innehåller ett fel!
    // Man kan göra detta genom att anropa:
    //   assert( false );
    // Men istället för att skriva:
    // if (!isOk) // om inte okay..
    //    assert( false );  // ..krascha programmet!
    // Bör man skriva:
    //   assert( isOk );
    // Ännu bättre... Istället för att skriva isOK kan man skriva ett uttryck som
    // blir true eller false, exempelvis (förutsatt att arr[0]==1 och arr[1]==2)
    //   assert( averageElementP(&arr[0],  &arr[2]) == 1.5 );



    cout << "(dina egna tester borde komma har!)\n";

    cout << "Testar min och max: ";

    float arr [] = {1,2,3,4,5};

    assert(minimumI(&arr[0], &arr[5]) == 1 && maximumI(&arr[0], &arr[5]) == 5 &&
           maximumP(&arr[0], &arr[5]) == 5 && minimumP(&arr[0], &arr[5]) == 1);

    std::cout << "Passed\n";
    std::cout << "Testing range: ";

    assert(hasValueInRangeI(3,5, &arr[0], &arr[5]) && numberOfValuesInRangeI(3,5, &arr[0], &arr[5]) == 3);
    assert(hasValueInRangeP(3,5, &arr[0], &arr[5]) && numberOfValuesInRangeP(3,5, &arr[0], &arr[5]) == 3);

    std::cout << "Passed!\n";

    std::cout << "Testing sum: ";

    assert(sumI(&arr[0], &arr[5]) == 15 && sumP(&arr[0], &arr[5]) == 15);

    std::cout << "Passed!\n";

    hasValueInRangeP(3,5, &arr[0], &arr[5]);

    std::cout << "Testar fillArrayRandom: ";

    fillRandomI(&arr[0], &arr[5]);
    fillRandomP(&arr[0], &arr[5]);

    std::cout << "Passed\n";

    std::cout << "Testart fillSorted: ";

    fillSortedRandomI(&arr[0], &arr[5]);

    assert(testSorted(&arr[0], &arr[5]));

    fillSortedRandomP(&arr[0], &arr[5]);

    assert(testSorted(&arr[0], &arr[5]));

    std::cout << "Passed!\n";
}




void mainFunctionInStudent1(){

    cout << "\n\n\n################ testingCode1 ################# \n\n";

    studentsTest1();


}


