#ifndef STUDENTSCALCULATOR_H
#define STUDENTSCALCULATOR_H

#include "token.h"
#include <vector>

const char* nameOfStudent6();

bool applyParsingAlgorithm(const std::vector<Token>& tokens,
                            std::vector<float> &stackOfValues,
                            std::vector<char> &stackOfOperators);


#endif // STUDENTSCALCULATOR_H
