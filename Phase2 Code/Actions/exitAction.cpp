#include "exitAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"
#include "SaveAction.h"
#include <iostream>
using namespace std;


exitAction::exitAction(ApplicationManager* app) :Action(app)
{
}

void exitAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	SaveAction* save = new SaveAction(pManager);


	if (pManager->getFigCount() != 0) {

		pOut->PrintMessage("You Clicked Exit button all Drawings will be discarded :(");

		Sleep(1500);

		pOut->PrintMessage("Do you want to Save your Drawing ? (y , n)");

		string ans = pIn->GetSrting(pOut);

		if (ans == "y" || ans == "yes") {

			save->Execute();

			pOut->PrintMessage("File Saved Successfully :) ");

			Sleep(1000);

			pOut->PrintMessage("Application closing");

		}

		else {
			pOut->PrintMessage("Application closing");
		}

	}
	
	pManager->DeleteAllFigures();

	delete save;
	
}

void exitAction::Execute()
{
	ReadActionParameters();
}
