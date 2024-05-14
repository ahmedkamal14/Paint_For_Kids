#include "switchToDrawAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"

switchToDrawAction::switchToDrawAction(ApplicationManager* app) :Action(app)
{
}

void switchToDrawAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	pOut->ClearDrawArea();
	pOut->ClearPlayToolBar();
	pOut->CreateDrawToolBar();

	pManager->resetPlayList();

	pOut->PrintMessage("You switched back to Draw mode, original drawing restored ");
}

void switchToDrawAction::Execute()
{
	ReadActionParameters();
}
