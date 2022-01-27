#include <iostream>
#include "studentIdentiskaAnrop.h"

using namespace std;




void assertApproximation(float value, float approximation){
    float diff = value - approximation;
    float epsilon = 0.01f;
    assert( -epsilon < diff && diff < epsilon );
}

void ragnarsTest(){

    // Första testet (size 4):					0.12 sek
    // Andra testet (size 32): 					0.12 sek
    // Tredje testet (utan konstant, size 4):	0.12 sek
    // Fjärde testet (utan konstant, size 32): 	> 10 min
    //
    // Det fjärde testet tar mycket längre tid eftersom
    // jämfört med de första tre är det en större mängd
    // data som algoritmen måste gå igenom.

    cout << "ragnarsTest testar att minimum fungerar..." << endl;
    const int size = 32;
    float arr[size]{ -1.2, 5.5, 1, 5.5 };
    assertApproximation( minimum(&arr[0], &arr[size]),  -1.2);

    float arr2[size]{ -1.2, 5.5, 1, -5.5 };
    assertApproximation( minimum(&arr2[0], &arr2[size]),  -5.5);

    cout << "...minimum tycks fungera " << endl;

}





int main()
{
    cout << endl << "Identiska Anrop" << endl<< endl;

    studentsTest();
    ragnarsTest();

    timingExperiment();

    return 0;
}
