#ifndef IMAZE_H
#define IMAZE_H

struct IMaze{
    virtual int  sizeR() = 0;
    virtual int  sizeK() = 0;
    virtual bool isInside(int r, int k) = 0;
    virtual bool isWall(int r, int k) = 0;
    virtual bool isGoal(int r, int k)   = 0;
    virtual bool hasStone(int r, int k) = 0;
    virtual void placeStone(int r, int k) = 0;
    virtual void indicateThatRKIsOnPath(int r, int k) = 0;
};

#endif // IMAZE_H
