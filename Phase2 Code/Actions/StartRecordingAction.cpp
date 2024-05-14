#include "StartRecordingAction.h"
#include "..\ApplicationManager.h"
#include "AddRectAction.h"
#include "AddHexaAction.h"
#include "AddTriangleAction.h"
#include "AddCircleAction.h"
#include "SelectAction.h"
#include "MoveFigureAction.h"
#include "StartRecordingAction.h"
#include "PlayRecordingAction.h"
#include "StopRecordingAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

StartRecordingAction::StartRecordingAction(ApplicationManager* pApp) : Action(pApp) {}

void StartRecordingAction::ReadActionParameters() {
	//Get a Pointer to Output Interface
	Output* pOut = pManager->GetOutput();

	if (RecordingCanBeEnabled() && !pManager->IsRecording()) {
		pOut->PrintMessage("Record Has Started");
		pManager->SetRecordingStatus(true);
	}
	else if (!RecordingCanBeEnabled() && !pManager->IsRecording()) {
		pOut->PrintMessage("Please Reset (Clear All) First To Start Recording");
	}
	else if (pManager->IsRecording()) {
		pOut->PrintMessage("Record Has Already Started");
	}

}

bool StartRecordingAction::RecordingCanBeEnabled() { // Function To Check If We Can Start Recording
	if (pManager->GetFigureCount() == 0 && pManager->GetRecordedActionsCount() == 0 && pManager->GetUndoActionsCount() == 0 && pManager->GetRedoActionsCount() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void StartRecordingAction::Execute()
{
	RecordingCanBeEnabled();
	ReadActionParameters();
}

