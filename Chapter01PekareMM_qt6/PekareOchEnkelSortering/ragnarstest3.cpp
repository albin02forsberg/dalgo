#include "ragnarstest3.h"
#include "student3swaps.h"
#include <string>
#include <iostream>
#include <qthread.h>
#include <cassert>
using namespace std;

bool okName3(){
    string name = nameOfTheStudent3();
    QThread::msleep(100);

    if (name=="Homer Simpson"){
        cout << "nameOfStudent3() returnerar inte DITT namn!" << endl;
        assert( false);
    }
    return true;
}




bool testSwaps(){
    cout << "testar swap " << endl;
    QThread::msleep(100);


    float x0 = 9.9f;
    float y0 = 1.9f;

    float x = x0;
    float y = y0;
    swap(&x, &y);
    assert( x==y0 && y==x0 );

    swap(x,y);
    assert( x==x0 && y==y0 );

    return true;
}




bool ragnarsTest3(){

    cout << "\n\nRagnars test 3." << endl;
    QThread::msleep(500);

    bool ok =  okName3() && testSwaps();
    if (ok)
        cout << "Grattis test 3 lyckades" << endl;
    assert(ok);
    return ok;
}
