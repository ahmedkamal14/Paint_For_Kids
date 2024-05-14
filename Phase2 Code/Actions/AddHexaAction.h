#pragma once
#include "Action.h"
class AddHexaAction :
    public Action
{
private:
	Point Center; 
	GfxInfo HexaGfxInfo;
	bool CanDraw; // Variable to validate the ability to draw the figure (if it comes over the bars then it won't be drawn)
	int ID;
	int length; // A variable to use when resizing
public:
	AddHexaAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

	virtual bool CanUndo() { return CanDraw; }

	virtual void PlayRecording();
};

