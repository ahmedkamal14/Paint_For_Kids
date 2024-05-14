#include "Output.h"
#include "UI_Info.h"
#define SquareRad 50 


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;
	UI.Is_created = false;// sees whether the additional tool bars are created?
	UI.isfilled = false;
	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 54;
	UI.SeperatingBorderWidth = 2;// the width of the line between the icons
	// assigning values for pick and hide tool bar;
	UI.PickHideToolBarHeight = 2*UI.ToolBarHeight;
	UI.PickHideToolBarWidth = ITEM_COUNT*UI.MenuItemWidth;
	
	UI.ColorListToolBarHeight = 2 * UI.ToolBarHeight;
	UI.ColorListToolBarWidth = COLOR_COUNT * UI.MenuItemWidth;
	//
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = WHITESMOKE;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.ToolBarBorderColor = BLUE;
	UI.SeperatingBorderColor = BLUE;//the color of the border seperating the icons
	UI.PenWidth = 3;	//width of the figures frames
	UI.ToolBarBorderWidth=3;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\square_icon.jpg"; 
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\hexa_icon.jpg";	   
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\tri.jpg";	   
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\Menu_Circ.jpg";	   
	MenuItemImages[SELECT_ONE] = "images\\MenuItems\\Select_One.jpg"; 
	MenuItemImages[FILL_COLOR] = "images\\MenuItems\\Fill_color.jpg"; 
	MenuItemImages[BORDER_COLOR] = "images\\MenuItems\\Border_color.jpg"; 
	MenuItemImages[RESIZE_ICON] = "images\\MenuItems\\Resize.jpg";
	
	MenuItemImages[TOPLAYM] = "images\\MenuItems\\toPlay.jpg";
	///////////////////////////////////
	MenuItemImages[DELETE_FIG_ICON] = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[MOVEFIG_ICON] = "images\\MenuItems\\Move.jpg";
	MenuItemImages[UNDO_ICON] ="images\\MenuItems\\Undo.jpg";
	MenuItemImages[REDO_ICON] = "images\\MenuItems\\Redo.jpg";
	MenuItemImages[CLEAR_ALL_ICON] = "images\\MenuItems\\Clear_All.jpg";
	MenuItemImages[STARTREC_ICON] = "images\\MenuItems\\Start_Recording.jpg";
	MenuItemImages[STOPREC_ICON] = "images\\MenuItems\\Stop_Recording.jpg";
	MenuItemImages[PLAYREC_ICON] = "images\\MenuItems\\Play_Recording.jpg";
	MenuItemImages[SAVE_ICON] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[LOAD_ICON] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[MUTE_ICON] = "images\\MenuItems\\Mute.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	MenuItemImages[MOVEBYDRAG_ICON] = "images\\MenuItems\\MoveByDragIcon.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	for (int i = 0; i < DRAW_ITM_COUNT; i++) {

		pWind->SetPen(UI.SeperatingBorderColor, UI.SeperatingBorderWidth);
		pWind->DrawLine(i * UI.MenuItemWidth, 0, i * UI.MenuItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

// (Creating tool bar for the play mode)
void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[PICKHIDE] = "images\\MenuItems\\PICKHIDE.jpg";
	MenuItemImages[TODRAW] = "images\\MenuItems\\ToDraw.jpg";
	MenuItemImages[ITEM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";


	// Draw menu items  
	for (int i = 0; i < PLAY_ITM_COUNT; i++) {
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	}
	for (int i = 0; i < PLAY_ITM_COUNT; i++) {
		

		pWind->SetPen(UI.SeperatingBorderColor, UI.SeperatingBorderWidth);
		pWind->DrawLine(i * UI.MenuItemWidth, 0, i * UI.MenuItemWidth, UI.ToolBarHeight);
	}
	// Deaw a line under the tool bar 
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void Output::CreatePickHideToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	UI.Is_created = true;
	// draw to tool bar itself
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);
	
	// assign images
	string MenuItemImages[ITEM_COUNT];
	MenuItemImages[BYSHAPE] = "images\\MenuItems\\byShape.jpg";
	MenuItemImages[BYCOLOR] = "images\\MenuItems\\byColor.jpg";
	MenuItemImages[BYBOTH] = "images\\MenuItems\\byBoth.jpg";

	// draw images
	for (int i = 0; i < ITEM_COUNT; i++) {
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	for (int i = 0; i < ITEM_COUNT; i++) {
		pWind->SetPen(UI.SeperatingBorderColor, UI.SeperatingBorderWidth);
		pWind->DrawLine(i * UI.MenuItemWidth, UI.ToolBarHeight, i * UI.MenuItemWidth, UI.PickHideToolBarHeight);
	}
	// draws the line under them
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.PickHideToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateColorlist() const  {
	
	UI.InterfaceMode = MODE_DRAW;
	UI.Is_created = true;

	// draw to tool bar itself
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);
	
	// assign images
	string MenuItemImages[COLOR_COUNT];
	MenuItemImages[BLACK_ICON] = "images\\MenuItems\\Black.jpg";
	MenuItemImages[YELLOW_ICON] = "images\\MenuItems\\Yellow.jpg";
	MenuItemImages[ORANGE_ICON] = "images\\MenuItems\\Orange.jpg";
	MenuItemImages[RED_ICON] = "images\\MenuItems\\Red.jpg";
	MenuItemImages[GREEN_ICON] = "images\\MenuItems\\Green.jpg";
	MenuItemImages[BLUE_ICON] = "images\\MenuItems\\Blue.jpg";
	
	// draw images
	for (int i = 0; i < COLOR_COUNT; i++) {
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	for (int i = 0; i < COLOR_COUNT; i++) {

		pWind->SetPen(UI.SeperatingBorderColor, UI.SeperatingBorderWidth);
		pWind->DrawLine(i * UI.MenuItemWidth, UI.ToolBarHeight, i * UI.MenuItemWidth, UI.ColorListToolBarHeight);
	}
		// draws the line under them
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ColorListToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);

}
////////////////////////
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	pWind->SetPen(UI.SeperatingBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	
}
void Output::ClearDrawToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	 
		// clears the Color tool bar if exist
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);


	// draws the line seperating the bars
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.ColorListToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);
	//////////////////////////////////////////////////
	
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);

	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	UI.Is_created = false;

}
void Output::ClearColorListToolBar() const {
	UI.Is_created = false;

	
		// clears the Color tool bar if exist
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);


	// draws the line seperating the bars
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.ColorListToolBarHeight, UI.ColorListToolBarWidth, UI.ColorListToolBarHeight);
	//////////////////////////////////////////////////
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void Output::ClearPickHideToolBar() const {
	UI.Is_created = false;

	// clears the pick and hide game tool bar if exist
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);


	// draws the line seperating the bars
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.PickHideToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::createToolBarWithSound() const
{
	UI.InterfaceMode = MODE_DRAW;


	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\square_icon.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\hexa_icon.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\tri.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[SELECT_ONE] = "images\\MenuItems\\Select_One.jpg";
	MenuItemImages[FILL_COLOR] = "images\\MenuItems\\Fill_color.jpg";
	MenuItemImages[BORDER_COLOR] = "images\\MenuItems\\Border_color.jpg";
	MenuItemImages[RESIZE_ICON] = "images\\MenuItems\\Resize.jpg";

	MenuItemImages[TOPLAYM] = "images\\MenuItems\\toPlay.jpg";
	///////////////////////////////////
	MenuItemImages[DELETE_FIG_ICON] = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[MOVEFIG_ICON] = "images\\MenuItems\\Move.jpg";
	MenuItemImages[MOVEBYDRAG_ICON] = "images\\MenuItems\\MoveByDragIcon.jpg";
	MenuItemImages[UNDO_ICON] = "images\\MenuItems\\Undo.jpg";
	MenuItemImages[REDO_ICON] = "images\\MenuItems\\Redo.jpg";
	MenuItemImages[CLEAR_ALL_ICON] = "images\\MenuItems\\Clear_All.jpg";
	MenuItemImages[STARTREC_ICON] = "images\\MenuItems\\Start_Recording.jpg";
	MenuItemImages[STOPREC_ICON] = "images\\MenuItems\\Stop_Recording.jpg";
	MenuItemImages[PLAYREC_ICON] = "images\\MenuItems\\Play_Recording.jpg";
	MenuItemImages[SAVE_ICON] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[LOAD_ICON] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[MUTE_ICON] = "images\\MenuItems\\Sound.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	for (int i = 0; i < DRAW_ITM_COUNT; i++) {

		pWind->SetPen(UI.SeperatingBorderColor, UI.SeperatingBorderWidth);
		pWind->DrawLine(i * UI.MenuItemWidth, 0, i * UI.MenuItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

void Output::ClearPlayToolBar() const 
{
	// clears the play mode tool bar 
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	
	UI.Is_created = false;


	// clears the pick and hide game tool bar if exist
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);


	// draws the line seperating the bars
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.PickHideToolBarHeight, UI.PickHideToolBarWidth, UI.PickHideToolBarHeight);

	pWind->SetPen(UI.ToolBarBorderColor, UI.ToolBarBorderWidth);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

void Output::setDrawclr(color C)
{
	UI.DrawColor = C;
}

void Output::setFillclr(color C)
{
	UI.FillColor = C;
}

void Output::setfilled()
{
	UI.isfilled = true;
}

void Output::SetNonFilled() {
	UI.isfilled = false;
}

bool Output::checkisfilled()
{
	return UI.isfilled;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,2);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	/*
	if (P1.y < UI.ToolBarHeight) {
		P1.y = UI.ToolBarHeight + UI.ToolBarBorderWidth;
	}
	if (P2.y < UI.ToolBarHeight) {
		P2.y = UI.ToolBarHeight + UI.ToolBarBorderWidth;
	}
	*/
	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawSquare(Point P, GfxInfo RectGfxInfo, bool selected, int length) const // Square Function
{
	int x1 = P.x - length / 2, x2 = P.x + length / 2, y1 = P.y + length / 2, y2 = P.y - length / 2;   
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 2);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	/*
	if (y1 < UI.ToolBarHeight) {
		y1 = UI.ToolBarHeight;
	}

	if (y2 < UI.ToolBarHeight) {
		y2 = UI.ToolBarHeight + UI.ToolBarBorderWidth;
	}
	*/


	pWind->DrawRectangle(x1, y1, x2, y2, style);

}

