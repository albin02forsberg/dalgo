#include "mainwindow.h"
#include <QApplication>
// LIBS += /Users/nora/Library/Mobile\ Documents/com\~apple\~CloudDocs/SKOLAN/kurserna/OOP/complete/shape-lib_clang-64_qt-5-14-1_debug.a


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
