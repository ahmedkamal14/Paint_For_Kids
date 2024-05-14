#pragma once
#include "Action.h"
class PlayRecordingAction :
	public Action
{
	bool CanPlay; // Validation variable to check the current status if it can play the record
public:
	PlayRecordingAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
};