void Output::DrawHexa(Point P, GfxInfo RectGfxInfo, bool selected, int length) const // Hexagon Function
{
	const int vertices = 6;
	int X[vertices];
	int Y[vertices];

	// The Length Of The Hexagonal Is 100

	X[0] = P.x;
	X[1] = P.x + length * 0.866;
	X[2] = P.x + length * 0.866;
	X[3] = P.x;
	X[4] = P.x - length * 0.866;
	X[5] = P.x - length * 0.866;

	Y[0] = P.y + length;
	Y[1] = P.y + length / 2;
	Y[2] = P.y - length / 2;
	Y[3] = P.y - length;
	Y[4] = P.y - length / 2;
	Y[5] = P.y + length / 2;

	/*
	for (int i = 0; i < vertices; i++) {
		if (Y[i] < UI.ToolBarHeight) {
			Y[i] = UI.ToolBarHeight + UI.ToolBarBorderWidth;
		}
	}
	*/



	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 2);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawPolygon(X, Y, vertices, style);

}

void Output::DrawCircle(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected)
{
	if (P1.y > (UI.ToolBarHeight + UI.ToolBarBorderWidth)) {
		int radius;
		int lenx = P1.x - P2.x;
		int leny = P1.y - P2.y;
		radius = sqrt((lenx * lenx) + (leny * leny));
		/*
		if (P1.y <= UI.height) {
			if (radius > P1.y - (UI.ToolBarHeight + UI.ToolBarBorderWidth)) { radius = P1.y - (UI.ToolBarHeight + UI.ToolBarBorderWidth); }
		}
		else { if (radius > UI.height - (P1.y + UI.StatusBarHeight)) { radius = UI.height - (P1.y + UI.StatusBarHeight + UI.ToolBarBorderWidth); } }
		*/
		color DrawingClr;

		if (selected)
			DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted 
		else
			DrawingClr = RectGfxInfo.DrawClr;

		pWind->SetPen(DrawingClr, 2);
		drawstyle style;
		if (RectGfxInfo.isFilled)
		{
			style = FILLED;
			pWind->SetBrush(RectGfxInfo.FillClr);
		}
		else
			style = FRAME;
		pWind->DrawCircle(P1.x, P1.y, radius, style);
	}
}
void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected)
{

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted 
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 2);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

