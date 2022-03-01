#include <QCoreApplication>
#include "ragnarstest.h"

#include "student1_liststack.h"
#include "student2_arrstack.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    studentTest1();
    studentTest2();

    ragnarsTest();

    return a.exec();

}
