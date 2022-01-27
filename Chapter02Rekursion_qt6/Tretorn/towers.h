#ifndef TOWERS_H
#define TOWERS_H

#include <QObject>
#include <vector>

#include "towersstate.h"

class Towers : public QObject
{
    Q_OBJECT

    TowersState _state;

    bool _ok = false;
    int _discsizeLifted = 0;
    int _pinSource = -1;
    bool _isLifted = false;



public:
    TowersState state() { return _state; }
    explicit Towers(QObject *parent = nullptr);
    Towers(const Towers& tow) = delete;

    void reset(int nbrDiscs=0) { _state.reset(nbrDiscs); }
    void mix() { _state.mix(); }
    int discsizeAtPinAndPos(int pin, int pos) { return _state.discsizeAtPinAndPos(pin,pos); }
    int nbrDiscsAtPin(int pin) { return _state.nbrDiscsAtPin(pin) - (_isLifted && _pinSource==pin?1:0);}
    int nbrDiscs() { return _state.nbrDiscs(); }
    bool isReseted() { return _state.isReseted(); }


    bool liftDisc(int pinSource);
    bool placeLiftedDisc(int pinDestination);

    bool isLifted() { return _isLifted; }
    int discsizeLifted() { return _discsizeLifted; }

    bool moveDisc(int pinFrom, int pinTo) { liftDisc(pinFrom); bool ok = placeLiftedDisc(pinTo); return ok;}


signals:
    void discLifted(int pinSource);
    void discDropped(int pinSource, int pinDestination);

public slots:
};

#endif // TOWERS_H
