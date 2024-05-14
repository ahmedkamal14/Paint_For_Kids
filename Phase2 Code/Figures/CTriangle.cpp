#include "CTriangle.h"
#include <cmath>
#include <fstream>




CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo FigureGfxInfo): CFigure(FigureGfxInfo) {
	Corner1 = p1;
	Corner2 = p2;
	Corner3 = p3;
}

CTriangle::CTriangle()
{
}
void CTriangle::Draw(Output* pOut) const {
	pOut->DrawTriangle(Corner1,Corner2,Corner3,FigGfxInfo,Selected);
}

	double TriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)//REQUIRED TO COMPUTE WHETHER THE POINT IS INSIDE THE TRIANGLE
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}


bool CTriangle::IsInside(int x, int y)const {
	
	double A = TriangleArea(Corner1.x, Corner1.y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);


	double A1 = TriangleArea(x, y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);

	
	double A2 = TriangleArea(Corner1.x, Corner1.y, x, y, Corner3.x, Corner3.y);

	
	double A3 = TriangleArea(Corner1.x, Corner1.y, Corner2.x, Corner2.y, x, y);

	/* Check if sum of A1, A2 and A3 is same as A */
	if (A != 0) {
		return ( std::abs(A - (A1 + A2 + A3)) < DBL_EPSILON);
	}
	else {//if the three points are collinear the previous line won't be enough to tell if the point is inside or not
		int x_min;
		int y_min;
		int x_max;
		int y_max;
		//the following code get the max and min x
		if (Corner1.x > Corner2.x)
		{
			x_max = Corner1.x;
			x_min = Corner2.x;
		}
		else {
			x_max = Corner2.x;
			x_min = Corner1.x;
		}
		if (Corner3.x > x_max) {
			x_max = Corner3.x;
		}
		else if (Corner3.x < x_min) {
			x_min = Corner3.x;
		}
		//the following code get the max and min y
		if (Corner1.y > Corner2.y)
		{
			y_max = Corner1.y;
			y_min = Corner2.y;
		}
		else {
			y_max = Corner2.y;
			y_min = Corner1.y;
		}
		if (Corner3.y > y_max) {
			y_max = Corner3.y;
		}
		else if (Corner3.y < y_min) {
			y_min = Corner3.y;
		}
		if (y >= y_min && y <= y_max && x >= x_min && x <= x_max) // sees whether the point is inside it or not
			return 1;
		return 0;
	}

	}

Point CTriangle::MoveFigure(Point move) {
	Point c, P1, P2, P3;
	c.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	c.y = (Corner1.y + Corner2.y + Corner3.y) / 3;

	int xDiff = move.x - c.x;
	int yDiff = move.y - c.y;

	P1.y = Corner1.y + yDiff;
	P2.y = Corner2.y + yDiff;
	P3.y = Corner3.y + yDiff;

	// Gets The Maximum And The Minimum Y Coordinate To Use Them In Validation
	int MinY = P1.y;
	int MaxY = P1.y;

	if (P1.y > P2.y) {
		if (P1.y > P3.y) {
			MaxY = P1.y;
		}
		else {
			MaxY = P3.y;
		}
		if (P2.y < P3.y) {
			MinY = P2.y;
		}
		else {
			MinY = P3.y;
		}
	}
	else {
		if (P2.y > P3.y) {
			MaxY = P2.y;
		}
		else {
			MaxY = P3.y;
		}
		if (P1.y < P3.y) {
			MinY = P1.y;
		}
		else {
			MinY = P3.y;
		}
	}

	// Checks if it will be drawn over any of two bars or not
	// if it won't be drawn over the bars it will be moved
	if (MinY < UI.ToolBarHeight + UI.ToolBarBorderWidth || MaxY > UI.height - UI.StatusBarHeight) {
		Point t;
		t.x = -1;
		t.y = -1;
		return t;
	}
	else {

		Corner1.x += xDiff;
		Corner1.y += yDiff;

		Corner2.x += xDiff;
		Corner2.y += yDiff;

		Corner3.x += xDiff;
		Corner3.y += yDiff;
		return c;
	}
}

