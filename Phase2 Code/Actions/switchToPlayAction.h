#pragma once
#include "Action.h"
class switchToPlayAction : public Action
{

public : 
	switchToPlayAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
};

