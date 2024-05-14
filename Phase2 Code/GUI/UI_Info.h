#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu
	ITM_SQUARE, 
	ITM_HEXA, 
	ITM_TRIANGLE,
	ITM_CIRCLE, 
	//TODO: Add more items names here
	SELECT_ONE,
	RESIZE_ICON,
	BORDER_COLOR, 
	FILL_COLOR,
	
	TOPLAYM,

	DELETE_FIG_ICON,
	
	MOVEFIG_ICON, 
	MOVEBYDRAG_ICON,
	UNDO_ICON,
	REDO_ICON,
	CLEAR_ALL_ICON,
	STARTREC_ICON,
	STOPREC_ICON,
	PLAYREC_ICON,
	SAVE_ICON,
	LOAD_ICON,
	MUTE_ICON,
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};
enum COLORS_LIST_ITEMS {
	
	BLACK_ICON,
	YELLOW_ICON,
	ORANGE_ICON,
	RED_ICON,
	GREEN_ICON,
	BLUE_ICON,
	//
	COLOR_COUNT
};
enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	PICKHIDE,
	TODRAW,
	ITEM_EXIT,

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PickHideMenuItems {
	BYSHAPE,
	BYCOLOR,
	BYBOTH,

	ITEM_COUNT
};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	    //Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth,		//Width of each item in toolbar menu
		PickHideToolBarHeight,
		PickHideToolBarWidth,
		ColorListToolBarWidth,
		ColorListToolBarHeight;
	bool Is_created;// sees whether the additional tool bars are created or not;

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color SeperatingBorderColor;
	color ToolBarBorderColor;
	int PenWidth;			//width of the pen that draws shapes
	int SeperatingBorderWidth;
	int ToolBarBorderWidth;
	bool isfilled;
	/// Add more members if needed
	
}UI;	//create a global object UI

#endif