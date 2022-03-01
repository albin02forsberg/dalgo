#include "ragnarstest.h"

#include "studentscalculator.h"
#include <string>
#include <vector>
#include "assert.h"
#include <QDebug>

using namespace std;

static string  STRING_WITH_LAST_ERROR;

float myAbs(float v){
    return (v>=0 ? v : -v);
}

bool equal( float a, float b){
    const float epsilon = 0.0000001;
    return myAbs( a-b ) < epsilon;
}




vector<Token> tokensFromString(const string& str , bool addFinalEqual)
{
  string inStr = str + " ";  // så att nedanstående algoritm fungerar även om inStr slutar med en siffra

  vector<Token> vecOfTokens;

  string previousNumberString="";

  for (unsigned int i=0; i<inStr.size() ; ++i)
    {
      char ch = inStr[i];
      if (ch!='.' && (ch<'0' || ch>'9'))
        { if (previousNumberString.size()>0)
            { float value;
              sscanf( previousNumberString.c_str(), "%f", &value);
              vecOfTokens.push_back( Token(value) );
              previousNumberString = "";
            }
          if (ch!=' ')
            vecOfTokens.push_back( Token(ch) );
        }
      else previousNumberString += ch;
    }

  if (addFinalEqual)
      vecOfTokens.push_back( Token('=' ));

  return vecOfTokens;
}



bool canCalculate( string strExpression, float desiredResult ){
    vector<float> stackValues;
    vector<char> stackOps;

    vector<Token> tokens = tokensFromString(strExpression, true);

    bool ok1 = applyParsingAlgorithm(tokens, stackValues, stackOps);

    bool ok2 = ok1 && stackValues.size()==1 && stackOps.size()==0;

    bool ok3 = ok2 && stackValues.back() == desiredResult;

    if (!ok3){
        STRING_WITH_LAST_ERROR = string("Failed to evaluate ") + strExpression;
        qDebug() << QString::fromStdString( STRING_WITH_LAST_ERROR );
    }
    return ok3;
}



bool shouldHaveSyntaxError( string strExpression ){
    vector<float> stackValues;
    vector<char> stackOps;

    vector<Token> tokens = tokensFromString(strExpression, true);

    bool ok = !applyParsingAlgorithm(tokens, stackValues, stackOps);

    if (!ok){
        STRING_WITH_LAST_ERROR = "Did not find syntax error in " + strExpression;
        qDebug() << QString::fromStdString(STRING_WITH_LAST_ERROR);
    }
    return ok;
}


string stringWithLastError(){
    return STRING_WITH_LAST_ERROR;
}

bool ragnarsTest(){

    STRING_WITH_LAST_ERROR = "";

    assert( !equal(0,0.1) );

    if (string("Homer Simpson") == nameOfStudent6()){
        STRING_WITH_LAST_ERROR = "DOH! Incorrect name of student!";
        return false;
    }

    bool ok = canCalculate( "2", (float)2 );
    ok = ok && canCalculate( "2+3", (float)2+3 );
    ok = ok && canCalculate( "2-3", (float)2-3 );
    ok = ok && canCalculate( "2*3", (float)2*3 );
    ok = ok && canCalculate( "2+3", (float)2+3 );
    ok = ok && canCalculate( "2*3+4", (float)2*3+4 );
    ok = ok && canCalculate( "2+3*4", (float)2+3*4 );
    ok = ok && canCalculate( "2*(3+4)^2", (float)2*(3+4)*(3+4));
    ok = ok && canCalculate( "2*(3+4)/(5+6/2)", (float)2*(3+4)/(5+6/2) );
    ok = ok && canCalculate( "(2*(3+4)+5+6/2)/(7+8)", (float)(2*(3+4)+5+6/2)/(7+8) );

    ok = ok && shouldHaveSyntaxError("2+");
    ok = ok && shouldHaveSyntaxError("2+");
    ok = ok && shouldHaveSyntaxError("2*(3+");

    return ok;

}
