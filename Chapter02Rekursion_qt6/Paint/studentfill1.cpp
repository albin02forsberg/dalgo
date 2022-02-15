
#include "studentfill1.h"
#include <QDebug>

#include <algorithm>
#include <iostream>

const char* nameOfStudent1(){
    return "Albin Forsberg";
}

void recursiveFull(int r, int k, IDrawingParent *pImage, QColor colorOld, QColor colorNew){

}


void recursiveFill(int r, int k, IDrawingParent *pImage, QColor colorOld, QColor colorNew){
    if(!(*pImage).isInside(r,k)){
        return;
    }
    if((*pImage).pixel(r,k) == colorNew || (*pImage).pixel(r,k) != colorOld){
        return;
    }
    std::cout << "r: " << r << " k: " << k << std::endl;
    (*pImage).setPixel(r, k, colorNew);


    recursiveFill(r+1, k, pImage, colorOld, colorNew);
    recursiveFill(r-1, k, pImage, colorOld, colorNew);
    recursiveFill(r, k+1, pImage, colorOld, colorNew);
    recursiveFill(r, k-1, pImage, colorOld, colorNew);
}
