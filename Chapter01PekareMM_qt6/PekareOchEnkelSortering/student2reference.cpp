#include "student2reference.h"

#include <iostream>
using namespace std;


const char* nameOfTheStudent2(){
    return "Albin Forsberg";  // Byt ut denna sträng mot ditt eget namn!
}




// ################ experiment med värde- pekar- och referensanrop #################



struct Exempelstruct{
    int m_intValue1;
    int m_intValue2;
    float m_array[1000];
    int m_intValue3;

};


// Skriver ut structobjektets adress, samt adresserna till alla
// medlemmar i objektet.
void skrivStruktensAdresser(const Exempelstruct &s){
    cout << "&s " << "\t\t== " << &s << endl;
    cout << "&s.m_intValue1 " << "\t== "  << &s.m_intValue1 << endl;
    cout << "&s.m_intValue2 " << "\t== "  << &s.m_intValue2 << endl;
    cout << "s.m_array "      << "\t== "   << s.m_array << endl;
    cout << "&s.m_intValue3 " << "\t== " << &s.m_intValue3 << endl;
}




// call by value, theStruct kommer att kopieras (även arrayen)
void skrivAdresser1(Exempelstruct theStruct){
    cout << "skrivAdresser1" << endl;
    cout << "--------------" << endl;
    skrivStruktensAdresser( theStruct );
    cout << endl << endl;
}


// call by reference, theStruct är identisk med anroparens s.
void skrivAdresser2(const Exempelstruct &theStruct){
    cout << "skrivAdresser2" << endl;
    cout << "--------------" << endl;
    skrivStruktensAdresser( theStruct );
    cout << endl << endl;
}

// call by pointer. Nu är (*pThestruct) identisk med anroparens s.
void skrivAdresser3(const Exempelstruct *pTheStruct){
    cout << "skrivAdresser3" << endl;
    cout << "--------------" << endl;
    skrivStruktensAdresser( *pTheStruct );
    cout << endl << endl;
}


// Experimentkoden är färdigskriven med betrakta utskrifterna!!
void experimentMedParameteroverforing(){

    cout << "Experiment med parameteröverföring!\n";
    cout << "(studera utskrifterna så att du kan förklara dem i nedanstående kommentar)" << endl;

    Exempelstruct mittObjekt;

    skrivAdresser1(mittObjekt);
    skrivAdresser2(mittObjekt);
    skrivAdresser3(&mittObjekt);

    /* TODO!!
       Skriv din förklaring här:
       (förklara allt som efterfrågas i kompendiet!)



     */
}




void mainFunctionInStudent2(){

    cout << "\n\n\n################ testingCode2 #################\n\n";

    experimentMedParameteroverforing();
}
