#include "SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"

SelectAction::SelectAction(ApplicationManager* pApp): Action(pApp) 
{
}
void SelectAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select figure: Click on the figure you want to select");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}
void SelectAction::Execute() {
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	CFigure* fig, * fig2; //A pointer to figure class
	fig = pManager->GetFigure(P.x, P.y);//sets the fig data member to the pointer of the selected figure
	if (fig) {// made to eliminate the possibility of calling a member function of a NULL pointer
		if (fig->IsSelected()) {
			fig->SetSelected(false);
			pManager->SetSelectedFigure(NULL);
			pOut->ClearStatusBar();
		}
		else {//sees the previous selected figure and unselect it then select the required figure
			fig2 = pManager->GetSelectedFigure();
			if (fig2) {
				fig2->SetSelected(false);
				pOut->ClearStatusBar();
			}
			pManager->SetSelectedFigure(fig);
			fig->SetSelected(true);
			fig->PrintInfo(pOut);
		}
	}

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		SelectAction* sAction = new SelectAction(pManager);
		*sAction = *this;
		pManager->AddActionToRecordingList(sAction);
	}
}

void SelectAction::PlayRecording()
{
	CFigure* fig, * fig2; //A pointer to figure class
	fig = pManager->GetFigure(P.x, P.y);//sets the fig data member to the pointer of the selected figure
	if (fig) {// made to eliminate the possibility of calling a member function of a NULL pointer
		if (fig->IsSelected()) {
			fig->SetSelected(false);
			pManager->SetSelectedFigure(NULL);
		}
		else {//sees the previous selected figure and unselect it then select the required figure
			fig2 = pManager->GetSelectedFigure();
			if (fig2) {
				fig2->SetSelected(false);
			}
			pManager->SetSelectedFigure(fig);
			fig->SetSelected(true);
		}
	}
}
