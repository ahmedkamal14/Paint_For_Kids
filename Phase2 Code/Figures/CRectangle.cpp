#include "CRectangle.h"
#include <fstream>
CRectangle::CRectangle()
{
}
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
bool CRectangle::IsInside(int x, int y) const {
	//get the max and min x value
	int x_min;
	int x_max;
	if (Corner1.x > Corner2.x)
	{
		x_max = Corner1.x;
		x_min = Corner2.x;
	}
	else {
		x_max = Corner2.x;
		x_min = Corner1.x;
	}
	//get the max and min y value
	int y_min;
	int y_max;
	if (Corner1.y > Corner2.y)
	{
		y_max = Corner1.y;
		y_min = Corner2.y;
	}
	else {
		y_max = Corner2.y;
		y_min = Corner1.y;
	}
	if (y >= y_min && y <= y_max && x >= x_min && x <= x_max) // sees whether the point is inside it or not
		return 1;
	return 0;
}

Point CRectangle::MoveFigure(Point move) {
	Point c, P1, P2;
	c.x = (Corner1.x + Corner2.x) / 2;
	c.y = (Corner1.y + Corner2.y) / 2;

	int xDiff = move.x - c.x;
	int yDiff = move.y - c.y;

	P1.y = Corner1.y + yDiff;
	P2.y = Corner2.y + yDiff;

	// Checks if it will be drawn over any of two bars or not
	// if it won't be drawn over the bars it will be moved
	if  (
		P1.y < UI.ToolBarHeight + UI.ToolBarBorderWidth 
		|| P2.y < UI.ToolBarHeight + UI.ToolBarBorderWidth 
		|| P1.y > UI.height - UI.StatusBarHeight 
		|| P2.y > UI.height - UI.StatusBarHeight
		)
	{
		Point T;
		T.x = -1;
		T.y = -1;
		return T;
	}
	else {
		Corner1.x += xDiff;
		Corner1.y += yDiff;

		Corner2.x += xDiff;
		Corner2.y += yDiff;
		return c;
	}
}

void CRectangle::save(ofstream& fout)
{
	/*Saving NAME & ID & CORNER POINTS*/
	fout << "RECT" << " \t\t" << ID << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t";

	/*Saving The Drawing Color*/
	if (FigGfxInfo.DrawClr == BLACK) fout << "BLACK" << "\t";
	else if (FigGfxInfo.DrawClr == BLUE) fout << "BLUE" << "\t";
	else if (FigGfxInfo.DrawClr == RED) fout << "RED" << "\t";
	else if (FigGfxInfo.DrawClr == GREEN) fout << "GREEN" << "\t";
	else if (FigGfxInfo.DrawClr == YELLOW) fout << "YELLOW" << "\t";
	else if (FigGfxInfo.DrawClr == ORANGE) fout << "ORANGE" << "\t";

	/*Checking If The Figure Is Filled Then Saving The Fill Color*/
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

void CRectangle::load(ifstream& fin)
{
	string drawclr, fillclr;
	/*Loading The ID & CORNER POINTS & COLORS*/
	fin >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> drawclr >> fillclr;

	/*Setting The Drawing Color*/
	if (drawclr == "BLACK") { FigGfxInfo.DrawClr = BLACK; }
	else if (drawclr == "BLUE") { FigGfxInfo.DrawClr = BLUE; }
	else if (drawclr == "RED") { FigGfxInfo.DrawClr = RED; }
	else if (drawclr == "ORANGE") { FigGfxInfo.DrawClr = ORANGE; }
	else if (drawclr == "YELLOW") { FigGfxInfo.DrawClr = YELLOW; }
	else if (drawclr == "GREEN") { FigGfxInfo.DrawClr = GREEN; }

	/*Checking If The Figure Is Filled Then Setting The Fill Color*/
	if (fillclr == "NOT_FILLED") { 
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = NULL;
	}
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

void CRectangle::Resize(Point P, int num)
{
	if (P.y > UI.ToolBarHeight + UI.ToolBarBorderWidth && P.y < UI.height - UI.StatusBarHeight) {
		if (num == 1) {
			if (abs(P.x-Corner2.x)>2 && abs(P.y-Corner2.y)>2)
			Corner1 = P;
		}
		else if (num == 2) {
			if (abs(P.x - Corner1.x)>2 && abs(P.y - Corner1.y)>2)
			Corner2 = P;
		}
	}
}

Point CRectangle::GetCorner(int n)
{
	if(n==1)
	return Corner1;
	return Corner2;
}

int CRectangle::IsACorner(Point point)
{
	if (abs(point.x - Corner1.x) <= 5) {

		if (abs(point.y - Corner1.y) <= 5) {
			return 1;
		}
		else if (abs(point.y - Corner2.y) <= 5) {
			swap(Corner1.y, Corner2.y);
			return 1;
		}
	}
	else if (abs(point.x - Corner2.x) <= 5) {

		if (abs(point.y - Corner2.y) <= 5) {
			return 2;
		}
		else if (abs(point.y - Corner1.y) <= 5) {
			swap(Corner1.y, Corner2.y);
			return 2;
		}
	}
	return -1;
}



void CRectangle::DistanceFromCenter(Point P, double& DIFFx, double& DIFFy)
{
	DIFFx = double((Corner1.x+Corner2.x)/2.0 - P.x);
	DIFFy = double((Corner1.y + Corner2.y) / 2.0 - P.y);
}

Point CRectangle::GetCenter()
{
	Point pTemp;
	pTemp.x = (Corner1.x + Corner2.x)/2;
	pTemp.y = (Corner1.y + Corner2.y)/2;
	return pTemp;
}

void CRectangle::PrintInfo(Output* pOut)
{
	int width = abs(Corner1.x - Corner2.x);
	int height = abs(Corner1.y - Corner2.y);
	pOut->PrintMessage("Sleceted A Rectangle, ID: " + to_string(ID) + "| Start Point: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ") | End Point: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ") | Width: " + to_string(width) + " | Height: " + to_string(height));
}

