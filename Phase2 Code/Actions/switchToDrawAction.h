#pragma once
#include "Action.h"
class switchToDrawAction : public Action
{

public :
	switchToDrawAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
};

