#pragma once
#include "Action.h"
class MoveByDraggingAction :
    public Action
{
	Point P, PB;
	bool IsReady;
	int ID;
public:
	MoveByDraggingAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual bool CanUndo() { return IsReady; }
	virtual void PlayRecording();
};

