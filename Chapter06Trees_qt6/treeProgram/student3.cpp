


#include "node.h"
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <QDebug>
#include "students.h"

using namespace std;


const char* nameOfStudent3(){
    return "Homer Simpson";
}

/**************************************************************************
 * Serialisering.
 *
 * Läsa och skriva träd från fil.
 * Dessa algoritmer skall fungera för alla typer av träd, inte bara sökträd.
 * Om man sparar ett träd och därefter läser filen skall det återskapade
 * trädet ha exakt samma struktur som det sparade trädet.
 **************************************************************************/


/**************************************************************************
 * Serialisering.
 *
 * Läsa och skriva träd från fil.
 * Dessa algoritmer skall fungera för alla typer av träd, inte bara sökträd.
 * Om man sparar ett träd och därefter läser filen skall det återskapade
 * trädet ha exakt samma struktur som det sparade trädet.
 **************************************************************************/

void saveTreeToStream(ofstream& utfil, Node *pTree){
  // TODO
}

Node *readTreeFromStream(ifstream& infil){
  return nullptr; // TODO ändra
}



void testfunktion3(Node *pTree){
    qDebug() << "testfunktion3";
    // frivilligt att skriva kod här
}
