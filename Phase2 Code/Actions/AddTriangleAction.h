#pragma once
#include "Action.h"
class AddTriangleAction :
    public Action
{
private: Point P1, P2, P3;
       GfxInfo TriangleGfxInfo;
	   int ID;
	   bool CanDraw;  // Variable to validate the ability to draw the figure (if it comes over the bars then it won't be drawn)
public:
    AddTriangleAction(ApplicationManager*);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual void Undo();

	virtual void Redo();
 
	virtual bool CanUndo() { return CanDraw; }

	virtual void PlayRecording();

};

