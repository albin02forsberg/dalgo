#ifndef STUDENTFILL1_H
#define STUDENTFILL1_H

#include <QColor>
#include "idrawingparent.h"

void recursiveFill(int r, int k, IDrawingParent* im, QColor colorOld, QColor colorNew);
void recursiveFull(int r, int k, IDrawingParent* im, QColor colorOld, QColor colorNew);


#endif // STUDENTFILL1_H
