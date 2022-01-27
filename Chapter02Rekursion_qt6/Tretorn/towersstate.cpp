#include "towersstate.h"

#include <vector>
#include <assert.h>

using namespace std;

TowersState::TowersState(const TowersState &towersState)
{
    _nbrOfDiscs = towersState._nbrOfDiscs;
    for (int pin=0;pin<3;pin+=1)
        _discsizeAtPinAndPos[pin] = towersState._discsizeAtPinAndPos[pin];
}

TowersState::TowersState(int nbrOfDiscs)
{
    reset( nbrOfDiscs );

}

std::vector<TowersState::Move> TowersState::legalMoves()
{
    vector<Move> moves;
    for (int pinSource=0; pinSource<3; pinSource+=1)
        for (int pinDestination=0; pinDestination<3;pinDestination+=1)
            if (pinSource!=pinDestination && isLegalMove(pinSource,pinDestination))
                moves.push_back({pinSource,pinDestination});
    return moves;
}

bool TowersState::isLegalMove(int pinSource, int pinDestination)
{
    if (nbrDiscsAtPin(pinSource)==0)
        return false;
    if (nbrDiscsAtPin(pinDestination)==0)
        return true;
    return discsizeAtTopOfPin(pinSource)<discsizeAtTopOfPin(pinDestination);
}


void TowersState::reset(int nbrDiscs)
{
    for (int pin=0; pin<3; pin+=1)
        _discsizeAtPinAndPos[pin].clear();

    if (nbrDiscs)
        _nbrOfDiscs = nbrDiscs;
    for (int size = _nbrOfDiscs-1 ; size>=0; size-=1){
        _discsizeAtPinAndPos[0].push_back(size);
    }
}

void TowersState::mix()
{
    for (int pin=0; pin<3; pin+=1)
        _discsizeAtPinAndPos[pin].clear();

    for (int size = _nbrOfDiscs-1 ; size>=0; size-=1){

        _discsizeAtPinAndPos[rand()%3].push_back(size);
    }
}

bool TowersState::isReseted()
{
    if (nbrDiscsAtPin(0)!=nbrDiscs())
        return false;

    for (int pos = 0 ; pos<_nbrOfDiscs; pos+=1){
        if (_discsizeAtPinAndPos[0][pos] != _nbrOfDiscs-1-pos )
            return false;
    }
    return true;
}

bool TowersState::isFinal()
{
    if (nbrDiscsAtPin(2)!=nbrDiscs())
        return false;

    for (int pos = 0 ; pos<_nbrOfDiscs; pos+=1){
        if (_discsizeAtPinAndPos[2][pos] != _nbrOfDiscs-1-pos )
            return false;
    }
    return true;
}

void TowersState::moveState(int pinSource, int pinDestination)
{
    assert( isLegalMove(pinSource, pinDestination));
    _discsizeAtPinAndPos[pinDestination].push_back(discsizeAtTopOfPin(pinSource));
    _discsizeAtPinAndPos[pinSource].pop_back();
}

void TowersState::moveState(TowersState::Move theMove)
{
    moveState(theMove.pinSource, theMove.pinDestination);
}

TowersState TowersState::movedState(TowersState::Move theMove)
{
    TowersState state = *this;
    state.moveState(theMove);
    return state;
}

bool TowersState::operator<(const TowersState &state2) const
{
    for (int pin=0; pin<3;pin+=1){
        if (_discsizeAtPinAndPos[pin] < state2._discsizeAtPinAndPos[pin])
            return true;
        if (_discsizeAtPinAndPos[pin] > state2._discsizeAtPinAndPos[pin])
            return false;
    }
    return false;
}
