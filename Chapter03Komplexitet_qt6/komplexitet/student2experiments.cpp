#include "experiments.h"

#include "sortingalgorithms.h"

#include <QElapsedTimer>
#include "dalgorandom.h"
#include <algorithm>
#include <iostream>
using namespace std;



/***********************************************************************

 Resultat av experimenten:

 TODO


Fyll i körttid OCH komplexitet i nedanstående tabell

----------------------------------------------------------------
            |     ordnat   |   nästan ordnat |   slumpmässigt  |
----------------------------------------------------------------
bubbleSort  |       O(   ) |        O(   )   |          O(  )  |
----------------------------------------------------------------
insertSort  |      O(   ) |        O(   )   |          O(  )  |
----------------------------------------------------------------

TODO fyll också i nedanstående!

körtiden för insertSort (slumpmässig) skattas med t(n) = c*n^2
där c = ...

Tiden att sortera sortera 10 miljoner tal borde då bli

= ...  sekunder, dvs .... timmar.

Med std::sort tog det ....  att sortera 10 miljoner tal.



************************************************************************/

void fillWithRandom(float *pBegin, float *pEnd){
    for(float *pI = pBegin; pI != pEnd; pI++ ){
        *pI = dalgoRandom() * 10;
    }
}

void fillWithRandomSorted(float *pBegin, float *pEnd){
    for(float *pI = pBegin; pI != pEnd; pI++ ){
        *pI = dalgoRandom() * 10;
    }

    sort(pBegin, pEnd);
}

void fillWithRandomAlmostSorted(float *pBegin, float *pEnd){
    fillWithRandomSorted(pBegin, pEnd);
}


void printArray(float *pBegin, float *pEnd){
    for(float *pI = pBegin; pI != pEnd; pI++ ){
        std::cout << *pI << " ";
    }
    std::cout << std::endl;
}

void testBubble(float *pBegin, float *pEnd){
    std::cout << "Testing bubblesort: \n";
    std::cout << "Sort random: ";
    QElapsedTimer timer;

    fillWithRandom(pBegin, pEnd);

    timer.start();

    bubbleSortI(pBegin, pEnd);

    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random almost sorted: ";

    fillWithRandomAlmostSorted(pBegin, pEnd);

    timer.start();

    bubbleSortI(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random sorted: ";

    fillWithRandomSorted(pBegin, pEnd);

    timer.start();

    bubbleSortI(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";
}

void testInsert(float *pBegin, float *pEnd){
    std::cout << "Testing Insert: \n";
    std::cout << "Sort random: ";
    QElapsedTimer timer;

    fillWithRandom(pBegin, pEnd);

    timer.start();

    insertSortP(pBegin, pEnd);

    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random almost sorted: ";

    fillWithRandomAlmostSorted(pBegin, pEnd);

    timer.start();

    insertSortP(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random sorted: ";

    fillWithRandomSorted(pBegin, pEnd);

    timer.start();

    insertSortP(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";
}

void testStdSort(float *pBegin, float *pEnd){
    std::cout << "Testing std::sort: \n";
    std::cout << "Sort random: ";
    QElapsedTimer timer;

    fillWithRandom(pBegin, pEnd);

    timer.start();

    std::sort(pBegin, pEnd);

    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random almost sorted: ";

    fillWithRandomAlmostSorted(pBegin, pEnd);

    timer.start();

    std::sort(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";

    std::cout << "Sort random sorted: ";

    fillWithRandomSorted(pBegin, pEnd);

    timer.start();

    std::sort(pBegin, pEnd);
    std::cout << timer.elapsed() / 1000 << " seconds\n";
}


void sixExperiments(){
    int size = 1000000;
    cout << endl << endl << "sixExperiments()" << endl ;

    float arr[size];

    std::cout << "Testing with array of size: " << size << std::endl;

//    testBubble(&arr[0], &arr[size]) ;
    testInsert(&arr[0], &arr[size]);
    testStdSort(&arr[0], &arr[size]);

    cout << endl << "sixExperiments()" << endl;
}


void stdSortExperiment(){
    cout << endl << endl << "stdSortExperiment()" << endl;



}

const char* nameOfStudent2(){
    return "Albin Forsberg"; // ändra till ditt namn
}

