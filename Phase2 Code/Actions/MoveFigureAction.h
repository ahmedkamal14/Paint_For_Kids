#pragma once
#include "Action.h"
class MoveFigureAction :
    public Action
{
	Point P,PB;
	bool IsReady; // Variable to validate the ability to move the figure (if it comes over the bars then it won't be moved)
	int ID;
public:
	MoveFigureAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual bool CanUndo() { return IsReady; }
	virtual void PlayRecording();

};

