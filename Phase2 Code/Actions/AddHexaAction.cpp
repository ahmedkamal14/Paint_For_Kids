#include "AddHexaAction.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddHexaAction::AddHexaAction(ApplicationManager* pApp) :Action(pApp)
{
	CanDraw = true;
	length = 100; // Sets the length of hexagon with 100
}

void AddHexaAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at Center Point");

	//Read center and store in point P
	pIn->GetPointClicked(Center.x, Center.y);

	//A validation statement Checks if the point clicked on the tool bar or the status bar to prevent drawing
	 if (Center.y - length < UI.ToolBarHeight + UI.ToolBarBorderWidth || Center.y + length > UI.height - UI.StatusBarHeight)
		CanDraw = false;
	

	HexaGfxInfo.isFilled = pOut->checkisfilled();	//default is not filled

	//get drawing, filling colors and pen width from the interface
	HexaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexaGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddHexaAction::Execute()
{
	ReadActionParameters();

	if (CanDraw) { // checks if the action is executable

		//Create a hexagon with the parameters read from the user
		CHexagon* H = new CHexagon(Center, HexaGfxInfo, length);

		//Add the hexagon to the list of figures
		pManager->AddFigure(H);
		ID = H->GetID();
		// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
		if (pManager->IsRecording()) {
			AddHexaAction* addAction = new AddHexaAction(pManager);
			*addAction = *this;
			pManager->AddActionToRecordingList(addAction);
		}
		// After Adding to application manager it deletes the redo list
		pManager->DeleteRedoList();

	}
	else {
		pManager->GetOutput()->PrintMessage("You Can't Draw On Any Bar");
	}
}

void AddHexaAction::Undo()
{
	CFigure* Fig = pManager->GetFigure(ID);
	CFigure* Fig2 = pManager->GetSelectedFigure();
	pManager->SetSelectedFigure(Fig);
	pManager->DeleteFigure();
	delete Fig;
	Fig = NULL;
	pManager->SetSelectedFigure(Fig2);
}

void AddHexaAction::Redo()
{
	CHexagon* H = new CHexagon(Center, HexaGfxInfo, length);
	//Add the hexagon to the list of figures
	pManager->AddFigure(H);
	H->SetID(ID);
}

void AddHexaAction::PlayRecording()
{
	//Creates a Figure with the parameters been already read from the user
	CHexagon* H = new CHexagon(Center, HexaGfxInfo, length);

	//Adds the Figure to the list of figures
	pManager->AddFigure(H);
	ID = H->GetID();

	// Adds the Figure to undo list while playing the recorde and deletes the redo list
	AddHexaAction* addAction = new AddHexaAction(pManager);
	*addAction = *this;
	pManager->AddToUndoList(addAction);
	pManager->DeleteRedoList();
}
