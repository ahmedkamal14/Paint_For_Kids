#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp):Action(pApp)
{
	CanDraw = true;
	length = 90;
}

void AddSquareAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at a Point to draw");

	pIn->GetPointClicked(Center.x, Center.y);

	//A validation statement Checks if the point clicked on the tool bar or the status bar to prevent drawing
	if (Center.y - length / 2 < UI.ToolBarHeight + UI.ToolBarBorderWidth || Center.y + length / 2 > UI.height - UI.StatusBarHeight)
		CanDraw = false;

	SquareGfxInfo.isFilled = pOut->checkisfilled();		// default is not filled
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();	
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddSquareAction::Execute()
{
	ReadActionParameters();

	if (CanDraw) { // checks if the action is executable

		//Create a Square with the parameters read from the user
		CSquare* S = new CSquare(Center, SquareGfxInfo, length);
		pManager->AddFigure(S);
		ID = S->GetID();

		// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
		if (pManager->IsRecording()) {
			AddSquareAction* addAction = new AddSquareAction(pManager);
			*addAction = *this;
			pManager->AddActionToRecordingList(addAction);
		}

		// Delete The Redo List
		pManager->DeleteRedoList();
	}
	else {
		pManager->GetOutput()->PrintMessage("You Can't Draw On Any Bar");
	}
}

void AddSquareAction::Undo()
{
	CFigure* Fig = pManager->GetFigure(ID);
	CFigure* Fig2 = pManager->GetSelectedFigure();
	if (Fig2) {
		Fig2->SetSelected(false);
	}
	pManager->SetSelectedFigure(Fig);
	pManager->DeleteFigure();
	delete Fig;
	Fig = NULL;

}

void AddSquareAction::Redo()
{
	CSquare* S = new CSquare(Center, SquareGfxInfo, length);

	//Add the hexagon to the list of figures
	pManager->AddFigure(S);
	 S->SetID(ID);

}

void AddSquareAction::PlayRecording()
{
	CSquare* S = new CSquare(Center, SquareGfxInfo, length);
	pManager->AddFigure(S);
	ID = S->GetID();

	// Adds the Figure to undo list while playing the record and deletes the redo list
	AddSquareAction* addAction = new AddSquareAction(pManager);
	*addAction = *this;
	pManager->AddToUndoList(addAction);
	pManager->DeleteRedoList();
}
