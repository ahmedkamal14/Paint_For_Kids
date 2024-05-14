#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	DRAW_HEXA,		
	DRAW_SQUARE,	
	DRAW_TRIANGLE,  
	DRAW_CIRCLE,    
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	SELECT_SHAPE,    
	CHANGE_BORDERCLR,
	CHANGE_FILLCLR, 
	RESIZE,
	MOVEBYDRAGGING,
	//color list
	CHNGCLR_BLACK,
	CHNGCLR_YELLOW,
	CHNGCLR_ORANGE,
	CHNGCLR_RED,
	CHNGCLR_GREEN,
	CHNGCLR_BLUE,
	//


	PickHideGame,
	PLAYBYSHAPE,
	PLAYBYCOLOR,
	PLAYBYBOTH,
	PLAYINGAREA,
	DELETE_FIGURE, 
	MOVE_FIGURE, 
	UNDO,
	REDO,
	CLEAR_ALL,
	START_RECORDING,
	STOP_RECORDING,
	PLAY_RECORDING,
	SAVE_GRAPH,
	LOAD_GRAPH,
	MUTE_SOUND
///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif