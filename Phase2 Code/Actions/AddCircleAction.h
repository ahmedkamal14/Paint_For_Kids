#pragma once
#include "Action.h"

class AddCircleAction :public Action
{
	Point Center, P2; // Center point and another point on the circle perimeter 
	GfxInfo CircleGfxInfo;
	bool CanDraw; // Variable to validate the ability to draw the figure (if it comes over the bars then it won't be drawn)
	int ID;
public:

	AddCircleAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

	virtual bool CanUndo() { return CanDraw; }

	virtual void PlayRecording();
};

