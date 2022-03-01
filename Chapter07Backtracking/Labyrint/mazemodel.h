#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include "imaze.h"
#include "rk.h"
#include <assert.h>
#include <vector>
#include <random>
#include <QObject>



class MazeModel  : public QObject, public IMaze
{
    Q_OBJECT

    struct Cell{

        bool _isWall   = true;
        bool _hasStone = false;
        bool _isRed    = false;
        int  _distanceForMultipath = 0;
    };



    std::vector< std::vector<Cell> > _maze;  // (2xR+1) x (2xK+1)

public:
    RK _rkStart;
    RK _rkGoal;

    void constructMaze(int numRows, int numCols, bool multiPath);
    int  sizeR() override { return _maze.size();}
    int  sizeK() override { return _maze[0].size(); }
    bool isRed(int r, int k)    { assert(isInside(r,k));return _maze[r][k]._isRed; }

    bool isInside(int r, int k) override { return r>=0 && r<sizeR() && k>=0 && k< sizeK(); }
    bool isWall(int r, int k) override { assert(isInside(r,k)); return _maze[r][k]._isWall; }
    bool isGoal(int r, int k)  override { assert(isInside(r,k)); return _rkGoal==RK(r,k);}
    bool hasStone(int r, int k) override { assert(isInside(r,k));return _maze[r][k]._hasStone; }
    void indicateThatRKIsOnPath(int r, int k) override { assert(isInside(r,k));_maze[r][k]._isRed = true; emit mazeCellChanged(r,k);}
    void placeStone(int r, int k)  override {assert(isInside(r,k)); _maze[r][k]._hasStone = true; emit mazeCellChanged(r,k);}
    void resetSearchData();

    MazeModel();

public: signals:
    void mazeCellChanged(int r, int k);

private:
    void registerEquivalens(std::vector<int> &ideqFromId, int id1, int id2);
    int ideq(std::vector<int> &ideqFromId, int id);
    void makeMultipath();
    void setDistanceForMultipath(int rz, int kz);
    bool didEliminateWall(int r1, int k1, int r2, int k2);
};

#endif // MAZEMODEL_H
