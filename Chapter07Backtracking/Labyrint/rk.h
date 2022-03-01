#ifndef RK_H
#define RK_H

// Lagrad en koordinat (rad och kolumn)

struct RK{
    RK(int r, int k) : m_r(r), m_k(k) {}
    RK() : m_r(0), m_k(0) {}
    int m_r;
    int m_k;
};
inline bool operator==(const RK& rk1, const RK& rk2){ return rk1.m_r==rk2.m_r && rk1.m_k==rk2.m_k; }
inline bool operator!=(const RK& rk1, const RK& rk2){ return !(rk1 == rk2); }
#endif // RK_H
