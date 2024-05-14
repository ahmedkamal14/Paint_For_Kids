#pragma once
#include "Action.h"
class StartRecordingAction : public Action
{
	int RecordedActionsIndex = 0;
public:
	StartRecordingAction(ApplicationManager* pApp);

	bool RecordingCanBeEnabled();

	virtual void ReadActionParameters();

	virtual void Execute();
	
};

