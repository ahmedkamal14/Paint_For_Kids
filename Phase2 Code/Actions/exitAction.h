#pragma once
#include "Action.h"

class exitAction: public Action
{

public:

	exitAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();

};

