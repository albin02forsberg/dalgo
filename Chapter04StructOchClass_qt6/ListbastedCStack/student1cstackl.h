#ifndef CStackFlt_H
#define CStackFlt_H

const char* nameOfStudent1();

struct Link {
    float m_data;
    Link *m_pNext;
};

struct CStackL{
    Link *m_pTop;
    int   m_size;
};


CStackL  CStackLConstruct();
CStackL  CStackLConstruct(const CStackL &other);

void   CStackLDestruct(CStackL *pDettaObjekt);

void   CStackLPush(CStackL *pDettaObjekt, float data);
float  CStackLTop(CStackL *pDettaObjekt);
void   CStackLPop(CStackL *pDettaObjekt);
int    CStackLSize(CStackL *pDettaObjekt);


void studentTest1();

#endif // CStackFlt_H
