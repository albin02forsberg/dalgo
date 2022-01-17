#include "ragnarstest1.h"
#include "student1.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <QThread>
#include <assert.h>
#include <math.h>



using namespace std;

float absolute(float x){
    return x<0 ? -x : x;
}


bool okName1(){
    // Ändra INTE denna funktion !!!!
    // Ändra istället nameOfTheStudent1 ! (se anvisningarna i kap 0)

    string name = nameOfTheStudent1();

    if (name=="Homer Simpson"){
        cout << "nameOfStudent1() returnerar inte DITT namn!" << endl;
        assert(false);
    }
    return true;
}


// Sätter alla element till nan (not a number)
void prepareArray(float *arr, int size){
    for (int i=0; i<size;  i+=1 )
        arr[i] = nanf("");
}

// Verifierar att första och sista elementet är nan, och att alla andra är icke-nan.
void assertArr(float *arr, int size){
    assert( isnan( arr[0] ) && isnan(arr[size-1] ));
    for (int i=1; i<size-1 ; i+=1)
        assert( !isnan(arr[i]) );
}



void assertApproximation(float value, float approximation){
    float diff = value - approximation;
    float epsilon = 0.01f;
    assert( -epsilon < diff && diff < epsilon );
}

typedef void(*FuncVoidFromPP)(float* pBegin,  float* pEnd);
typedef float(*FuncFloatFromPP)(const float* pBegin,  const float* pEnd);
typedef bool(*FuncBoolFromFPP)(float x, const float* pBegin,  const float* pEnd);
typedef bool(*FuncBoolFromFFPP)(float min, float max, const float* pBegin,  const float* pEnd);
typedef int(*FuncIntFromFPP)(float x, const float* pBegin,  const float* pEnd);
typedef int(*FuncIntFromFFPP)(float min, float max, const float* pBegin,  const float* pEnd);


void testaFill( FuncVoidFromPP fillWithRandom){
    const int size = 100;
    float arr[size];

    float *pBegin = &arr[1];
    float *pEnd   = &arr[size-1];

    prepareArray(arr, size);
    fillWithRandom(pBegin, pEnd);
    assertArr(arr, size);
}


void testaFillSorted( FuncVoidFromPP fillWithRandomSorted){
    const int size = 100;
    float arr[size];

    float *pBegin = &arr[1];
    float *pEnd   = &arr[size-1];

    prepareArray(arr, size);
    fillWithRandomSorted(pBegin, pEnd);
    assertArr(arr, size);

    for (float* p=pBegin+1 ; p!=pEnd; p+=1)
        assert( *p>=*(p-1));

}

void testa( FuncFloatFromPP  minimumElement,
            FuncFloatFromPP  maximumElement,
            FuncFloatFromPP  sumOfElements,
            FuncBoolFromFFPP   hasValueInRange,
            FuncIntFromFFPP  numberOfValuesInRange){

    float data1[5] = {nanf(""), 6.0f, 2.3f, 15.4f, nanf("")};
    float data2[5] = {nanf(""), -6.0f, -2.3f, -15.4f, nanf("")};
    float data3[5] = {nanf(""), 6.0f, 2.3f, 6.0f, nanf("")};

    assertApproximation( minimumElement(&data1[1], &data1[4]) , 2.3f);
    assertApproximation( minimumElement(&data2[1], &data2[4]) , -15.4f);

    assertApproximation( maximumElement(&data1[1], &data1[4]) , 15.4f);
    assertApproximation( maximumElement(&data2[1], &data2[4]) , -2.3f);

    assertApproximation(sumOfElements(&data1[1], &data1[4]) , float(6.0+2.3+15.4));


    const float delta = 0.01;
    for (int i=1; i<4 ; i+=1){
        assert( hasValueInRange(data1[i]-delta,data1[i]+delta, &data1[1], &data1[4]) );
        assert( !hasValueInRange(data1[i]-delta,data1[i]+0, &data1[1], &data1[4]) );

    }

    assert( numberOfValuesInRange(6.0f-delta,6.0f+delta, &data3[1],&data3[4]) == 2 );
}

void printCheck(int i){
    cout << "test " << i << endl;
    QThread::msleep(500);

}

bool testIandP(){
    int testNumber = 0;

    printCheck(testNumber++);
    testaFill( fillRandomI );

    printCheck(testNumber++);
    testa(minimumI, maximumI,sumI,hasValueInRangeI, numberOfValuesInRangeI);

    printCheck(testNumber++);
    testaFillSorted( fillSortedRandomI);

    printCheck(testNumber++);
    testaFill( fillRandomP );

    printCheck(testNumber++);
    testa(minimumP, maximumP,sumP,hasValueInRangeP, numberOfValuesInRangeP);

    printCheck(testNumber++);
    testaFillSorted( fillSortedRandomP);

    printCheck(testNumber++);


    return true;
}


bool ragnarsTest1(){

   cout << "Hej " << nameOfTheStudent1() << ", nu kör vi Ragnars test 1." << endl;
   cout << "Om testen lyckas kommer ett meddelande som anger detta att skrivas ut," << endl;
   cout << "annars har du en bug" << endl;



   QThread::msleep(100);
   bool ok = okName1()
           && testIandP();

   cout << "Grattis, Ragnars test 1 lyckades! " << endl;
   return ok;
}
