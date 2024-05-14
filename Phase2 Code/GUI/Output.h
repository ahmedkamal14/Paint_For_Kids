#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	
public:
	Output();		
	
	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreatePickHideToolBar() const; // creates the tool bar to show the types of pick and hide game 
	void CreateStatusBar() const;	//create the status bar
	void CreateColorlist() const;

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearDrawToolBar() const; // clears the draw tool bar 
	void ClearPlayToolBar() const; // clears the play tool bar 
	void ClearColorListToolBar() const;
	void ClearPickHideToolBar() const;
	void createToolBarWithSound() const;
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawSquare(Point P, GfxInfo RectGfxInfo, bool selected = false, int length = 100) const;  // Draw a Square
	void DrawHexa(Point P, GfxInfo RectGfxInfo, bool selected = false, int length = 100) const;  //  Draw a Hexagon
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected);//Draw a Triangle
	void DrawCircle(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected);//Draw a Circle
	
	///Make similar functions for drawing all other figure types.
	//
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void setDrawclr(color);
	void setFillclr(color);
	void setfilled();
	void SetNonFilled();
	bool checkisfilled();
	
	~Output();
};

#endif