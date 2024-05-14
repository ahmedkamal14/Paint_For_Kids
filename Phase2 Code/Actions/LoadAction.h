#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class LoadAction :public Action
{
	string FileName;
public:
	LoadAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); 
	virtual void Execute(); 
};

