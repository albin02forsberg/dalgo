#include "student5Sortings.h"
#include "student1.h"
#include "student3swaps.h"

#include "ragnarstest5.h"

#include <iostream>
using namespace std;

// Läs detta!
// Nedan finns version I och P av bubble- respektive insert-sort.

// Själv har jag implementerat bubbleSortI och insertSortP.
// Två algoritmer återstår!



// ************************************************************
// ANROP:   char* namn = nameOfStudent5();
// UPPGIFT: Returnerar ditt namn!
// ************************************************************
const char* nameOfTheStudent5(){
    return "Homer Simpson";  // Byt ut denna sträng mot ditt eget namn!
}



/**********************************************************************************
 * ANROP:   bubbleSortI( pBegin, pEnd);
 * UPPGIFT: pBegin och pEnd definierar en array av element (pBegin pekar på det
 *          första elementet och pEnd EFTER det sista).
 *          Funktionen sorterar arrayen så att det minsta elementet hamnar först.
 *
 *          Algoritmen bubbleSort beskrivs i uppdragshäftet!!
 *          Nedanstående I-version använder  heltalsindex och hakparanteser.
 * ********************************************************************************/
void bubbleSortI(float *pBegin, float *pEnd){
    long int size = pEnd - pBegin;
    for (long int maxIndex = size-1 ; maxIndex>0 ; maxIndex -= 1)
        for (int i=0 ; i<maxIndex ; i+=1)
            if (pBegin[i]>pBegin[i+1])
                swap( (pBegin[i]), (pBegin[i+1]));
}


/**********************************************************************************
 * ANROP:   insertSortP( pBegin, pEnd);
 * UPPGIFT: pBegin och pEnd definierar en array av element (pBegin pekar på det
 *          första elementet och pEnd EFTER det sista).
 *          Funktionen sorterar arrayen så att det minsta elementet hamnar först.
 *
 *          Algoritmen insertSort beskrivs i uppdragshäftet!!
 *          Nedanstående P-version använder varken heltalsindex eller hakparanteser.
 * ********************************************************************************/
void insertSortP(float *pBegin, float *pEnd){
    for (float *pLastInOrder=pBegin; pLastInOrder<pEnd-1 ; pLastInOrder+=1){
        float x = *(pLastInOrder+1);
        float *pValue = pLastInOrder;
        for (   ; pValue>=pBegin && *pValue>x ; pValue-=1)
            *(pValue+1) = *pValue;
        *(pValue+1) = x;
    }
}


// ++++++++++++++++++++++++++ studentkod här nedanför ++++++++++++++++++++++++++++++


/**********************************************************************************
 * ANROP:   bubbleSortP( pBegin, pEnd);
 * UPPGIFT: pBegin och pEnd definierar en array av element (pBegin pekar på det
 *          första elementet och pEnd EFTER det sista).
 *          Funktionen sorterar arrayen så att det minsta elementet hamnar först.
 *
 *          Algoritmen som används måste vara den version av bubbleSort som
 *          beskrivs i uppdragshäftet!! Se bubbleSortI ovan!
 *
 *          Syftet är bl.a. att träna på pekare.
 *          Man får varken använda heltalsindex eller hakparanteser.
 * ********************************************************************************/
void bubbleSortP(float *pBegin, float *pEnd){
    // TODO skall skrivas av studenten

}


/**********************************************************************************
 * ANROP:   insertSortI( pBegin, pEnd);
 * UPPGIFT: pBegin och pEnd definierar en array av element (pBegin pekar på det
 *          första elementet och pEnd EFTER det sista).
 *          Funktionen sorterar arrayen så att det minsta elementet hamnar först.
 *
 *          Algoritmen som används måste vara den version av insertSort som
 *          beskrivs i uppdragshäftet!! se insertSortP ovan!
 *
 *          Nedanstående version skall använda heltalsindex och hakparanteser.
 *
 * ********************************************************************************/
void insertSortI(float *pBegin, float *pEnd){
    // TODO skall skrivas av studenten

}




void studentsTest5(){

    // Testa själv bubble- och insert- sort här!
    cout << "Dina egna tester måste komma haer!\n";

    // TODO

}


void mainFunctionInStudent5(){

    cout << "\n\n\n################ testingCode5 #################\n\n";

    studentsTest5();


}
