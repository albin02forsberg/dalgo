#ifndef STUDENTARRAYREKURSIONER_H
#define STUDENTARRAYREKURSIONER_H

#include <string>

std::string nameOfStudent();


float sum(const float *pBegin, const float *pEnd);
void fillValue(float value,  float *pBegin,  float *pEnd);
bool hasValueInRange(float min, float max, const float *pBegin, const float *pEnd);
int  numberOfValuesInRange(float min, float max, const float *pBegin, const float *pEnd);

void studentTest();


#endif // STUDENTARRAYREKURSIONER_H
