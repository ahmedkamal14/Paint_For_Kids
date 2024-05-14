#pragma once
#include "Action.h"
class pickHideAction: public Action
{

public :

	pickHideAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
};

