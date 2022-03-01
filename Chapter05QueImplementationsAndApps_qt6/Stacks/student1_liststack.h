#ifndef STUDENTSLISTSTACK_H
#define STUDENTSLISTSTACK_H


const char* nameOfStudentLStack();


class LStack
{
    // Till studenten: Man får ändra på denna privata del av klassen om man vill

    struct Link{
        float  m_value;
        Link  *m_pLinkNext;
        Link(float value, Link* next) : m_value(value), m_pLinkNext(next) {}
    };

    Link *m_pBack;
    int  m_size;


public:
    // Till studenten: implementera dessa metoder i cpp-filen
    // Med undantag av destruktorn skall alla metoder ha
    // komplexitet O(1)



    LStack();
    ~LStack();


    void pushBack(float value);
    float &back();
    void  popBack();
    int   size() const;
};





void studentTest1();


#endif // STUDENTSLISTSTACK_H
