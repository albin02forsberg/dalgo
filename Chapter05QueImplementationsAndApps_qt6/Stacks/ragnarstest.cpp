#include "ragnarstest.h"


#include "student2_arrstack.h"
#include "student1_liststack.h"

#include <iostream>
#include <string>
#include <QThread>
#include <QElapsedTimer>
#include <assert.h>


using namespace std;



template<class CStack> bool stackTest1(int recursionDepth=0)
{
    QThread::msleep(300);
    cout << "  stackTest1 (recursionDepth " << recursionDepth << ")" << endl;

    const int size = 100;

    float arr[size];
    for (int i=0;i<size;++i)
        arr[i] = (float) rand()/RAND_MAX;


    CStack stack;

    for (int i=0; i<size ;++i){
        int z = stack.size();
        if (z!=i)
        { cout << "Fel storlek på stacken!! "<< z << " i st för "<< i <<endl;;
            return false;
        }
        stack.pushBack( arr[i] );
    }

    if (recursionDepth==0 && stackTest1<CStack>(1)==false)// Testar att stacken kan användas i en rekursion.
        return false;

    for (int i=size; i>0 ;i--)
    {
        if (stack.size()!=i){
            cout << "Fel stackstorlek, vid poppningen\n";
            return false;
        }
        if (stack.back()!=arr[i-1]){
            cout << "Fel TOP-värde pÂ stacken\n";
            return false;
        }
        stack.popBack();

    }


    return true;
}// stackTest


template<class CStack> bool stackTest2(){

    cout << "  stackTest2 (tidtagning)" << endl;

    const int big = 1000000;

    CStack stack;

    QElapsedTimer myTimer;
    myTimer.start();

    for (int i=0;i<big ; ++i){
        stack.pushBack( 1.2 );
        if (big%100==0){

            int duration = myTimer.elapsed();
            if (duration>1000){
                cout << "BUG:  Stacken är för långsam!!!" << endl;
                cout << "      testen avslutades vid i=" << i << "av ("<<big<<")" << endl;

                return false;
            }
        }
    }

    int duration = myTimer.elapsed();
    cout << "  stackTest2 avslutades inom " << duration << " ms." << endl;
    return true;

}//stackTest2


bool testStart( const char *testName, const char *studentName ){

    cout << endl << endl;
    cout << "------------------------------------------\n";
    cout << "Testing " << testName << " for student:" << studentName << endl;

    assert( string("Homer Simpson") != studentName );

    return true;
}

bool testStop( const char *testName, bool success ){

    QThread::msleep(500);
    cout << endl << testName << " " << (success? "Lyckades" : "MISSLYCKADES\7") << endl;
    cout << "------------------------------------------\n";
    assert( success );
    return true;
}

//***********************************************************************
// ANROP:   ragnarsTest(  );
// VERSION: 2010-01-15
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//***********************************************************************
bool ragnarsTest(){

    setlocale(LC_ALL, "Swedish" );


    cout << "\n\n ragnarsTest" << endl;


    bool ok = true;

//    testStart("LStack" , nameOfStudentLStack() );
//    ok = ok && stackTest1<LStack>();
//    ok = ok && stackTest2<LStack>();
//    testStop("LStack", ok);


    testStart("AStack" , nameOfStudentAStack() );
    ok = ok && stackTest1<AStack>();
    ok = ok && stackTest2<AStack>();
    testStop("AStack", ok);


    if (ok)
        cout << "(självtesten lyckades!)" << endl;

    return ok;

}// ragnarsTest
