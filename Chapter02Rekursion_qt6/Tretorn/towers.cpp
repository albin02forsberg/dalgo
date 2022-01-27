#include "towers.h"

Towers::Towers(QObject *parent) : QObject(parent), _state( 10 )
{

    _ok = true;
}





bool Towers::liftDisc(int pinSource)
{
    if (_isLifted || nbrDiscsAtPin(pinSource)==0){
        return false;
    }
    _discsizeLifted =  _state.discsizeAtTopOfPin(pinSource);
    _pinSource = pinSource;
    _isLifted = true;
    emit discLifted(pinSource);
    return true;
}

bool Towers::placeLiftedDisc(int pinDestination)
{
    if (!_isLifted)
        return false;
    if (!_state.isLegalMove(_pinSource, pinDestination))
        return false;

    _state.moveState(_pinSource, pinDestination);
    _isLifted = false;
    emit discDropped(_pinSource, pinDestination);
    return true;
}


