#include "playByColorAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"
#include "time.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
playByColorAction::playByColorAction(ApplicationManager* app) :Action(app)
{
	pManager->copyDrawList();

	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	numOfShapes = pManager->getFigCount();
	correct = 0;
	wrong = 0;
	blackCount = yellowCount = orangeCount = redCount = greenCount = blueCount = 0;
	pManager->getColorsCount(blackCount, yellowCount, orangeCount, redCount, greenCount, blueCount);
	fillCount = pManager->getFillCount();

}

void playByColorAction::ReadActionParameters()
{
	if (numOfShapes != 0 && fillCount > 0) {

		pOut->PrintMessage("Playing Pick and hide By Color ");

		pOut->ClearPickHideToolBar();

		randColor = pManager->getRandomColor();

		startGame();

		if (correct >= wrong + 2 && pManager->getSoundState()) {
			PlaySound(TEXT("Sound/Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		else if (wrong >= correct + 2 && pManager->getSoundState()) {
			PlaySound(TEXT("Sound/Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		pOut->ClearDrawArea();

		pOut->PrintMessage("Game Ended. Final Results -----> Correct: " + to_string(correct) + "  " + "Wrong: " + to_string(wrong));
	}

	else if (fillCount == 0 && numOfShapes != 0) {
		pOut->ClearPickHideToolBar();
		pOut->PrintMessage("No colored shapes to play with ");
	}

	else {
		pOut->ClearPickHideToolBar();
		pOut->PrintMessage("Can't play without any drawings ");
	}

	pManager->resetPlayList();
}


void playByColorAction::Execute()
{
	ReadActionParameters();
}

void playByColorAction::startGame()
{
	int count = 0;

	pManager->createPlayArea();

	if (randColor == BLACK) {
		pOut->PrintMessage("Select all Black shapes :) ");
		count = blackCount;
	}
	else if (randColor == YELLOW) {
		pOut->PrintMessage("Select all Yellow shapes :) ");
		count = yellowCount;
	}
	else if (randColor == ORANGE) {
		pOut->PrintMessage("Select all Orange shapes :) ");
		count = orangeCount;
	}
	else if (randColor == RED) {
		pOut->PrintMessage("Select all RED shapes :) ");
		count = redCount;
	}
	else if (randColor == GREEN) {
		pOut->PrintMessage("Select all Green shapes :) ");
		count = greenCount;
	}
	else if (randColor == BLUE) {
		pOut->PrintMessage("Select all Blue shapes :) ");
		count = blueCount;
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

			if (randColor == pManager->GetFigure(p.x, p.y)->getFillColor()
											&& pManager->GetFigure(p.x, p.y)->getGfxInfo().isFilled){
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
