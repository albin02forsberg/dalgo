#include <QCoreApplication>
#include "studentstest.h"

#include "ragnarstest.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    studentstest();

    bool testAQue  = true;
    bool testLQue   = true;
    bool testADeque   = true;

    ragnarsTest(testAQue, testLQue, testADeque);


    return a.exec();
}

