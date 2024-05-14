#include "ResizeAction.h"
#include "Action.h"
#include "../Figures/CCircle.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../GUI/UI_Info.h"
ResizeAction::ResizeAction(ApplicationManager* pApp):Action(pApp)
{
	IsDone = true;
}

void ResizeAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click on the vertex of the selected figure to resize");
	//Read the point and stores it in p
	pIn->GetPointClicked(P.x, P.y);
	//if the click was on the tool/status bar the action will be ignored
	if (P.y <= UI.ToolBarHeight + UI.ToolBarBorderWidth && P.y >= UI.height - UI.StatusBarHeight)
		IsDone = false;
}

void ResizeAction::Execute()
{
	ReadActionParameters();
	if (IsDone) {
		CFigure* FIG = pManager->GetSelectedFigure();
		Output* pOut = pManager->GetOutput();
		if (FIG) {
			Input* pIn = pManager->GetInput();
			num = FIG->IsACorner(P);
			if (num != -1) {
				P = FIG->GetCorner(num);
				ID = FIG->GetID();
				Point pTemp;
				while (pIn->GetMouseClick(pTemp.x, pTemp.y) == NO_CLICK) {
					pIn->GetMouseCoordinates(pTemp.x, pTemp.y);
					FIG->Resize(pTemp,num);
					Pause(10);
					pManager->UpdateInterface();
				}
				P2 =  FIG->GetCorner(num);
				pManager->SetSelectedFigure(NULL);
				FIG->SetSelected(false);
				// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
				if (pManager->IsRecording()) {
					ResizeAction* ReAction = new ResizeAction(pManager);
					*ReAction = *this;
					pManager->AddActionToRecordingList(ReAction);
				}
				pManager->GetOutput()->ClearStatusBar();
				pManager->DeleteRedoList();
			}
			else {
				pOut->PrintMessage("You didn't choose a corner. Try again");
				IsDone = false;
			}
		}
		else {
			pOut->PrintMessage("Please select a figure first");
			IsDone = false;
		}
	}
}

bool ResizeAction::CanUndo()
{
	return IsDone;
}

void ResizeAction::Undo()
{
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		FIG->Resize(P,num);
	}
}

void ResizeAction::Redo()
{
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		FIG->Resize(P2,num);
	}
}

void ResizeAction::PlayRecording()
{
	CFigure* figure = pManager->GetSelectedFigure();
	if (figure) {
		pManager->SetSelectedFigure(NULL);
		figure->SetSelected(false);
		figure->Resize(P2, num);
		ResizeAction* ReAction = new ResizeAction(pManager);
		*ReAction = *this;
		pManager->AddToUndoList(ReAction);
		pManager->DeleteRedoList();
	}
}
