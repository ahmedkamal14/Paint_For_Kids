#include "ChangeFillClrAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
ChangeFillClrAction::ChangeFillClrAction(ApplicationManager* pApp, color FC) :Action(pApp)
{
	FillingClr = FC; 
}

void ChangeFillClrAction::ReadActionParameters()
{
}

void ChangeFillClrAction::Execute()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetSelectedFigure();
	if (FIG) {
		PrevDefault.isFilled = op->checkisfilled();
		PrevDefault.DrawClr = op->getCrntDrawColor();
		PrevDefault.FillClr = op->getCrntFillColor();
		PrevDefault.BorderWdth = op->getCrntPenWidth();
		op->setfilled();
		PrevFillingClr = FIG->getGfxInfo();
		ID = FIG->GetID();
		op->setFillclr(FillingClr); //Setting The Fill Color With The One Chosen By User
		FIG->ChngFillClr(FillingClr);
		FIG->SetSelected(false); //Making The Figure Unselected
		pManager->SetSelectedFigure(NULL);
		op->ClearStatusBar();
	}

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		ChangeFillClrAction* ChangeColorAction = new ChangeFillClrAction(pManager, FillingClr);
		*ChangeColorAction = *this;
		pManager->AddActionToRecordingList(ChangeColorAction);
	}
}

void ChangeFillClrAction::PlayRecording()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetSelectedFigure();
	if (FIG) {
	
		op->setfilled();
		op->setFillclr(FillingClr);
		FIG->ChngFillClr(FillingClr);
		FIG->SetSelected(false);
		pManager->SetSelectedFigure(NULL);
	}
	ChangeFillClrAction* ChangeColorAction = new ChangeFillClrAction(pManager, FillingClr);
	*ChangeColorAction = *this;
	pManager->AddToUndoList(ChangeColorAction);
}


void ChangeFillClrAction::Undo()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		if (PrevDefault.isFilled)
			op->setfilled();
		else
			op->SetNonFilled();
		FIG->SetGfxinfo(PrevFillingClr);
		FIG->SetSelected(false);
		op->setFillclr(PrevDefault.FillClr);
		op->setDrawclr(PrevDefault.DrawClr);
		pManager->SetSelectedFigure(NULL);
	}
}

void ChangeFillClrAction::Redo()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		ID = FIG->GetID();
		op->setfilled();
		op->setFillclr(FillingClr);
		FIG->ChngFillClr(FillingClr);
		FIG->SetSelected(false);

		pManager->SetSelectedFigure(NULL);
	}
}


bool ChangeFillClrAction::CanUndo()
{
	return true;
}

