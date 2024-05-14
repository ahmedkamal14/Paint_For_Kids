#pragma once
#include "CFigure.h"
//#include "DEFS.h"
class CCircle :public CFigure
{
	Point center, P2;
public:
	CCircle();
	CCircle(Point p1, Point p2, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual Point MoveFigure(Point P);
	virtual bool IsInside(int, int) const;
	virtual void save(ofstream& fout);
	virtual void load(ifstream& fin);
	virtual void Resize(Point, int);
	virtual void DistanceFromCenter(Point,double& DIFFx, double& DIFFy);
	virtual Point GetCorner(int);
	virtual int IsACorner(Point);
	virtual Point GetCenter();
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
};

