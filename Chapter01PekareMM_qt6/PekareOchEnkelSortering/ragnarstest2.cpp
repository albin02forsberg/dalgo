#include "ragnarstest2.h"
#include "student2reference.h"
#include <QThread>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;



bool okName2(){
    string name = nameOfTheStudent2();

    if (name=="Homer Simpson"){
        cout << "nameOfStudent2() returnerar inte DITT namn!" << endl;
        assert( false );
    }
    return true;
}


bool ragnarsTest2(){
    cout << "\n\nRagnars test 2" << endl;

    QThread::msleep(500);
    bool ok = okName2();

    cout << "Detta uppdrag har ingen test. "<< endl;
    QThread::msleep(500);

    return ok;
}
