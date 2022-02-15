#include "ragnarstest.h"

#include "student1cstackl.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <QThread>

using namespace  std;

bool test1(){
    cout << endl << "testar test1()" << endl;
    CStackL stack1 = CStackLConstruct();
    CStackL stack2 = CStackLConstruct(stack1);
    return CStackLSize(&stack2)==0;
}

bool test2(){
    cout << endl << "testar test2()" << endl;
    CStackL stack1 = CStackLConstruct();
    CStackLPush(&stack1,1);
    CStackL stack2 = CStackLConstruct(stack1);
    CStackL stack3 = CStackLConstruct(stack2);
    return CStackLSize(&stack3)==1;
}



bool test3(){
    cout << endl << "testar test3()" << endl;

    CStackL stack1 = CStackLConstruct();
    CStackLPush( &stack1,  1);
    CStackLPush( &stack1,  2);
    CStackLPush( &stack1,  3);
    CStackLPush( &stack1,  4.5);


    assert( CStackLTop(&stack1) == 4.5 );
    assert( CStackLSize(&stack1) == 4 );

    CStackL stack2 = CStackLConstruct(stack1);

    CStackLPop( &stack2);
    assert( CStackLSize(&stack2) == 3 );

    CStackL stack3 = CStackLConstruct(stack2);

    assert(  CStackLSize( &stack3 ) == 3 );

    assert( CStackLTop( &stack1 ) == 4.5 );
    assert( CStackLTop( &stack2 ) == 3 );

    while( CStackLSize(&stack2) > 0){
        CStackLPop( &stack2 );
    }


    CStackLDestruct( &stack1 );
    CStackLDestruct( &stack2 );
    CStackLDestruct( &stack3 );

    return true;
}


bool test(){
    bool ok = test1()
             && test2()
             && test3();
    return ok;
}


bool ragnarsTest1(){

    cout <<  endl << endl << nameOfStudent1()  << " nu kors ragnarsTest1" << endl;
    cout << "(Efter testen skall det sta att den lyckats!) " << endl << endl;


    QThread::msleep(1000);

    assert( string("Homer Simpson") != nameOfStudent1() );
    bool ok = test();
    QThread::msleep(1000);

    cout << "Nu körs testen, nedanför måste det stå att den lyckats..." << endl << endl;
    QThread::msleep(2000);


    if (ok)
        cout << "Grattis ragnarsTest1 lyckades!" << endl << endl;
    else cout << "SORRY! ragnarsTest1 misslyckades!" << endl << endl;

    assert( ok );

    return ok;
}
