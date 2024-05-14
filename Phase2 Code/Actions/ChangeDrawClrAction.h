#pragma once
#include "Action.h"
#include "..\GUI\UI_Info.h"
#include "..\GUI\Input.h"
class ChangeDrawClrAction :public Action
{
	color DrawingClr, PrevDrawingClr;
	GfxInfo PrevDefault;
	int ID;
public:
	ChangeDrawClrAction(ApplicationManager* pApp, color DC);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void PlayRecording();
	virtual bool CanUndo();
	virtual void Undo();
	virtual void Redo();

};

