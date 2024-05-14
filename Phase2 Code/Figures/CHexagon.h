#pragma once
#include "CFigure.h"
class CHexagon :
    public CFigure
{
private:
	Point Center;
	int length;
public:
	CHexagon();

	CHexagon(Point, GfxInfo FigureGfxInfo, int l);

	virtual void Draw(Output* pOut) const;

	virtual bool IsInside(int, int)const;

	virtual Point MoveFigure(Point P);

	virtual void save(ofstream& fout);

	virtual void load(ifstream& fin);

	virtual void Resize(Point, int);

	virtual Point GetCorner(int);

	virtual int IsACorner(Point);

	virtual void DistanceFromCenter(Point, double &DIFFx, double& DIFFy);
	virtual Point GetCenter();

	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar

};

