#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "Action.h"

//Add Rectangle Action class
class AddRectAction: public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	int ID;
	bool CanDraw; // Variable to validate the ability to draw the figure (if it comes over the bars then it won't be drawn)
public:
	AddRectAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual void Redo();

	virtual bool CanUndo() { return CanDraw; }

	virtual void PlayRecording();

};

#endif