#pragma once
#include "..\ApplicationManager.h"
#include "Action.h"
class muteAction : public Action
{
public:

	muteAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
};

