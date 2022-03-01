#ifndef STUDENTSADEQUE_H
#define STUDENTSADEQUE_H

#include <deque>

const char* nameOfStudentADeque();


class ADeque
{
    float *m_pArr;
    int    m_indexOfFront;
    int	   m_indexOfBack;
    int    m_size;
    int    m_capacity;

public:
    // Till studenten: implementera dessa metoder i cpp-filen
    // Alla metoder ha (genomsnittlig) komplexitet O(1)

    ADeque();
    ~ADeque();

    void pushBack(float value);
    void pushFront(float value);

    void popBack();
    void popFront();

    void print();

    float &back();
    float &front();
    int  size() const;
};

#endif // STUDENTSADEQUE_H
