#ifndef STUDENTFILL2_H
#define STUDENTFILL2_H

#include <QColor>
#include "idrawingparent.h"


void nonRecursiveFillStack(int r, int k, IDrawingParent *im, QColor colorOld, QColor colorNew);
void nonRecursiveFillFifo(int r, int k, IDrawingParent *im, QColor colorOld, QColor colorNew);


#endif // STUDENTFILL2_H
