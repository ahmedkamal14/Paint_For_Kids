#include "switchToPlayAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"

switchToPlayAction::switchToPlayAction(ApplicationManager* app):Action(app)
{

}

void switchToPlayAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	pOut->ClearDrawArea();
	pOut->ClearDrawToolBar();
	pOut->CreatePlayToolBar();

	pOut->PrintMessage("You entered Play mode, Click the icon to see available games :) ");
	
}

void switchToPlayAction::Execute()
{
	ReadActionParameters();
}

