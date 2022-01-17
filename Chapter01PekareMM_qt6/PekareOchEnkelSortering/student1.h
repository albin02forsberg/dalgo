#ifndef STUDENT1_H
#define STUDENT1_H

// pekaruppdragen går ut på att implementera nedastående funktioner i cpp-filen

const char *nameOfTheStudent1();
void mainFunctionInStudent1();


float minimumI(const float *pBegin, const float *pEnd);
float maximumI(const float *pBegin, const float *pEnd);
float sumI(const float *pBegin, const float *pEnd);
void fillRandomI(float *pBegin, float *pEnd);
void fillSortedRandomI(float *pBegin, float *pEnd);
bool  hasValueInRangeI(float min, float max, const float *pBegin, const float *pEnd);
int numberOfValuesInRangeI(float min, float max, const float *pBegin, const float *pEnd);


float minimumP(const float *pBegin, const float *pEnd);
float maximumP(const float *pBegin, const float *pEnd);
float sumP(const float *pBegin, const float *pEnd);
void fillRandomP(float *pBegin, float *pEnd);
void fillSortedRandomP(float *pBegin, float *pEnd);
bool  hasValueInRangeP(float min, float max, const float *pBegin, const float *pEnd);
int numberOfValuesInRangeP(float min, float max, const float *pBegin, const float *pEnd);





#endif // STUDENT1_H
