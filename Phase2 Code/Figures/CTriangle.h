#pragma once
#include "CFigure.h"
class CTriangle :
    public CFigure
{
private:
    Point Corner1;
    Point Corner2;
    Point Corner3;
public:
    CTriangle();
    CTriangle(Point, Point, Point , GfxInfo );
    virtual void Draw(Output* pOut) const;
    virtual bool IsInside(int, int) const;
    virtual Point MoveFigure(Point P);
    virtual void save(ofstream& fout);
    virtual void load(ifstream& fin);
    virtual void Resize(Point, int);
    virtual int IsACorner(Point);
    virtual Point GetCorner(int);
    virtual Point GetCenter();
    virtual void DistanceFromCenter(Point, double& DIFFx, double& DIFFy);

    virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
};

