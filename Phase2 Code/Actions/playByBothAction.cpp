#include "playByBothAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"
#include <ctime>
#include <string>
#include "..\Figures\CSquare.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CRectangle.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
playByBothAction::playByBothAction(ApplicationManager* app):Action(app)
{
	pManager->copyDrawList();

	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();

	correct = wrong = 0;

	numOfShapes = pManager->getFigCount();

	nonFilledCount = pManager->getNonFillCount();

	color colors[6] = { BLACK, YELLOW, RED, ORANGE, GREEN, BLUE };
	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	for (int i = 0; i < 6; i++) {
		Rects[i] = pManager->countShapeColors("R", colors[i]);
	}

	for (int i = 0; i < 6; i++) {
		Squares[i] = pManager->countShapeColors("S", colors[i]);
	}

	for (int i = 0; i < 6; i++) {
		Circles[i] = pManager->countShapeColors("C", colors[i]);
	}

	for (int i = 0; i < 6; i++) {
		Hexas[i] = pManager->countShapeColors("H", colors[i]);
	}

	for (int i = 0; i < 6; i++) {
		Triangles[i] = pManager->countShapeColors("T", colors[i]);
	}

	
}

void playByBothAction::ReadActionParameters()
{
	if (numOfShapes != 0 && pManager->getFillCount() != 0) {

		randShape = pManager->getRandomFig();

		while (randShape->getGfxInfo().isFilled != 1) {
			randShape = pManager->getRandomFig();
		}

		randColor = randShape->getFillColor();

		pOut->PrintMessage("Playing Pick and hide By Both Shape and Color ");

		pOut->ClearPickHideToolBar();

		if (dynamic_cast<CSquare*>(randShape)) {
			playSquare();
		}
		else if (dynamic_cast<CRectangle*>(randShape)) {
			playRectangle();
		}
		else if (dynamic_cast<CHexagon*>(randShape)) {
			playHexagon();
		}
		else if (dynamic_cast<CCircle*>(randShape)) {
			playCircle();
		}
		else if (dynamic_cast<CTriangle*>(randShape)) {
			playTriangle();
		}

		if (correct >= wrong + 2 && pManager->getSoundState()) {
			PlaySound(TEXT("Sound/Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		else if (wrong >= correct + 2 && pManager->getSoundState()) {
			PlaySound(TEXT("Sound/Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		pOut->ClearDrawArea();

		pOut->PrintMessage("Game Ended. Final Result ----> Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
	}

	else if (numOfShapes != 0 && pManager->getFillCount() == 0) {
		pOut->ClearPickHideToolBar();
		pOut->PrintMessage("No colored Shapes to play with ");
	}

	else {
		pOut->ClearPickHideToolBar();
		pOut->PrintMessage("Can't play without any drawings ");
	}

	pManager->resetPlayList();

}

void playByBothAction::Execute()
{
	ReadActionParameters();
}

void playByBothAction::playSquare()
{
	pManager->createPlayArea();

	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black Squares :) ");
		count = Squares[0];
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow Squares :) ");
		count = Squares[1];
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange Squares :) ");
		count = Squares[3];
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED Squares :) ");
		count = Squares[2];
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green Squares :) ");
		count = Squares[4];
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue Squares :) ");
		count = Squares[5];
	}

	while (numOfShapes > 0)
	{
		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CSquare*>(pManager->GetFigure(p.x, p.y)) && pManager->GetFigure(p.x, p.y)->getFillColor() == randColor
				&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == count) break;
			}

			else {
				wrong++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			pManager->deleteChosenFig(p);

			pOut->PrintMessage("Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
		}

		
	}
}

void playByBothAction::playRectangle()
{
	pManager->createPlayArea();

	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black Rectangles :) ");
		count = Rects[0];
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow Rectangles :) ");
		count = Rects[1];
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange Rectangles :) ");
		count = Rects[3];
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED Rectangles :) ");
		count = Rects[2];
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green Rectangles :) ");
		count = Rects[4];
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue Rectangles :) ");
		count = Rects[5];
	}

	while (numOfShapes > 0)
	{
		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CRectangle*>(pManager->GetFigure(p.x, p.y)) && pManager->GetFigure(p.x, p.y)->getFillColor() == randColor
				&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == count) break;
			}

			else {
				wrong++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			pManager->deleteChosenFig(p);

			pOut->PrintMessage("Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
		}

	}
}

void playByBothAction::playHexagon()
{
	pManager->createPlayArea();

	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black Hexagons :) ");
		count = Hexas[0];
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow Hexagons :) ");
		count = Hexas[1];
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange Hexagons :) ");
		count = Hexas[3];
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED Hexagons :) ");
		count = Hexas[2];
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green Hexagons :) ");
		count = Hexas[4];
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue Hexagons :) ");
		count = Hexas[5];
	}

	while (numOfShapes > 0)
	{
		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CHexagon*>(pManager->GetFigure(p.x, p.y)) && pManager->GetFigure(p.x, p.y)->getFillColor() == randColor
				&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == count) break;
			}

			else {
				wrong++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			pManager->deleteChosenFig(p);

			pOut->PrintMessage("Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
		}

		
	}
}

void playByBothAction::playCircle()
{
	pManager->createPlayArea();

	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black Circles :) ");
		count = Circles[0];
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow Circles :) ");
		count = Circles[1];
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange Circles :) ");
		count = Circles[3];
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED Circles :) ");
		count = Circles[2];
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green Circles :) ");
		count = Circles[4];
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue Circles :) ");
		count = Circles[5];
	}

	while (numOfShapes > 0)
	{
		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CCircle*>(pManager->GetFigure(p.x, p.y)) && pManager->GetFigure(p.x, p.y)->getFillColor() == randColor
				&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == count) break;
			}

			else {
				wrong++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			pManager->deleteChosenFig(p);

			pOut->PrintMessage("Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
		}

		
	}
}

void playByBothAction::playTriangle()
{
	pManager->createPlayArea();

	// indexing  0: Black, 1: Yellow, 2: Red, 3: Orange, 4: Green, 5: Blue  ---------------*

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black Triangles :) ");
		count = Triangles[0];
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow Triangles :) ");
		count = Triangles[1];
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange Triangles :) ");
		count = Triangles[3];
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED Triangles :) ");
		count = Triangles[2];
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green Triangles :) ");
		count = Triangles[4];
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue Triangles :) ");
		count = Triangles[5];
	}

	while (numOfShapes > 0)
	{
		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("coYou Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CTriangle*>(pManager->GetFigure(p.x, p.y)) && pManager->GetFigure(p.x, p.y)->getFillColor() == randColor
				&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == count) break;
			}

			else {
				wrong++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			pManager->deleteChosenFig(p);

			pOut->PrintMessage("Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
		}

		
	}
}
