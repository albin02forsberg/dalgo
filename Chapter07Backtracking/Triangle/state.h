#ifndef STATE_H
#define STATE_H

#include <vector>

#include "move.h"


class State
{
    int m_state; // bitarna i detta heltal anger vilka kulor som är närvarande
public:
    State();
    State(const State& s) { m_state = s.m_state; }
    int integerFromState() { return m_state; }
    virtual ~State();

    bool isOccupied(Position position ) const;
    bool isFree(Position position ) const;
    void setPos(Position position);
    void clearPos(Position position);

    std::vector<Move>  legalMoves();
    std::vector<Move>  legalMoves(Position position);
    int numberOfBricks();
    State nextState(const Move& move);
    Position positionOfSingleBrick();
    bool isLegal(Move move);
};


Position posNeighbour(Position position, int direction);
Position posdestinationFromPosAndDirection(Position position, int direction);

#endif // STATE_H