void CTriangle::save(ofstream& fout)
{

	/*Saving NAME & ID & CORNER POINTS*/
	fout << "TRIANGLE" << "\t" << ID << "  \t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << Corner3.x << "\t" << Corner3.y << "\t";
	
	/*Saving The Drawing Color*/
	if (FigGfxInfo.DrawClr == BLACK) fout << "BLACK" << "\t";
	else if (FigGfxInfo.DrawClr == BLUE) fout << "BLUE" << "\t";
	else if (FigGfxInfo.DrawClr == RED) fout << "RED" << "\t";
	else if (FigGfxInfo.DrawClr == GREEN) fout << "GREEN" << "\t";
	else if (FigGfxInfo.DrawClr == YELLOW) fout << "YELLOW" << "\t";
	else if (FigGfxInfo.DrawClr == ORANGE) fout << "ORANGE" << "\t";

	/*Checking If The Figure IS Fiiled Then Saving The Fill Color*/
	if (FigGfxInfo.isFilled == true) {
		if (FigGfxInfo.FillClr == BLACK) fout << "BLACK" << "\n";
		else if (FigGfxInfo.FillClr == BLUE) fout << "BLUE" << "\n";
		else if (FigGfxInfo.FillClr == RED) fout << "RED" << "\n";
		else if (FigGfxInfo.FillClr == GREEN) fout << "GREEN" << "\n";
		else if (FigGfxInfo.FillClr == YELLOW) fout << "YELLOW" << "\n";
		else if (FigGfxInfo.FillClr == ORANGE)fout << "ORANGE" << "\n";
	}
	else { fout << "NOT_FILLED" << endl; }
}

void CTriangle::load(ifstream& fin)
{
	string drawclr, fillclr;

	/*Loading ID & CORNER POINTS & COLORS*/
	fin >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y >> drawclr >> fillclr;

	/*Setting The Drawing Color*/
	if (drawclr == "BLACK") { FigGfxInfo.DrawClr = BLACK; }
	else if (drawclr == "BLUE") { FigGfxInfo.DrawClr = BLUE; }
	else if (drawclr == "RED") { FigGfxInfo.DrawClr = RED; }
	else if (drawclr == "ORANGE") { FigGfxInfo.DrawClr = ORANGE; }
	else if (drawclr == "YELLOW") { FigGfxInfo.DrawClr = YELLOW; }
	else if (drawclr == "GREEN") { FigGfxInfo.DrawClr = GREEN; }

	/*Checking If The Figure Is Filled Then Setting The Fill Color*/
	if (fillclr == "NOT_FILLED") { FigGfxInfo.FillClr = NULL; FigGfxInfo.isFilled = false; }
	else {
		FigGfxInfo.isFilled = true;
		if (fillclr == "BLACK") { FigGfxInfo.FillClr = BLACK; }
		else if (fillclr == "BLUE") { FigGfxInfo.FillClr = BLUE; }
		else if (fillclr == "RED") { FigGfxInfo.FillClr = RED; }
		else if (fillclr == "ORANGE") { FigGfxInfo.FillClr = ORANGE; }
		else if (fillclr == "YELLOW") { FigGfxInfo.FillClr = YELLOW; }
		else if (fillclr == "GREEN") { FigGfxInfo.FillClr = GREEN; }
	}
}

void CTriangle::Resize(Point P, int num)
{
	if (P.y > UI.ToolBarHeight + UI.ToolBarBorderWidth && P.y < UI.height - UI.StatusBarHeight) {
		if (num == 1) {
		if(TriangleArea(P.x,P.y,Corner2.x,Corner2.y,Corner3.x,Corner3.y)>=2)
			Corner1 = P;
		}
		else if (num == 2) {
			if (TriangleArea(P.x, P.y, Corner1.x, Corner1.y, Corner3.x, Corner3.y)>=2)
			Corner2 = P;
		}
		else if (num == 3) {
			if (TriangleArea(P.x, P.y, Corner2.x, Corner2.y, Corner1.x, Corner1.y)>=2)
			Corner3 = P;
		}
	}
}

int CTriangle::IsACorner(Point P)
{
	if (std::abs(P.x - Corner1.x) <= 5 && std::abs(P.y - Corner1.y) <= 5) {
		return 1;

	}
	 if (std::abs(P.x - Corner2.x)<=5 && std::abs(P.y - Corner2.y) <= 5) {
		 return 2;
	}
	 if (std::abs(P.x - Corner3.x) <= 5 && std::abs(P.y - Corner3.y) <= 5) {
		return 3;
	}
	 return -1;
}

Point CTriangle::GetCorner(int n)
{
	if (n == 1)
		return Corner1;
	if (n == 2)
		return Corner2;
	return Corner3;
}

Point CTriangle::GetCenter()
{
	Point pTemp;
	pTemp.x = (Corner1.x + Corner2.x + Corner3.x)/3;
	pTemp.y = (Corner1.y + Corner2.y + Corner3.y)/3;
	return pTemp;
}

void CTriangle::DistanceFromCenter(Point P, double& DIFFx, double& DIFFy)
{
	DIFFx = double((Corner1.x + Corner2.x+Corner3.x) / 3.0 - P.x);
	DIFFy = double((Corner1.y + Corner2.y+Corner3.y) / 3.0 - P.y);
}

void CTriangle::PrintInfo(Output* pOut)
{
	pOut->PrintMessage("Seleced A Triangle, ID: " + to_string(ID) + " | First Vertex: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ") | Second Vertex: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ") | Third Vertex: (" + to_string(Corner3.x) + "," + to_string(Corner3.y) + ")");
}
