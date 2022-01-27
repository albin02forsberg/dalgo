#include "ragnarstest.h"

#include <iostream>

#include "studentbinsearch1.h"
#include "studentbinsearch2.h"
#include <QThread>
#include <QElapsedTimer>
#include <assert.h>

float  GLOBAL = 0;

using namespace std;

bool isDebugmode() {
    bool debugging = false;

#ifdef QT_DEBUG
    debugging = true;
#endif
    return debugging;
}


bool verify(const float* pBegin, const float *pEnd, float searched, const float* pResult){


    if (pResult<pBegin || pResult>pEnd){
        cerr << "felaktig pekare utanför området returnerades !\n";
        return false;
    }
    if (pResult == pEnd){
        if (searched <= *(pEnd - 1)){
            cerr << "pEnd returnerades felaktigt !\n";
            return false;
        }
        return true;
    }

    if (pResult == pBegin){
        if (searched > *pBegin){
            cerr << "pBegin returnerades felaktigt !\n";
            return false;
        }
        return true;
    }

    bool ok1 = (*pResult >= searched);
    bool ok2 = (*(pResult - 1) < searched);
    if (!ok1 || !ok2){
        cerr << "felaktig pResult, ok1 = " << ok1 << " ok2 = " << ok2 << endl;

        int ix = pResult - pBegin;
        cerr << "pResult motsvarar index " << ix << endl;
        return false;
    }

    if (*pResult==0)
        GLOBAL += 1;

    return true;

}


bool ragnarsSecondFloatTest(){
    const int M = 10000000;


    float *ptr = new float[M+1];

    float lastValue = -1000;

    int index = 0;
    while (index<M){
        lastValue += 1;
        for (int i=0; i<100000 && index<M ; i+=1)
            ptr[index++] = lastValue;
    }

    QElapsedTimer myTimer;
    myTimer.start();

    bool ok = true;
    for (int i = 0; ok && i < M; i+=10){
        const float *pResult = pointerToFirstElementGreaterOrEqualToX(ptr[i], ptr, ptr+M);
        verify(ptr, ptr+M, ptr[i], pResult);
        unsigned long timeElapsed = myTimer.elapsed();
        if (timeElapsed > 10000){
            std::cerr << "BUG 4:  din funktionen är för långsam!!\n(förmodligen ej rekursiv på rätt sätt) \7\n";
            ok = false;
        }

    }
    unsigned long timeElapsed = myTimer.elapsed();
    std::cerr << "(secondFloatTest avslutades inom " << timeElapsed << " ms.)\n";

    delete [] ptr;
    return ok;

}


//***********************************************************************
// ANROP:   ragnarsFloatTest()
// VERSION: 2010-01-15
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//***********************************************************************
bool ragnarsFloatTest(){

    cout << endl << endl << "ragnarsFoatTest" << endl;

    assert( string("Homer Simpson") != nameOfStudent2() );


    const int len = 100000;
    float* ptr = new float[len];
    ptr[0] = -1000;
    for (int i = 1; i < len; ++i)
        ptr[i] = ptr[i - 1] + (rand() % 4) / 4.0f;

    // ptr är nu en sorterad array av längd len med flera dubletter

    QElapsedTimer myTimer;
    myTimer.start();
    bool ok = true;
    int notImplemented = 0;
    const float *pBegin = ptr;
    const float *pEnd = ptr + len;

    for (int i = 0; ok && i < len; ++i){
        const float* pf1 = pointerToFirstElementGreaterOrEqualToX( ptr[i], pBegin, pEnd);
        const float* pf2 = pointerToFirstElementGreaterOrEqualToX( ptr[i] + 0.1f, ptr, ptr + len);

        if (pf1 == nullptr && pf2 == nullptr){
            notImplemented += 1;
            continue;
        }

        ok = verify(pBegin, pEnd, ptr[i], pf1) && verify(pBegin, pEnd, ptr[i] + 0.1, pf2);

        unsigned long timeElapsed = myTimer.elapsed();

        if (timeElapsed > 1000){
            std::cerr << "BUG 4:  din funktionen är för långsam!!\n(förmodligen ej rekursiv på rätt sätt) \7\n";
            ok = false;
        }
    }
    if (notImplemented > 0)
        ok = false;

    unsigned long eclapsed = myTimer.elapsed();

    if (notImplemented == len && eclapsed < 100){
        delete[] ptr;
        std::cerr << "float search not implemented!!\n";
        return true;
    }

    ok = ok && ragnarsSecondFloatTest();

    if (ok)
        std::cerr << "ragnarsFloatTest lyckades på " << eclapsed << " millisekunder\n";
    else std::cerr << "ragnarsFloatTest MISSLYCKADES!!\7\n";

    delete[]ptr;
    return ok;
}// ragnarsFloatTest



