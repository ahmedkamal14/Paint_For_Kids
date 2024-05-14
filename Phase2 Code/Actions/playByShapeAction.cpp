#include "playByShapeAction.h"
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


using namespace std;

playByShapeAction::playByShapeAction(ApplicationManager* app) :Action(app)
{
	pManager->copyDrawList();

	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	numOfShapes = pManager->getFigCount();
	correct = 0;
	wrong = 0;
	RectCount = SquareCount = CircleCount = HexCount = TriangleCount = 0;
	pManager->getShapesCount(RectCount, SquareCount, CircleCount, HexCount, TriangleCount);
}

void playByShapeAction::ReadActionParameters()
{

	if (numOfShapes != 0) {

		Shapes randomShape;
		CFigure* shape;

		pOut->PrintMessage("Playing Pick and hide By Shape ");

		pOut->ClearPickHideToolBar();


		// Enum Values, Square:0 , Rectngle: 1, Hexagon: 2, Circle: 3, Triangle: 4 

		shape = pManager->getRandomFig();

		if (dynamic_cast<CSquare*>(shape)) randomShape = SQUARE;
		else if (dynamic_cast<CRectangle*>(shape)) randomShape = RECTANGLE;
		else if (dynamic_cast<CHexagon*>(shape)) randomShape = HEXAGON;
		else if (dynamic_cast<CCircle*>(shape)) randomShape = CIRCLE;
		else if (dynamic_cast<CTriangle*>(shape)) randomShape = TRIANGLE;

		Sleep(1000);

		switch (randomShape)
		{

		case SQUARE:
			playSquare();
			break;

		case RECTANGLE:
			playRectangle();
			break;

		case HEXAGON:
			playHexagon();
			break;

		case CIRCLE:
			playCircle();
			break;

		case TRIANGLE:
			playTriangle();
			break;

		default:
			break;

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

	else {
		pOut->ClearPickHideToolBar();
		pOut->PrintMessage("Can't play without any drawings");
	}

	pManager->resetPlayList();
}

void playByShapeAction::Execute()
{
	ReadActionParameters();
}

void playByShapeAction::playSquare()
{
	pManager->createPlayArea();

	pOut->PrintMessage("Select All the Squares :) ");


	while (numOfShapes > 0) {

		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {
			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CSquare*>(pManager->GetFigure(p.x, p.y))) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == SquareCount) break;
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

void playByShapeAction::playRectangle()
{
	pManager->createPlayArea();

	pOut->PrintMessage("Select All the Rectangles :) ");

	while (numOfShapes > 0) {

		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {

			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CRectangle*>(pManager->GetFigure(p.x, p.y))) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == RectCount) break;
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

void playByShapeAction::playHexagon()
{
	pManager->createPlayArea();

	pOut->PrintMessage("Select All the Hexagons :) ");

	while (numOfShapes > 0) {

		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {

			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CHexagon*>(pManager->GetFigure(p.x, p.y))) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == HexCount) break;
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

void playByShapeAction::playCircle()
{
	pManager->createPlayArea();

	pOut->PrintMessage("Select All the Circles :) ");

	while (numOfShapes > 0) {

		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {

			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CCircle*>(pManager->GetFigure(p.x, p.y))) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == CircleCount) break;
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

void playByShapeAction::playTriangle()
{
	pManager->createPlayArea();

	pOut->PrintMessage("Select All the Triangles :) ");

	while (numOfShapes > 0) {

		pIn->GetPointClicked(p.x, p.y);

		if (p.y >= 0 && p.y < UI.ToolBarHeight) {

			pOut->PrintMessage("You Clicked the tool bar Game Exited :( ");

			Sleep(1000);

			break;
		}

		else {

			if (pManager->GetFigure(p.x, p.y) == NULL) continue;

			else numOfShapes--;

			if (dynamic_cast<CTriangle*>(pManager->GetFigure(p.x, p.y))) {
				correct++;

				if (pManager->getSoundState())
					PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (correct == TriangleCount) break;
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
