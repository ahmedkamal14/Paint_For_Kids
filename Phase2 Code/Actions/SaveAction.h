#pragma once
#include <iostream>
#include <string.h>
#include "Action.h"
using namespace std;
class SaveAction:public Action
{
	string File_Name;
public:
	SaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	void setFileName(string name);
	
};

