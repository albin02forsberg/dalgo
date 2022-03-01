// copyright (c) Ragnar Nohre


#include "mazemodel.h"

#include <vector>
#include <deque>
#include <algorithm>
#include <random>
#include <QDebug>

#include <assert.h>

using namespace std;




std::random_device s_randomDevice;
std::mt19937 s_generator( s_randomDevice() );



struct Opening{
    Opening(int r, int k, bool isHorizontal) : _r(r), _k(k), _isHorizontal(isHorizontal) {}
    int r1() { return _r; }
    int k1() { return _k; }
    int r2() { return _isHorizontal ? _r : _r+1; }
    int k2() { return _isHorizontal ? _k+1 : _k; }
    int _r;
    int _k;
    bool _isHorizontal;
};


void MazeModel::constructMaze(int numRows, int numCols, bool multiPath)
{
    vector<vector<int>> idFromRK( numRows, vector<int>(numCols) );
    vector<Opening>     openingFromIndex;
    vector<Opening>     openingThatWasUsed;
    vector<int>         ideqFromId( numRows*numCols + 1);


    int id=1;
    for (int r=0;r<numRows; r+=1)
        for (int k=0; k<numCols; k+=1){
            ideqFromId[id] = id;
            idFromRK[r][k] = id;
            id += 1;
        }
    for (int r=0;r<numRows; r+=1)
        for (int k=0; k<numCols; k+=1){
            if (k<(numCols-1))
                openingFromIndex.push_back( Opening(r,k,true) );
            if (r<(numRows-1))
                openingFromIndex.push_back( Opening(r,k,false) );
        }

    shuffle( openingFromIndex.begin(), openingFromIndex.end(), s_generator );

    for (Opening opening : openingFromIndex){
        int id1 = idFromRK[opening.r1()][opening.k1()];
        int ideq1 = ideq(ideqFromId, id1);
        int id2 = idFromRK[opening.r2()][opening.k2()];
        int ideq2 = ideq(ideqFromId, id2);

        if (ideq1!=ideq2){
            openingThatWasUsed.push_back(opening);
            registerEquivalens((ideqFromId), ideq1, ideq2);            
        }
    }

    _maze = vector< vector<Cell> >( numRows*2+1, vector<Cell>(numCols*2+1) );

    for (Opening opening : openingThatWasUsed){      
        int r1Ix = opening.r1()*2+1;
        int k1Ix = opening.k1()*2+1;
        int r2Ix = opening.r2()*2+1;
        int k2Ix = opening.k2()*2+1;
        int rMid = (r1Ix+r2Ix)/2;
        int kMid = (k1Ix+k2Ix)/2;
        _maze[r1Ix][k1Ix]._isWall = false;
        _maze[r2Ix][k2Ix]._isWall = false;
        _maze[rMid][kMid]._isWall = false;
    }
    if (multiPath)
        makeMultipath();
}

void MazeModel::resetSearchData()
{
    for (int r=0; r<sizeR() ; r+= 1)
        for (int k=0 ; k<sizeK() ; k+=1){
            Cell &cell = _maze[r][k];
            cell._hasStone = false;
            cell._isRed = false;
            cell._distanceForMultipath = 0;
        }
}


void MazeModel::makeMultipath(){

    struct RK{
        RK( int r, int k) : _r(r), _k(k) {}
        int _r, _k;
    };
    vector<RK> rkPositions;
    for (int r=1; r<sizeR() ; r+=2)
       for (int k=1; k<sizeK() ; k+=2){
            rkPositions.push_back(RK(r,k));
        }
    int numEleminated = 0;
    shuffle( rkPositions.begin(), rkPositions.end(), s_generator );
    for (RK rk : rkPositions){
        setDistanceForMultipath(rk._r, rk._k);
        bool eliminated =
                   didEliminateWall(rk._r, rk._k, rk._r+2, rk._k)
                || didEliminateWall(rk._r, rk._k, rk._r-2, rk._k)
                || didEliminateWall(rk._r, rk._k, rk._r, rk._k+2)
                || didEliminateWall(rk._r, rk._k, rk._r, rk._k+2);
        if (eliminated)
            numEleminated += 1;

    }

}

bool MazeModel::didEliminateWall(int r1, int k1, int r2, int k2){
    if (isInside(r1,k1) && isInside(r2,k2)){
        Cell c1 = _maze[r1][k1];
        Cell c2 = _maze[r2][k2];
        if (std::abs(c1._distanceForMultipath - c2._distanceForMultipath)>25){
            int rMid = (r1+r2)/2;
            int kMid = (k1+k2)/2;
            assert(_maze[rMid][kMid]._isWall);

            _maze[rMid][kMid]._isWall = false;
            return true;
        }
    }
    return false;
}

void MazeModel::setDistanceForMultipath(int rz, int kz){
    for (unsigned int r=0;r< _maze.size(); r+=1)
        for (unsigned int k=0; k<_maze[r].size() ; k+=1){
           _maze[r][k]._distanceForMultipath = 9999;
        }
    struct RKD{
        RKD(int r, int k, int d) : _r(r), _k(k), _d(d) {}
        int _r,_k, _d;
    };

    deque<RKD> fifo;
    fifo.push_back( RKD(rz,kz, 0) );
    while (!fifo.empty()){
        RKD rkd = fifo.front();
        fifo.pop_front();
        if (isInside(rkd._r, rkd._k) && !isWall(rkd._r, rkd._k) && _maze[rkd._r][rkd._k]._distanceForMultipath>rkd._d){
            _maze[rkd._r][rkd._k]._distanceForMultipath = rkd._d;
            fifo.push_back( RKD(rkd._r+1, rkd._k, rkd._d+1));
            fifo.push_back( RKD(rkd._r-1, rkd._k, rkd._d+1));
            fifo.push_back( RKD(rkd._r, rkd._k+1, rkd._d+1));
            fifo.push_back( RKD(rkd._r, rkd._k-1, rkd._d+1));
        }

    }

}

int MazeModel::ideq(vector<int> &ideqFromId, int id){
    assert( ideqFromId[id] <= id );
    if (ideqFromId[id]==id)
        return id;
    ideqFromId[id] = ideq( (ideqFromId), ideqFromId[id]);
    return ideqFromId[id];
}

void MazeModel::registerEquivalens(vector<int> &ideqFromId, int id1, int id2){
    ideqFromId[ std::max(id1,id2) ] = std::min(id1,id2);
}

MazeModel::MazeModel():
    _rkStart(1,1), _rkGoal(1,1)
{

}

