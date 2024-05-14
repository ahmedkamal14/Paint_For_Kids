#pragma once
#include "Action.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

class playByColorAction : public Action
{
	int correct, wrong, numOfShapes, fillCount;
	int blackCount, yellowCount, orangeCount, redCount, greenCount, blueCount;
	Point p;
	color randColor;
	Output* pOut;
	Input* pIn;



public:

	playByColorAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
	void startGame();
	virtual bool CanUndo() { return false; }
	virtual void Undo() {}
	virtual void Redo() {}

};


