#include "CFigure.h"

CFigure::CFigure()
{
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	isFilled = false;

}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

void CFigure::RemoveFillClr(color PrevClr)
{
	FigGfxInfo.isFilled = false;
	isFilled = false;
	FigGfxInfo.FillClr = PrevClr;
}

GfxInfo CFigure::getGfxInfo()
{
	return FigGfxInfo;
}
void CFigure::SetGfxinfo(GfxInfo info)
{
	FigGfxInfo = info;
}

color CFigure::getDrawColor()
{
	return FigGfxInfo.DrawClr;
}
color CFigure::getFillColor()
{
	return FigGfxInfo.FillClr;
}
void CFigure::SetID(int id)
{
	ID = id;
}

int CFigure::GetID() const
{
	return ID;
}

bool CFigure::getFillStats()
{
	return isFilled;
}