void testArrayWithZeroOrOneElement(){
    int smallArr[] = { 1, 3, 5 };

    // sök efter olika tal i en array som bara innehåller 3:an
    // (talen 1 och 5 ligger utanför arrayen)
    assert( containedInSortedarray(3, &smallArr[1], &smallArr[2]) );
    assert( !containedInSortedarray(1, &smallArr[1], &smallArr[2]) );
    assert( !containedInSortedarray(5, &smallArr[1], &smallArr[2]) );

    // sök i tom array (pBegin == pEnd)
    assert( !containedInSortedarray(3, &smallArr[1], &smallArr[1]) );
}

void testShortArrays(){
    const int size = 7;
    int oddNumbers[size] = { -7, -5, -3, 1, 3, 5, 7 };

    const int *pBegin = &oddNumbers[1];
    for (const int *pEnd = pBegin;  pEnd< &oddNumbers[size]; ++pEnd ){
        assert( !containedInSortedarray(*(pBegin-1),  pBegin,pEnd) );
        assert( !containedInSortedarray(*pEnd,  pBegin,pEnd) );

        for (int even=-10; even<10 ; even+=2)
            assert( !containedInSortedarray(even,  pBegin,pEnd) );

        for (const int *pExisting = pBegin; pExisting<pEnd; ++pExisting)
            assert( containedInSortedarray(*pExisting,  pBegin,pEnd) );
    }
}


void assertTimer(QElapsedTimer &timer){
    if (timer.elapsed()>1000){
        if (isDebugmode()){
            std::cerr << "BUG?? Din funktion är lååångsam.\n"
                      << "Kompilera i RELEASE-mode så kanske det går snabbare.\n";
        }
        else {
            std::cerr << "BUG:  din funktionen är för långsam!!\n"
                      << "(förmodligen ej rekursiv på rätt sätt) \7\n";
        }
        assert( false );
    }
}


void testComplexity(){

    const int size = 100000;
    int* pEven = new int[size];

    pEven[0] = -1000;

    for (int i = 1; i < size; ++i)
        pEven[i] = pEven[i - 1] + 2 * (rand() % 10);

    // pEven är en sorterad array med jämna tal

    cout << "Vi kommer nu att söka efter " << size << " existerande och " << size << " ickeexisterande tal i en array bestående av " << size << " tal...\n";

    QElapsedTimer timer;
    timer.start();


    for (const int* pData = pEven; pData<pEven+size; pData++){
        assert( containedInSortedarray(*pData, pEven, pEven+size) );
        assert( !containedInSortedarray(1 + *pData, pEven, pEven+size) );

        assertTimer(timer);
    }

    unsigned long elapsed = timer.elapsed();
    cout << "Tidsmätning: "<< elapsed << " millisekunder\n";

    delete []pEven;

}
//***********************************************************************
// ANROP:   ragnarsTest1(  );
// VERSION: 2010-01-15
// UPPFIFT: Testar en eller flera rutiner som studenten har skrivit.
//***********************************************************************
bool ragnarsTest1(){


    cout << endl << endl << "ragnarsTest1" << endl;

    QThread::msleep(100);
    cout << "När testen är klar kommer programmet att skriva att testen har lyckats,\n"
            "i annat fall har ditt program antagligen kraschat...\n";

    QThread::msleep(100);


    assert( string("Homer Simpson") != nameOfStudent1() );



    QThread::msleep(1000);


    if (isDebugmode())
        cout << "Du bor aven kora denna test i RELEASE-mode!\n\n";
    QThread::msleep(500);

    cout << "Vi koer nu testArrayWithZeroOrOneElement ...\n";


    testArrayWithZeroOrOneElement();

    QThread::msleep(500);

    cout << "Vi koer nu testShortArrays ...\n";

    testShortArrays();

    QThread::msleep(500);

    cout << "Vi koer nu testComplexity ...\n";

    testComplexity();

    cout << "Testen ragnarsTest1 har lyckats! \n";
    if (isDebugmode())
        cout << "testen lyckades troligtvis, men kör även i RELEASE-mode!! \7\n";

    QThread::msleep(1000);

    cout << "\n\n\n";

    return true;
}// ragnarsTest1
