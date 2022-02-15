#ifndef STACKOFFLOATS_H
#define STACKOFFLOATS_H


class StackL {
private:
    struct Link {
        float m_data;
        Link *m_pNext;
    };

    Link *m_pTop;
    int  m_size;

public:
    StackL();
    StackL(const StackL& theOther);
    ~StackL();

    void push(float value);
    void pop();
    float top() const;
    int size() const;
    void print();
};




void studentTest2();
const char* nameOfStudent2();

#endif // STACKOFFLOATS_H
