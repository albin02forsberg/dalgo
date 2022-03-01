
#include "studentfill1.h"
#include <QDebug>

#include <algorithm>

const char* nameOfStudent1(){
    return "Albin Forsberg";
}

void recursiveFull(int r, int k, IDrawingParent *pImage, QColor colorOld, QColor colorNew){
   // behöver ej implementeras
}


void recursiveFill(int r, int k, IDrawingParent *pImage, QColor colorOld, QColor colorNew){
    if(!(*pImage).isInside(r,k)){
        return;
    }
    if((*pImage).pixel(r,k) == colorNew || (*pImage).pixel(r,k) != colorOld){
        return;
    }
    (*pImage).setPixel(r, k, colorNew);


    recursiveFill(r+1, k, pImage, colorOld, colorNew);
    recursiveFill(r-1, k, pImage, colorOld, colorNew);
    recursiveFill(r, k+1, pImage, colorOld, colorNew);
    recursiveFill(r, k-1, pImage, colorOld, colorNew);
}
