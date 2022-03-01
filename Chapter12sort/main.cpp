#include <QCoreApplication>

#include "ragnarstest.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool testHeapsort  = true;  // Ändra till false om du ej implementerat heapsort
    bool testMergesort = true;  // Ändra till false om du ej implementerat mergesort

    ragnarsTest(testHeapsort, testMergesort);

    return a.exec();
}
