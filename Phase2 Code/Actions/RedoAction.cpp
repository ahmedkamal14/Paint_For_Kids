#include "RedoAction.h"
#include "..\ApplicationManager.h"
#include "AddHexaAction.h"

RedoAction::RedoAction(ApplicationManager* pApp):Action(pApp)
{
}

void RedoAction::Execute()
{

	// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
	if (pManager->IsRecording()) {
		RedoAction* rAction = new RedoAction(pManager);
		*rAction = *this;
		pManager->AddActionToRecordingList(rAction);
	}
	
	Action* Act = pManager->GetLastAction_Redo();
	if (Act) {
		Act->Redo();
		pManager->AddToUndoList(Act);
		Act = NULL;
	}
	else
		pManager->GetOutput()->PrintMessage("ERROR: you can't redo an action unless you undo it first");

	pManager->sortByID();
}

void RedoAction::ReadActionParameters()
{
}

void RedoAction::PlayRecording()
{
	

	Action* Act = pManager->GetLastAction_Redo();
	if (Act) {
		Act->Redo();
		pManager->sortByID();
		pManager->AddToUndoList(Act);
		Act = NULL;
	}
	else
		pManager->GetOutput()->PrintMessage("ERROR: you can't redo an action unless you undo it first");

}
