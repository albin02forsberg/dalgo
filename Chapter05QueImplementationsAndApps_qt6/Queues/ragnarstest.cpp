#include "ragnarstest.h"


#include "student3_listque.h"
#include "student4_arrayque.h"
#include "student5_adeque.h"

#include <iostream>
#include <string>
#include <QThread>
#include <deque>
#include <assert.h>
#include <QDebug>

using namespace std;

//#pragma warning( disable : 4996 )


bool  ALLOK = true;

bool equalEndings(ADeque &q1, std::deque<float>  &q2){
    if (q1.size() == q2.size() && q1.size()==0)
        return true;

    return  q1.size() == q2.size() && q1.front() == q2.front()  && q1.back() == q2.back();
}

bool dequePushBack(ADeque &q1, std::deque<float>  &q2){
    float v = rand() / 2.5;

    q1.pushBack( v );
    q2.push_back( v );

    return equalEndings(q1,q2);
}

bool dequePushFront(ADeque &q1, std::deque<float>  &q2){
    float v = rand() / 2.5;

    q1.pushFront( v );
    q2.push_front( v );
    return equalEndings(q1,q2);
}

bool dequePopBack(ADeque &q1, std::deque<float>  &q2){

    if (q2.size()>0){
        q1.popBack(  );
        q2.pop_back( );
    }
    return equalEndings(q1,q2);
}


bool dequePopFront(ADeque &q1, std::deque<float>  &q2){
   if (q2.size()>0){
        q1.popFront( );
        q2.pop_front( );
   }
    return equalEndings(q1,q2);
}




bool ragnarsDequetest(int lev ){

    ADeque q1;
    deque<float>  q2;

    bool ok = true;
    int maxSize = 0;
    for (int i=0; i<1000000 && ok; i+=1){

        int prcIncrease = 50;
        int prcDecrease = 50;

        if (i>10000 && i<20000)
            prcIncrease = 70;
        if (i>9000)
            prcDecrease = 90;

        if (ok && lev==0 && i == 108)
            ok = ragnarsDequetest(1);

        if (rand()%100 < prcIncrease)
            ok = ok && dequePushBack((q1), (q2));
        if (rand()%100 < prcIncrease)
            ok = ok && dequePushFront((q1), (q2));
        if (rand()%100 < prcDecrease)
            ok = ok & dequePopBack((q1), (q2));
        if (rand()%100 < prcDecrease)
            ok = ok && dequePopFront((q1), (q2));

        if (q1.size()>maxSize)
            maxSize = q1.size();
    }
    return ok;
}



void tst(bool err, string str)
{
  if (err)
    { cout << str << endl;
      ALLOK = false;
    }
}


// ändra ej på denna funktion
template<typename Que> bool ragnarsKoeTest(int lev=0)
{
  if (lev==0)
    ALLOK = true;

  float arr[100];
  for (int i=0 ; i<100; ++i)
    arr[i] = float(rand());

  Que que;

  tst(que.size()!=0, "storleken ej noll");

  for (int i=0; i< 8 ; ++i)
    que.pushBack( arr[i] );

  tst(que.size()!=8, "storleken ej 8");

  tst(que.front()!=arr[0], "första fel" );
  tst(que.back()!=arr[7],  "sista fel"  );

  if (lev==0) ragnarsKoeTest<Que>(1);

  int iRemove = 0;
  for (int i=8 ; i<20 ; ++i)
  {
    tst(que.front()!=arr[iRemove], "fel i första" );
    que.popFront();

    ++iRemove;
    tst(que.size()!=7, "storleken ej 7");
    que.pushBack(arr[i]);
    tst(que.back()!=arr[i], "fel i sista");
  }

  return ALLOK;
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
    assert( success );
    return true;
}



//***********************************************************************
// ANROP:   ragnarsTest( testQue, testLQue, testADeque );
// VERSION: 2010-01-15
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//***********************************************************************
bool ragnarsTest(bool testAQue, bool testLQue, bool testADeque){
    setlocale(LC_ALL, "Swedish" );



    cout << endl << "ragnarsTest" << endl;

    bool ok = true;

    if (testLQue){
        testStart("LQue", nameOfStudentLQue() );
        ok = ragnarsKoeTest<LQue>();
        if (ok)
            cout << "(LQue lyckades! Jag har dock inte testat minnesläckor!" << endl
                 << " Verifiera själv att destruktor och pop inte läcker!)" << endl;
        else cout << "LQue misslyckades\7" << endl << endl;
        testStop("LQue", ok);
    }
    else cout << "LQue kommer ej att testas (andra detta i main)" << endl;

    if (testAQue){
        testStart("AQue", nameOfStudentAQue() );
        ok = ragnarsKoeTest<AQue>();

        if (ok)
            cout << "(AQue lyckades! << endl"
                 << "  Jag har dock inte testat minnesläckor!" << endl
                 << "     Verifiera själv att destruktor och pop inte läcker)" << endl
                 << "  Jag har inte heller testat om kon kan vaxa. " << endl
                 << "     Se uppdrags-PM for hur man testar detta.)" << endl;
        else cout << "AQue misslyckades\7" << endl << endl;
        testStop("AQue", ok);
    }
    else cout << "AQue kommer ej att testas (andra detta i main)" << endl;


    if (testADeque){
        testStart("ADeque", nameOfStudentADeque() );

        ok = ragnarsDequetest(0);

        if (ok)
            cout << "(ADeque lyckades! Jag har dock inte testat minnesläckor!" << endl
                 << " Verifiera själv att destruktor och pop inte läcker)" << endl;
        else cout << "ADeque misslyckades\7" << endl << endl;

        testStop("ADeque", ok);
    }
    else cout << "ADeque kommer ej att testas (andra detta i main)" << endl;

    return ok;


}// ragnarsTest
