#include <QCoreApplication>

#include "sortingalgorithms.h"
#include "experiments.h"
#include <cassert>
#include <string>
#include "dalgorandom.h"

#include <iostream>


using  namespace  std;

const char* nameOfStudent1();
const char* nameOfStudent2();
const char* nameOfStudent3();



int main(int , char **)
{
    cout << endl << endl <<  "main" << endl << endl << endl;


    assert( string("Homer Simpson") != nameOfStudent1() );

    testingSortAlgoritms();


    assert( string("Homer Simpson") != nameOfStudent2() );

    sixExperiments();

    stdSortExperiment();

    assert( string("Homer Simpson") != nameOfStudent3() );


}
