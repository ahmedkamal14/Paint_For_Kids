#include "pickHideAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"

pickHideAction::pickHideAction(ApplicationManager* app):Action(app)
{

}

void pickHideAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Choose the mode you want to play  ");

	pOut->CreatePickHideToolBar();
	
}

void pickHideAction::Execute()
{
	ReadActionParameters();
}
