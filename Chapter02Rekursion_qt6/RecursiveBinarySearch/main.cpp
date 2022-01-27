
#include "studentbinsearch1.h"
#include "studentbinsearch2.h"
#include "ragnarstest.h"

#include <cassert>
#include <iostream>

using namespace std;




int  main()
{

    studentsTest1();
    bool ok = ragnarsTest1();

    // Ändra nedanstående variabel till false om du ej löst
    // den frivilliga uppgiften pointerToFirstGreaterorequalThanX

    bool didImplementPointerToFirstGreaterorequalThanX = true;
    if (didImplementPointerToFirstGreaterorequalThanX){
        studentsTest2();
        ok = ragnarsFloatTest();
    }
    else cout << "\n\nDen frivilliga uppgiften ar ej implementerad!\n\n";




}



void studentsTest1();
