#ifndef TOKEN_H
#define TOKEN_H

struct Token
{
  bool m_isValueToken;
  char  m_opSymbol;
  float m_value;
  Token( char c ) : m_isValueToken(false), m_opSymbol(c), m_value(0) {}
  Token( float value ) :m_isValueToken(true), m_opSymbol(0), m_value(value) {}
  Token() {}
};



#endif // TOKEN_H
