#include <iostream>
#include <string>

#include "studentbadgames.h"
#include <cassert>

using namespace std;




bool verify(bool ok, string str, int a, int b= -9999){
    if (!ok){
        std::cerr << str << ", a="<<a;
        if (b!=-9999)
            std::cerr << ", b="<<b;
        std::cerr << endl;
    }
    return ok;
}

//***********************************************************************
// ANROP:   ragnarsTest( );
// VERSION: 2010-01-15
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//***********************************************************************
bool ragnarsTest1(){

    cout << endl << endl << "ragnarsTest" << endl;

    assert( string("Homer Simpson") != nameOfStudent() );


    bool ok = true;
    for (int i=0; ok && i<100; ++i){
       int small = rand()%5;
       int big   = small + (rand()%5);
       ok = ok && verify(sum(big, small)==big+small, "sum misslyckades", big,small);
       ok = ok && verify(diff(big, small)==big-small, "diff misslyckades", big,small);
       ok = ok && verify(product(big, small)==big*small, "product misslyckades", big,small);
    }

    ok = ok && verify(pow(0,0)==1, "pow misslyckades", 0,0);
    ok = ok && verify(pow(2,0)==1, "pow misslyckades", 2,0);
    ok = ok && verify(pow(0,2)==0, "pow misslyckades", 0,2);
    ok = ok && verify(pow(2,3)==8, "pow misslyckades", 2,3);

    ok = ok && verify(fac(0)==1, "fac misslyckades", 0);
    ok = ok && verify(fac(1)==1, "fac misslyckades", 1);
    ok = ok && verify(fac(4)==2*3*4, "fac misslyckades", 4);

    cout << endl;
    if (ok)
        std::cerr << "ragnarsTest lyckades!" << endl;
    else std::cerr << "ragnarsTest MISSLYCKADES!!\7\n";

    return ok;
}// ragnarsTest
