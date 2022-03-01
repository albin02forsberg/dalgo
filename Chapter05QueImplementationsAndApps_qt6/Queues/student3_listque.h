#ifndef STUDENTSLISTQUE_H
#define STUDENTSLISTQUE_H


const char* nameOfStudentLQue();



class LQue
{
    // Till studenten: Man får ändra på denna privata del av klassen om man vill

    struct Link{
        Link(float value=0, Link *pNext=nullptr) : m_value(value), m_pNext(pNext) {}
        float m_value;
        Link *m_pNext;
    };

    Link  *m_pFront;
    Link  *m_pBack;
    int   m_size;

public:
    // Till studenten: implementera dessa metoder i cpp-filen
    // Med undantag av destruktorn skall alla metoder ha
    // komplexitet O(1)

    LQue();
    ~LQue();

    void pushBack(float value);
    float &back();
    void popFront();
    float &front();
    int  size() const;
    void print();
};

#endif // STUDENTSLISTQUE_H
