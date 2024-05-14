#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
	DeletedFig = NULL;
}
void DeleteAction::ReadActionParameters()
{}
void DeleteAction::Execute() {

	CFigure* fig = pManager->DeleteFigure();
	if (fig){
	fig->SetSelected(false);
	DeletedFig = fig;
	ID = fig->GetID();
	fig = NULL;
	pManager->SetSelectedFigure(NULL);
	}

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		DeleteAction* dAction = new DeleteAction(pManager);
		*dAction = *this;
		pManager->AddActionToRecordingList(dAction);
	}
	pManager->DeleteRedoList();
	pManager->GetOutput()->ClearStatusBar();
}
void DeleteAction::Undo() {
	pManager->AddFigure(DeletedFig);
	DeletedFig->SetID(ID);
	DeletedFig = NULL;
}


void DeleteAction::Redo()
{
	CFigure* fig = pManager->GetFigure(ID);
	pManager->SetSelectedFigure(fig);
	fig = pManager->DeleteFigure();
	DeletedFig = fig;
	fig = NULL;
	pManager->SetSelectedFigure(NULL);
}

DeleteAction::~DeleteAction()
{
	if (DeletedFig) {
		delete DeletedFig;
	}

}


void DeleteAction::PlayRecording()
{
	CFigure* fig = pManager->DeleteFigure();
	fig->SetSelected(false);
	pManager->SetSelectedFigure(NULL);
	DeletedFig = fig;
	fig = NULL;
	DeleteAction* dAction = new DeleteAction(pManager);
	*dAction = *this;
	pManager->AddToUndoList(dAction);
	pManager->DeleteRedoList();
}
