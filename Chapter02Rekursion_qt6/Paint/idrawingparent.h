#ifndef IDRAWINGPARENT_H
#define IDRAWINGPARENT_H

#include <QColor>

struct IDrawingParent {
    virtual int numberOfRows() = 0;
    virtual int numberOfColumns() = 0;
    virtual bool isInside(int r, int k) = 0;
    virtual QColor  pixel(int r, int k) = 0;
    virtual void setPixel(int r, int k, QColor) = 0;


    virtual QColor colorSelected() = 0;
    virtual bool   isPentool() = 0;
    virtual bool   isFilltool() = 0;
    virtual bool   isFulltool() = 0;

    virtual bool isFilltoolNonRecursiveStack() = 0;
    virtual bool isFilltoolNonRecursiveFifo() = 0;

  //  virtual void pixelChanged(int r, int k);
};


#endif // DRAWINGPARENT_H
