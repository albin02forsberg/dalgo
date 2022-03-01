// copyright (c) Ragnar Nohre

#include "state.h"
#include <assert.h>

using namespace std;

/******************************************************************

indexnummer enligt nedanstående:

                  0
                1   2
              3   4   5
            6   7   8   9
          10  11  12  13 14
 ******************************************************************/


static int s_posFromDirAndPrevpos[3][16]
    //00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
= { {15,0,15, 1, 2,15, 3, 4, 5,15, 6, 7, 8, 9,15,15},
    {15,2,15, 4, 5,15, 7, 8, 9,15,11,12,13,14,15,15},
    { 2,4, 5, 7, 8, 9,11,12,13,14,15,15,15,15,15,15}} ;

static int s_posFromReversedirAndPrevpos[3][16];

static int initReverse();

static int dum = initReverse();

static int initReverse()
{
 for (int direction =0; direction<3 ; ++direction)
    for (int pos=0 ; pos<16 ; ++pos)
      s_posFromReversedirAndPrevpos[direction][pos]=15;
 for (int direction =0; direction<3 ; ++direction)
    for (int pos=0 ; pos<16 ; ++pos)
    s_posFromReversedirAndPrevpos[direction][ s_posFromDirAndPrevpos[direction][pos] ] = pos;
 return 0;
}

// pinnen flyttas i riktning direction=0...5
Position posNeighbour(Position position, int direction)
{
  if (direction<3)
     return s_posFromDirAndPrevpos[direction][position];
     return s_posFromReversedirAndPrevpos[direction-3][position];
}

// pinnen flyttas tvÂ steg i riktning direction=0...5
Position posdestinationFromPosAndDirection(Position position, int direction)
{
  return posNeighbour( posNeighbour(position,direction), direction );
}





State::State(void)
{
    m_state = 0;
    for (int i=1 ; i<5 ; ++i)
        setPos( i );
    for (int i=8 ; i<11 ; ++i)
        setPos( i );
}// konstruktor

State::~State(void)
{
}

bool State::isOccupied(Position position) const
{
   return position>=0 && position<=14 && ((m_state & (1<<position))!=0);
}

bool State::isFree(Position position) const
{
    return position>=0 && position<=14 && ((m_state & (1<<position))==0);
}

void State::setPos(Position position)
{
  m_state = m_state | (1<<position);
}

void State::clearPos(Position position)
{
    m_state = m_state & ~(1<<position);
}

/************************************************************
ANROP:    vector<Move> moves = state.legalMoves();
VERSION:  2004-08-17/2017-10-01 RAG
UPPGIFT:  Returnerar ett objekt som beskriver alla mˆjliga
          drag i detta tillstÂnd
************************************************************/
vector<Move> State::legalMoves( )
{
  vector<Move>  moves;
  for (int pin=0;pin<15 ;++pin)
    { if (isOccupied(pin))
         for (int direction=0 ;direction<6;++direction)
             if (isOccupied( posNeighbour(pin,direction) ) && isFree( posdestinationFromPosAndDirection(pin,direction) ))
                  moves.push_back( Move(pin,direction) );
    }
  return moves;
}// legalMoves



/************************************************************
ANROP:    vector<Move> moves = state.legalMoves(pos);
VERSION:  2004-08-17/2017-10-01 RAG
UPPGIFT:  Returnerar ett objekt som beskriver alla möjliga
          drag av pinne pos i detta tillstÂnd
************************************************************/
vector<Move>  State::legalMoves(Position position)
{
    vector<Move>  moves;
    if (isOccupied(position)){
        for (int direction=0 ;direction<6;++direction){
            int mid = posNeighbour(position, direction);
            int dest = posdestinationFromPosAndDirection(position, direction);
            if (isOccupied(mid) && isFree(dest)){
                moves.push_back( Move(position,direction) );
            }
        }
    }
    return moves;
}



/************************************************************
ANROP:    int nr = state.numberPins();  // 0..15
VERSION:  2004-08-17/2017-10-01 RAG
UPPGIFT:  Returnerar antalet pinnar i tillstÂndet, dvs ett
          tal mellan 0 och 15.
************************************************************/
int State::numberOfBricks()
{
    int n=0;
    for (int i=0; i<15 ; ++i)
        if (isOccupied(i))
            ++n;
    return n;
}// numberPins

/************************************************************
ANROP:    State ns = state.nextState(move);
VERSION:  2004-08-17/2017-10-01 RAG
UPPGIFT:  Returnerar n‰sta tillstÂnd efter engivet drag.
************************************************************/
State State::nextState(const Move& move)
{
    assert( isLegal(move) );

    State s = *this;
    s.clearPos( move.m_pos );
    s.clearPos( posNeighbour( move.m_pos, move.m_direction ) );
    s.setPos( posdestinationFromPosAndDirection( move.m_pos, move.m_direction ) );
    return s;
}// nextState


/************************************************************
ANROP:    int ix = state.getFinalIndex()
VERSION:  2004-08-17/2017-10-01 RAG
UPPGIFT:  Under fˆruts‰ttning att tillstÂndet innehÂller
          exakt en spelmarker sÂ returneras dess index (0..14)
************************************************************/
Position State::positionOfSingleBrick()
{
    assert( numberOfBricks()==1 );

    for (int p=0;p<15;++p)
        if (isOccupied(p))
            return p;
    return 0;
}// getFinalIndex

bool State::isLegal(Move move)
{
  int ix1   = move.m_pos;
  int ixMid = posNeighbour( ix1, move.m_direction );
  int ix2   = posNeighbour( ixMid, move.m_direction );

  bool ok = isOccupied(ix1) && isOccupied(ixMid) && isFree(ix2);

  return ok;
}


