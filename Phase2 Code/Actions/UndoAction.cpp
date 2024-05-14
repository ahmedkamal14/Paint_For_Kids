#include "UndoAction.h"
#include "..\ApplicationManager.h"
UndoAction::UndoAction(ApplicationManager* pApp):Action(pApp)
{
}

void UndoAction::Execute()
{

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		UndoAction* uAction = new UndoAction(pManager);
		*uAction = *this;
		pManager->AddActionToRecordingList(uAction);
	}

	Action* Act = pManager->GetLastAction();
	if (Act) {
		Act->Undo();
		pManager->AddToRedoList(Act);
		Act = NULL;
	}
	else
		pManager->GetOutput()->PrintMessage("ERROR: you can't Undo When there is no more actions in the actions list (max Actions 5)");

	pManager->sortByID();
}


void UndoAction::ReadActionParameters()
{
}

void UndoAction::PlayRecording()
{
	

	Action* Act = pManager->GetLastAction();
	if (Act) {
		Act->Undo();
		pManager->sortByID();
		pManager->AddToRedoList(Act);
		Act = NULL;
	}
	else
		pManager->GetOutput()->PrintMessage("ERROR: you can't Undo When there is no more actions in the actions list (max Actions 5)");

}
