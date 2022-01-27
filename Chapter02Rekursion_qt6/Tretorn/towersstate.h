#ifndef TOWERSSTATE_H
#define TOWERSSTATE_H

#include <string>
#include <vector>



class TowersState
{
    int _nbrOfDiscs = 10;

    std::vector<int> _discsizeAtPinAndPos[3];


public:

    struct Move{
        int pinSource;
        int pinDestination;
    };

    TowersState(const TowersState& towersState);

    TowersState(int nbrOfDiscs);
    std::vector<Move> legalMoves();

    bool isLegalMove(int pinSource, int pinDestination);

    void reset(int nbrDiscs=0);
    void mix();

    bool isReseted();
    bool isFinal();

    int discsizeAtPinAndPos(int pin, int pos) { return _discsizeAtPinAndPos[pin][pos]; }
    int discsizeAtTopOfPin(int pin) { return _discsizeAtPinAndPos[pin].back(); }
    int nbrDiscsAtPin(int pin) { return _discsizeAtPinAndPos[pin].size(); }
    int nbrDiscs() { return _nbrOfDiscs; }

    void moveState(int pinSource, int pinDestination);

    void moveState(Move theMove);
    TowersState movedState(Move theMove);

    bool operator<(const TowersState& state2) const;

};

#endif // TOWERSSTATE_H
