#include "AddCircleAction.h"
#include "Action.h"
#include "../Figures/CCircle.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../GUI/UI_Info.h"


AddCircleAction::AddCircleAction(ApplicationManager* pApp) :Action(pApp)
{
	CanDraw = true;
}

void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Circle: Click at Center Point");

	//Read center and store in Center
	pIn->GetPointClicked(Center.x, Center.y);


	pOut->PrintMessage("Click any point on the Circle");

	//Read another point P2 to calc the radius
	pIn->GetPointClicked(P2.x, P2.y);

	// Checks if the radius = 0 it does't excute the action
	if (Center.x == P2.x && Center.y == P2.y) CanDraw = false;

	//A validation statement Checks if the point clicked on the tool bar or the status bar to prevent drawing
	if (Center.y > UI.ToolBarHeight + UI.ToolBarBorderWidth && Center.y < UI.height - UI.StatusBarHeight) {
		double radius;
		int XDiff = Center.x - P2.x;
		int YDiff = Center.y - P2.y;
		radius = sqrt((XDiff * XDiff) + (YDiff * YDiff));
		//A validation statement Checks if the Circle will come over the tool bar or the status bar to prevent drawing
		if (radius > Center.y - (UI.ToolBarHeight + UI.ToolBarBorderWidth) || radius > UI.height - UI.StatusBarHeight - Center.y) {
			CanDraw = false;
		}
	}
	else {
		CanDraw = false;
	}


	CircleGfxInfo.isFilled = pOut->checkisfilled();	//default is not filled

	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();


}

void AddCircleAction::Execute()
{
	ReadActionParameters();

	if (CanDraw) { // checks if the action is executable

		//Create a Circle with the parameters read from the user
		CCircle* C = new CCircle(Center, P2, CircleGfxInfo);

		//Add the Circle to the list of figures
		pManager->AddFigure(C);
		ID = C->GetID();

		// If Recording Is Enabled This Will Add Current Recording To RecordedActionsList
		if (pManager->IsRecording()) {
			AddCircleAction* addAction = new AddCircleAction(pManager);
			*addAction = *this;
			pManager->AddActionToRecordingList(addAction);
		}

		// After Adding to application manager it deletes the redo list
		pManager->DeleteRedoList();
	}
	else {
		pManager->GetOutput()->PrintMessage("You Can't draw from these points");
	}
}

void AddCircleAction::Undo()
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

void AddCircleAction::Redo()
{
	CCircle* C = new CCircle(Center, P2, CircleGfxInfo);
	//Add the Circle to the list of figures
	pManager->AddFigure(C);
	C->SetID(ID);
}

void AddCircleAction::PlayRecording()
{
	//Creates a Figure with the parameters been already read from the user
	CCircle* C = new CCircle(Center, P2, CircleGfxInfo);
	
	//Add the Figure to the list of figures
	pManager->AddFigure(C);
	ID = C->GetID();

	// Adds the Figure to undo list while playing the record and deletes the redo list
	AddCircleAction* addAction = new AddCircleAction(pManager);
	*addAction = *this;
	pManager->AddToUndoList(addAction);
	pManager->DeleteRedoList();

}