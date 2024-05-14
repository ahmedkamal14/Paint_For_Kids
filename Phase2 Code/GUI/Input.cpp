#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();
	
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
		pWind->FlushKeyQueue();
		pWind->FlushMouseQueue();
	}

	
}

clicktype Input::GetMouseClick(int&x, int&y)
{
	return pWind->GetMouseClick(x, y);

}

void Input::GetMouseCoordinates(int& x, int& y)
{
	pWind->GetMouseCoord(x, y);
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_SQUARE: return DRAW_SQUARE; 
			case ITM_HEXA: return DRAW_HEXA; 
			case ITM_TRIANGLE:return DRAW_TRIANGLE;
			case ITM_CIRCLE: return DRAW_CIRCLE;
			
			case SELECT_ONE: return SELECT_SHAPE;
			case RESIZE_ICON:return RESIZE;
			case BORDER_COLOR: return CHANGE_BORDERCLR;
			
			case FILL_COLOR: return CHANGE_FILLCLR;
			case MOVEBYDRAG_ICON: return MOVEBYDRAGGING;
			
			//
			case TOPLAYM:  return TO_PLAY;
			
		case DELETE_FIG_ICON: return DELETE_FIGURE;

			case MOVEFIG_ICON: return MOVE_FIGURE;
			case UNDO_ICON: return UNDO;
			case REDO_ICON: return REDO;
			case CLEAR_ALL_ICON: return CLEAR_ALL;
			case STARTREC_ICON: return START_RECORDING;
			case STOPREC_ICON: return STOP_RECORDING;
			case PLAYREC_ICON: return PLAY_RECORDING;
			case SAVE_ICON: return SAVE_GRAPH;
			case LOAD_ICON: return LOAD_GRAPH;
			case MUTE_ICON: return MUTE_SOUND;
			case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		if (y >= UI.ToolBarHeight && y < UI.ColorListToolBarHeight && x <= UI.ColorListToolBarWidth && UI.Is_created){//added is_created to prevent wrong actions from being interpreted

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{

			case BLACK_ICON: return CHNGCLR_BLACK;

			case YELLOW_ICON: return CHNGCLR_YELLOW;

			case ORANGE_ICON: return CHNGCLR_ORANGE;

			case RED_ICON: return CHNGCLR_RED;

			case GREEN_ICON: return CHNGCLR_GREEN;

			case BLUE_ICON: return CHNGCLR_BLUE;

			default: return EMPTY;

			}
		}
			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				return DRAWING_AREA;
			}

			//[3] User clicks on the status bar
			return STATUS;
		}
	
	else	//GUI is in PLAY mode   // (input for the play mode)  ##########################
	{
		///TODO:
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{

			case PICKHIDE:  return PickHideGame;

			case TODRAW: return TO_DRAW;

			case ITEM_EXIT : return EXIT;

			default: return EMPTY;
				
			}
		}


		if (y >= UI.ToolBarHeight && y < UI.PickHideToolBarHeight && x <= UI.PickHideToolBarWidth && UI.Is_created) {
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{

			case BYSHAPE: return PLAYBYSHAPE;

			case BYCOLOR:return PLAYBYCOLOR;

			case BYBOTH: return PLAYBYBOTH;

			default: return EMPTY;
				
			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYINGAREA;
		}
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
