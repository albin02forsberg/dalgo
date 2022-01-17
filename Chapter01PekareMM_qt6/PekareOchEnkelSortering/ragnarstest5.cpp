#include "ragnarstest5.h"
#include "student5Sortings.h"

#include <QThread>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;



typedef void(*FuncSorterare)(float* pBegin,  float* pEnd);






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
bool testAlgorithm(FuncSorterare simpleSort, string name){

    cout << "testar " << name <<endl;
    QThread::msleep(500);

    const int size = 100;
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




bool okName5(){
    string name = nameOfTheStudent5();
    if (name=="Homer Simpson"){
        cout << "nameOfStudent5() returnerar inte DITT namn!" << endl;
        assert(false);
    }
    return true;
}


bool ragnarsTest5(){
    cout << "Ragnars test 5\n";
    cout << "Om testen lyckas kommer ett meddelande som anger detta att skrivas ut,\n"
           "annars har du en bug\n";

    QThread::msleep(500);

    bool ok = okName5()
          && testAlgorithm( bubbleSortI, "bubbleSortI")
          && testAlgorithm( bubbleSortP, "bubbleSortP")
          && testAlgorithm( insertSortI, "insertSortI")
          && testAlgorithm( insertSortP, "insertSortP") ;

    if (!ok)
        cout << endl << "Ragnars test 5 MISSLYCKADES! \7" << endl;
    else cout << endl << "Grattis, Ragnars test 5 lyckades! " << endl << endl;

    assert(ok);
    return ok;


}
