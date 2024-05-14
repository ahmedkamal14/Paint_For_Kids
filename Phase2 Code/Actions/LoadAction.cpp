#include "LoadAction.h"
#include "ClearAllAction.h"
#include <string>
#include <fstream>
#include "../Figures/CCircle.h"
#include "../Figures/CHexagon.h"
#include "../Figures/CRectangle.h"
#include "../Figures/CSquare.h"
#include "../Figures/CTriangle.h"
#include "../ApplicationManager.h"




LoadAction::LoadAction(ApplicationManager* pApp): Action(pApp)
{
}

void LoadAction::ReadActionParameters()
{ 
	Input* pIn;
	Output* pOut;
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("please enter the File Name to load from: ");  //Getting the File Name to Load from
	FileName = pIn->GetSrting(pOut);
}

void LoadAction::Execute()
{
	ReadActionParameters();
	
	int figsnumber;
	Input* pIn;
	Output* pOut;
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	ifstream Fin;
	string path = "Graphs/";
	Fin.open(path+FileName+".txt"); 
	

	string CDrawClr, CFillClr,type;

	if (Fin.is_open()) {
		ClearAllAction CA(pManager); 
		CA.Execute();  // Clear Every Thing in FigList before Loading in Case The File Exists Only 
		pOut->PrintMessage("Loaded Successfully :)");
		Fin >> CDrawClr >> CFillClr;    

		//**To Set The Draw Color
		if (CDrawClr == "BLACK") pOut->setDrawclr(BLACK);
		else if (CDrawClr == "RED") pOut->setDrawclr(RED);
		else if (CDrawClr == "BLUE") pOut->setDrawclr(BLUE);
		else if (CDrawClr == "ORANGE") pOut->setDrawclr(ORANGE);
		else if (CDrawClr == "YELLOW") pOut->setDrawclr(YELLOW);
		else if (CDrawClr == "GREEN") pOut->setDrawclr(GREEN);


		//** To Set The Fill Color 
		if (CFillClr == "NOT_FILLED") pOut->SetNonFilled();
		else {
			pOut->setfilled();
		if (CFillClr == "BLACK") pOut->setFillclr(BLACK);
		else if (CFillClr == "RED") pOut->setFillclr(RED); 
		else if (CFillClr == "BLUE") pOut->setFillclr(BLUE);
		else if (CFillClr == "ORANGE") pOut->setFillclr(ORANGE);
		else if (CFillClr == "YELLOW") pOut->setFillclr(YELLOW);
		else if (CFillClr == "GREEN") pOut->setFillclr(GREEN);
		}

		//** To Set Number Of Figures
		Fin >> figsnumber;
		CFigure* myfig = NULL; // Creating A Pointer Of Class Figure To Points To Each Figure 


		for (int i = 0; i < figsnumber; i++) {
			Fin >> type;

			// Checking The Type Of Each Figure

			if (type == "RECT") { myfig = new CRectangle; }
			else if (type == "SQUARE") { myfig = new CSquare; }
			else if (type == "HEXAGON") { myfig = new CHexagon; }
			else if (type == "TRIANGLE") { myfig = new CTriangle; }
			else if (type == "CIRCLE") { myfig = new CCircle; }
			else continue;
			myfig->load(Fin);  //Calling the Function Load In Each Figure To Creat It
			pManager->AddFigure(myfig); // Adding This Figure To The FigList
			myfig->SetSelected(false);

		}

		Fin.close();

	}
	else pOut->PrintMessage("Sorry, This file doesn't exist :("); ///In Case The File doesn't Exist
	
	

}

