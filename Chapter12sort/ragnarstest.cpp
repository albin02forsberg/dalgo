#include "ragnarstest.h"

#include "student1mergesort.h"
#include "student2heapsort.h"

#include <string>
#include <iostream>
#include <QThread>
#include <QElapsedTimer>

#include "assert.h"

using namespace std;

typedef void(*sortFunction)(float* pBegin,  float* pEnd);



/**************************************************************
ANROP:     doTheSwap((a),(b));
VERSION:   2005-10-05 NORA
UPPGIFT:   Byter a mot b.
**************************************************************/
static void doTheSwap(float &a, float &b)
{
    float tmp = a;
    a = b;
    b = tmp;
}// doTheSwap



// Testar om angiven sorteringsalgoritm fungerar.
// Felutskrift om så inte är fallet.
// Returnerar true omm ok.
bool testAlgorithm(sortFunction simpleSort, string name){

    cout << "testar " << name <<endl;
    QThread::msleep(100);

    const int size = 128;
    // skapa en sekvens (seq) av slumptal sorterad i stigande ordn.
    float seq[size];
    seq[0] = -10; // size;
    for (int i = 1; i<size; ++i)
    {
        float d = (float)rand() / RAND_MAX;
        seq[i] = seq[i - 1] + d; // - d;
    }

    // låt mixed innehålla samma tal men i slumpordning
    // pÂ varje sida utanför arrayen ligger det en 1a, som
    // ej får ändras av sorteringsalgoritmenn

    float mixedExtraLarge[size + 2];
    float *mixed = &mixedExtraLarge[1]; // -1...size
    for (int i = 0; i<size; ++i)
        mixed[i] = seq[i];
    for (int i = 0; i<size; ++i)
        doTheSwap((mixed[i]), (mixed[rand() % size]));
    mixed[-1] = 1;
    mixed[size] = 1;
    // testa att simpleSort fungerar
    simpleSort( &mixed[0], &mixed[size]);

    bool ok = true;
    if (mixed[-1] != 1 || mixed[size] != 1){
        cout << "BUG: Algoritmen " << name << " skriver utanför (array)minnet!\7\n";
        ok = false;
    }

    if (ok)
        for (int i = 0; i<size; ++i)
            if (mixed[i] != seq[i])
            {
                cout << "BUG: i algoritm " << name <<  " mixed[" << i << "]==" << mixed[i] <<" != " << seq[i] << endl;
                ok = false;
            }

    return ok;

}


void thrillPrint(string str){

    cout << str;
//    for (int i=0; i<str.size(); i+=1){
//        cout << str[i];
//        cout.flush();
//        QThread::msleep(20);
//    }
}




bool testStart( const char *testName, const char *studentName ){

    cout << endl << endl;
    cout << "------------------------------------------\n";
    string str = string("Testing ") + testName + " for Student " + studentName + "\n";
    thrillPrint(str);


    assert( string("Homer Simpson") != studentName );

    return true;
}

bool testStop( const char *testName, bool success ){

    QThread::msleep(500);
    cout << endl << testName << " " << (success? "Lyckades" : "MISSLYCKADES\7") << endl;
    cout << "------------------------------------------\n";
    return success;
}



void timeSort(sortFunction sortFunc, string nameOfSortfunction ){

    int size = 8*1024*1024;
    float *arr = new float [size];
    for (int i=0;i<size ; i+=1)
        arr[i] = rand();
    for (int i=0;i<size ; i+=1)
        arr[i] +=  float( rand() / 1000.0 );

    cout << endl
         << endl
         << "time to sort " << size << " floats with " << nameOfSortfunction << "..." << endl;


    QElapsedTimer myTimer;
    myTimer.start();

    sortFunc(&arr[0], &arr[size]);

    cout << "The time was " << myTimer.elapsed() << " ms" << endl;

}


void stdsort(float* pBegin, float*pEnd){
    std::sort(pBegin, pEnd);
}


void ragnarsTest(bool  testHeapsort, bool testMergesort){

    cout << endl
         << endl
         << "Andra i main vilka sorteringsalgoritmer du har implementerat!"
         << endl
         << endl;

    bool okSort = true;
    bool okHeap = false;
    bool oKMerge = false;

    if (testHeapsort){
        testStart("heapsort", nameOfStudentHeapsort() );

        okHeap = testAlgorithm(heapsort, "heapsort");

        if (okHeap)
            cout << "(heapsort lyckades!)" << endl;
        else cout << "heapsort misslyckades\7" << endl << endl;
        testStop("heapsort", okHeap);
    }
    else cout << "heapsort kommer ej att testas (andra detta i main)" << endl;



    if (testMergesort){
        testStart("testMergesort", nameOfStudentMergesort() );

        oKMerge = testAlgorithm(mergesort, "mergesort");

        if (oKMerge)
            cout << "(mergesort lyckades!)" << endl;
        else cout << "mergesort misslyckades\7" << endl << endl;
        testStop("mergesort", oKMerge);
    }
    else cout << "mergesort kommer ej att testas (andra detta i main)" << endl;


    if (okSort)
        timeSort(stdsort, "std::sort");

    if (okHeap)
        timeSort(heapsort, "heapsort");
    if (oKMerge)
        timeSort(mergesort, "mergesort");


}
