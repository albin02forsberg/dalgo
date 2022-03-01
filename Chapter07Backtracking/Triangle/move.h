#ifndef MOVE_H
#define MOVE_H

typedef int Position; // 0..14, dvs 15 möjliga positioner

struct Move
{

  Move() : m_pos(0), m_direction(0) {}
  Move( int pos, int direction ) : m_pos(pos), m_direction(direction) {}

  Position m_pos;    // En pinne kan ha 15 olika start-positioner:   0..14
  int m_direction; // pinne kan flyttas i 6 olika riktningar:   0..5
};

#endif // MOVE_H
