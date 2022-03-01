#ifndef STUDENT_H
#define STUDENT_H

#include "state.h"
#include "move.h"
#include <set>
#include <vector>

std::set<Position>      setOfPossibleFinalPositions(State state);

std::vector<Move>  movesInPathToFinal(State state, Position posOfFinal);


#endif // STUDENT_H
