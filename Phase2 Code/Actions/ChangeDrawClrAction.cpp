#include "ChangeDrawClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI/UI_Info.h"
ChangeDrawClrAction::ChangeDrawClrAction(ApplicationManager* pApp, color DC) : Action(pApp)
{
	DrawingClr = DC;
}

void ChangeDrawClrAction::ReadActionParameters()
{
}

void ChangeDrawClrAction::Execute()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetSelectedFigure();
	if (FIG) {
		PrevDefault.isFilled = op->checkisfilled();
		PrevDefault.DrawClr = op->getCrntDrawColor();
		PrevDefault.FillClr = op->getCrntFillColor();
		PrevDefault.BorderWdth = op->getCrntPenWidth();
		PrevDrawingClr=FIG->getDrawColor();
		ID = FIG->GetID();
		op->setDrawclr(DrawingClr); //SettinG The Drawing Color Chosen By User
		FIG->ChngDrawClr(DrawingClr); 
		FIG->SetSelected(false); //Make The Figure Unselected
		pManager->SetSelectedFigure(NULL);
		op->ClearStatusBar(); 
	}

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		ChangeDrawClrAction* ChangeColorAction = new ChangeDrawClrAction(pManager, DrawingClr);
		*ChangeColorAction = *this;
		pManager->AddActionToRecordingList(ChangeColorAction);
	}

}

void ChangeDrawClrAction::PlayRecording()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetSelectedFigure();
	if (FIG) {
		op->setDrawclr(DrawingClr);
		FIG->ChngDrawClr(DrawingClr);
		FIG->SetSelected(false);
		pManager->SetSelectedFigure(NULL);
	}
	ChangeDrawClrAction* ChangeColorAction = new ChangeDrawClrAction(pManager, DrawingClr);
	*ChangeColorAction = *this;
	pManager->AddToUndoList(ChangeColorAction);
}

bool ChangeDrawClrAction::CanUndo()
{
	return true;
}

void ChangeDrawClrAction::Undo()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		if (PrevDefault.isFilled)
			op->setfilled();
		else
			op->SetNonFilled();
		FIG->ChngDrawClr(PrevDrawingClr);
		FIG->SetSelected(false);

		op->setFillclr(PrevDefault.FillClr);
		op->setDrawclr(PrevDefault.DrawClr);
		pManager->SetSelectedFigure(NULL);
	}
}

void ChangeDrawClrAction::Redo()
{
	Output* op = pManager->GetOutput();
	CFigure* FIG = pManager->GetFigure(ID);
	if (FIG) {
		op->setDrawclr(DrawingClr);
		FIG->ChngDrawClr(DrawingClr);
		FIG->SetSelected(false);
		pManager->SetSelectedFigure(NULL);
	}
}
