#include "ragnarstest2.h"

#include "student2stackl.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <QThread>

using namespace  std;


static bool test(){

    StackL stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4.5);

    assert( stack1.top() == 4.5 );
    assert( stack1.size() == 4 );

    StackL stack2 = stack1;
    StackL stack3 = stack2;

    stack2.pop();
    assert( stack2.size() == 3 );

    assert( stack1.top() == 4.5 );
    assert( stack2.top() == 3 );

    while( stack2.size() > 0){
        stack2.pop();
    }


    return true;
}



bool ragnarsTest2(){

    cout <<  endl << endl << nameOfStudent2() << " nu kors ragnarsTest2" << endl;
    cout << "(Efter testen skall det sta att den lyckats!) " << endl << endl;

    QThread::msleep(500);

    assert( string("Homer Simpson") != nameOfStudent2() );
    QThread::msleep(1000);

    cout << "Nu körs testen, nedanför måste det stå att den lyckats..." << endl;
    QThread::msleep(2000);

    bool ok = test();

    if (ok)
        cout << "Grattis ragnarsTest2 lyckades!" << endl << endl;
    else cout << "SORRY! ragnarsTest2 misslyckades!" << endl << endl;

    assert( ok );

    return ok;
}
