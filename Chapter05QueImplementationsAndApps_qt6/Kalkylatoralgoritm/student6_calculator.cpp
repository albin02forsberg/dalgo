#include "studentscalculator.h"
#include <vector>

#include <math.h>
#include <assert.h>

using namespace std;


const char* nameOfStudent6(){
    return "Homer Simpson";
}


/********************************************************************
ANROP:    float valueFromInfixoperation(x, op,  y);
VERSION:  071114 RAG
UPPGIFT:  returnerar x op y;
**********************************************************************/
float valueFromInfixexpression( float x, char op,  float y)
{

  if (op=='+') return x+y;
  if (op=='-') return x-y;
  if (op=='*') return x*y;
  if (op=='/') return x/y;
  if (op=='^') return float( pow(x,y) );

  assert( false );
  return float();
}//valueFromInfixoperation


int priorityOfOp(char op){
    if (op=='+') return 1;
    if (op=='-') return 1;
    if (op=='*') return 2;
    if (op=='/') return 2;
    if (op=='^') return 3;
    return -1;
}

bool isLegalOp(char op){
    return priorityOfOp(op)>=0;
}






// Denna algoritm skall implementeras av studenten
bool applyParsingAlgorithm(const std::vector<Token> &tokens, std::vector<float> &stackOfValues, std::vector<char> &stackOfOperators)
{
    bool ok = true;

    return ok;
}







