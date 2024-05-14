#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddHexaAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\SelectAction.h"
#include "Actions\MoveFigureAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions/switchToPlayAction.h"
#include "Actions/switchToDrawAction.h"
#include "Actions/pickHideAction.h"
#include "Actions/playByShapeAction.h"
#include "Actions/playByColorAction.h"
#include "Actions/playByBothAction.h"
#include "Figures/CCircle.h"  
#include "Figures/CHexagon.h" 
#include "Figures/CRectangle.h"
#include "Figures/CSquare.h" 
#include "Figures/CTriangle.h"
#include <time.h>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include "Actions/DeleteAction.h"
#include "Actions/Action.h"
#include "Actions/UndoAction.h"
#include "Actions/RedoAction.h"
#include "Actions\ChangeDrawClrAction.h"
#include "Actions\ChangeFillClrAction.h"
#include "Actions\StartRecordingAction.h"
#include "Actions\StopRecordingAction.h"
#include "Actions\PlayRecordingAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"
#include "Actions/exitAction.h"
#include "Actions/ResizeAction.h"
#include "Actions/muteAction.h"
#include"Actions/MoveByDraggingAction.h"
#pragma comment(lib,"winmm.lib")
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	FigCount = 0;
	isPlayMode = 0;
	ActionsCount = 0;
	RedoCount = 0;
	ID = 0;
	RecordStarted = false;
	PlayingRecord = false;
	soundOn = true;
	RecordedActionsCount = 0;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++) {
		FigList[i] = NULL;
		PlayFigList[i] = NULL;
	}
		

	for (int i = 0; i < MaxActionsCount; i++) {
		UndoList[i] = NULL;
		RedoList[i] = NULL;
	}
	for (int i = 0; i < MaxRecords; i++)
		RecordingActionList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			if (soundOn)
				PlaySound(TEXT("Sound/rectangle.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pAct = new AddRectAction(this);
			break;

		case DRAW_HEXA:
			if (soundOn)
				PlaySound(TEXT("Sound/Hexagon.wav"),NULL, SND_FILENAME| SND_ASYNC);
			pAct = new AddHexaAction(this);
			break;

		case DRAW_TRIANGLE:
			if (soundOn)
				PlaySound(TEXT("Sound/Triangle.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pAct = new AddTriangleAction(this);
			break;
		case DRAW_CIRCLE:
			if (soundOn)
				PlaySound(TEXT("Sound/Circle.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pAct = new AddCircleAction(this);
			break;

		case DRAW_SQUARE:
			if (soundOn)
				PlaySound(TEXT("Sound/square.wav"), NULL, SND_FILENAME | SND_ASYNC);
			pAct = new AddSquareAction(this);
			break;

		case SELECT_SHAPE:
			pAct = new SelectAction(this);
			break;
		case SAVE_GRAPH: 
			pAct = new SaveAction(this);
			break;

		case LOAD_GRAPH: 
			pAct = new LoadAction(this);
			break;
		case RESIZE:
			if (SelectedFig)
			pAct = new ResizeAction(this);
			break;
		case MOVEBYDRAGGING:
			pAct = new MoveByDraggingAction(this);
			break;
		case CHANGE_BORDERCLR: 
		{
			if (SelectedFig){
			pOut->CreateColorlist();
			ActionType ActType = pIn->GetUserAction();
			switch (ActType)
			{
			case CHNGCLR_BLACK:
				pAct = new ChangeDrawClrAction(this, BLACK);
				break;

			case CHNGCLR_BLUE:
				pAct = new ChangeDrawClrAction(this, BLUE);
				break;

			case CHNGCLR_GREEN:
				pAct = new ChangeDrawClrAction(this, GREEN);
				break;

			case CHNGCLR_YELLOW:
				pAct = new ChangeDrawClrAction(this, YELLOW);
				break;

			case CHNGCLR_ORANGE:
				pAct = new ChangeDrawClrAction(this, ORANGE);
				break;

			case CHNGCLR_RED:
				pAct = new ChangeDrawClrAction(this, RED);
				break;
			default:
				pAct = NULL;
				break;
			}
			break;
			}
		}

		case CHANGE_FILLCLR:
		{
			if (SelectedFig){
			pOut->CreateColorlist();
			ActionType ActType = pIn->GetUserAction();
			switch (ActType)
			{
			case CHNGCLR_BLACK:
				pAct = new ChangeFillClrAction(this, BLACK);
				break;

			case CHNGCLR_BLUE:
				pAct = new ChangeFillClrAction(this, BLUE);
				break;

			case CHNGCLR_GREEN:
				pAct = new ChangeFillClrAction(this, GREEN);
				break;

			case CHNGCLR_YELLOW:
				pAct = new ChangeFillClrAction(this, YELLOW);
				break;

			case CHNGCLR_ORANGE:
				pAct = new ChangeFillClrAction(this, ORANGE);
				break;

			case CHNGCLR_RED:
				pAct = new ChangeFillClrAction(this, RED);
				break;
			default:
				pAct = NULL;
				break;
			}
			break;
			}
		}

		case MOVE_FIGURE:
			if (SelectedFig)
			pAct = new MoveFigureAction(this);
			break;

		case START_RECORDING:
			pAct = new StartRecordingAction(this);
			break;

		case STOP_RECORDING:
			pAct = new StopRecordingAction(this);
			break;
		case PLAY_RECORDING:
			pAct = new PlayRecordingAction(this);
			break;

		case TO_PLAY:  
			pAct = new switchToPlayAction(this);
			isPlayMode = true;
			break;

		case TO_DRAW: 
			pAct = new switchToDrawAction(this);
			isPlayMode = false;
			break;

		case PickHideGame:
			pAct = new pickHideAction(this);
			break;

		case PLAYBYSHAPE: 
			pAct = new playByShapeAction(this);
			loopCount = FigCount;
			isPlaying = true;
			break;

		case PLAYBYCOLOR: 
			pAct = new playByColorAction(this);
			loopCount = FigCount;
			isPlaying = true;
			break;

		case PLAYBYBOTH:
			pAct = new playByBothAction(this);
			loopCount = FigCount;
			isPlaying = true;
			break;
		case DELETE_FIGURE:
			if(SelectedFig)
			pAct = new DeleteAction(this);
			break;
		case UNDO:
			pAct = new UndoAction(this); 
			break;
		case REDO:
			pAct = new RedoAction(this);
			break;
		case CLEAR_ALL: 
			pAct = new ClearAllAction(this);
			break;

		case MUTE_SOUND:
			if (soundOn) {
				soundOn = false;
				pOut->ClearDrawToolBar();
				pOut->createToolBarWithSound();
			}
			else {
				soundOn = true;
				pOut->ClearDrawToolBar();
				pOut->CreateDrawToolBar();
			}

			pAct = new muteAction(this);
			break;

		case EXIT:
			///create ExitAction here
			pAct = new exitAction(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute

			AddToUndoList(pAct);
		

		pAct=NULL;//You may need to change this line depending to your implementation
	}
}

void ApplicationManager::AddActionToRecordingList(Action* pAct)
{
	if (pAct) {
		if (RecordedActionsCount < MaxRecords) {
			RecordingActionList[RecordedActionsCount] = pAct;
			RecordedActionsCount++;
		}
		else {
			pOut->PrintMessage("Error: You Can't Record More Than 20 Actions, The Following Actions Won't Be Recorded");
		}
	}
}

Action** ApplicationManager::GetRecordedActions()
{
	return RecordingActionList;
}

bool ApplicationManager::IsRecording()
{
	return RecordStarted;
}

void ApplicationManager::SetRecordingStatus(bool s)
{
	RecordStarted = s;
}

int ApplicationManager::GetRecordedActionsCount()
{
	return RecordedActionsCount;
}

int ApplicationManager::GetUndoActionsCount()
{
	return ActionsCount;
}

int ApplicationManager::GetRedoActionsCount()
{
	return RedoCount;
}

void ApplicationManager::sortByID()
{
	int i, j, minIndx;

	for (i = 0; i < FigCount - 1; i++) {
		
		minIndx = i;

		for (j = i + 1; j < FigCount; j++) {
			if (FigList[j]->GetID() < FigList[minIndx]->GetID())
				minIndx = j;
		}

		if (minIndx != i)
			swap(FigList[minIndx], FigList[i]);
	}
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures


void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount) {
		FigList[FigCount++] = pFig;
		pFig->SetID(ID++);
	}
}

int ApplicationManager::GetFigureCount() const {
	return FigCount;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	int i;

	if (!isPlayMode) {
		i = FigCount - 1;

		while (i >= 0 && FigList[i]) {
			if (FigList[i]->IsInside(x, y))
				return FigList[i];
			i--;
		}

	}

	else {
		i = loopCount - 1;

		while (i >= 0 && FigList[i]) {
			if (PlayFigList[i])
				if (PlayFigList[i]->IsInside(x, y))
					return FigList[i];
			i--;
		}

	}

	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
	return NULL;
}
CFigure* ApplicationManager::GetFigure(int id)
{
	int i = 0;
	bool found = false;
	while (!found && i < FigCount && FigList[i]) {
		if (FigList[i]->GetID() == id) {
			found = true;
		}
		else
			i++;
	}
	if (found)
		return FigList[i];

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface

CFigure *ApplicationManager::GetSelectedFigure() const {
	return SelectedFig;
}
void ApplicationManager::SetSelectedFigure(CFigure* Fig)
{
	SelectedFig = Fig;
}
int ApplicationManager::GetSelectedFigureIndex() {

	if (SelectedFig == NULL) return -1;
	else {
		int i = 0;
		bool detected = false;
		while (!detected && i < FigCount && FigList[i]){
			if (SelectedFig == FigList[i]) {
				detected = true;
			}
			else
				i++;
		}
		return i;
	}
}
CFigure* ApplicationManager::DeleteFigure()
{
	int i = GetSelectedFigureIndex();
	if (i == -1) return NULL;
	else{
	for (int j = i; j < FigCount - 1; j++) {
		swap(FigList[j], FigList[j + 1]);
	}
	--FigCount;
	FigList[FigCount] = NULL;
	return SelectedFig;
	}
}

void ApplicationManager::DeleteAllFigures()
{
	/*Looping on The FigList And Delete All Figures*/
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	ID = 0;
}

void ApplicationManager::DeleteAllRecordedActions()
{
	if (!PlayingRecord) {
	for (int i = 0; i < RecordedActionsCount; i++) {
		if (RecordingActionList[i]) {
		delete RecordingActionList[i];
		RecordingActionList[i] = NULL;
		}
	}
	RecordedActionsCount = 0;
	RecordStarted = false;
	}
}
void ApplicationManager::SetPlayingRecord(bool b)
{
	PlayingRecord = b;
}
bool ApplicationManager::IsPlayingRecord()
{
	return PlayingRecord;
}
void ApplicationManager::UpdateInterface() const
{

	if (!isPlayMode) 
	{
		pOut->ClearDrawArea();

		for (int i = 0; i < FigCount; i++)
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	}

	else { 
		
		if (!isPlaying) {
			pOut->CreatePlayToolBar();
		}

		else {
			pOut->CreatePlayToolBar();
		}


	}
}
void ApplicationManager::createPlayArea() const 
{

	pOut->ClearDrawArea();

	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)

}

int ApplicationManager::getFigCount() const
{
	return FigCount;
}

CFigure* ApplicationManager::getRandomFig() const
{

	srand(static_cast<unsigned int>(time(NULL)));

	int randomIndex = rand() % FigCount;

	return FigList[randomIndex];
}

void ApplicationManager::getShapesCount(int& RC, int& SC, int& CC, int& HC, int& TC) const
{
	for (int i = 0; i < FigCount; i++) {
		if (dynamic_cast<CSquare*>(FigList[i])) SC++;
		else if (dynamic_cast<CRectangle*>(FigList[i])) RC++;
		else if (dynamic_cast<CCircle*>(FigList[i])) CC++;
		else if (dynamic_cast<CHexagon*>(FigList[i])) HC++;
		else if (dynamic_cast<CTriangle*>(FigList[i])) TC++;

	}
}

void ApplicationManager::getColorsCount(int& BlackC, int& YC, int& OC, int& RC, int& GC, int& BlueC)
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFillColor() == BLACK && FigList[i]->getGfxInfo().isFilled) BlackC++;
		else if (FigList[i]->getFillColor() == YELLOW && FigList[i]->getGfxInfo().isFilled) YC++;
		else if (FigList[i]->getFillColor() == ORANGE && FigList[i]->getGfxInfo().isFilled) OC++;
		else if (FigList[i]->getFillColor() == RED && FigList[i]->getGfxInfo().isFilled) RC++;
		else if (FigList[i]->getFillColor() == GREEN && FigList[i]->getGfxInfo().isFilled) GC++;
		else if (FigList[i]->getFillColor() == BLUE && FigList[i]->getGfxInfo().isFilled) BlueC++;
	}
}

void ApplicationManager::deleteChosenFig(Point p)
{
	pOut->ClearDrawArea();

	CFigure* selected = GetFigure(p.x, p.y);

	SetSelectedFigure(selected);

	int i = GetSelectedFigureIndex();

	if (i != -1) {
		PlayFigList[i] = NULL;
	}	

	for (int i = 0; i < loopCount; i++) {
		if (PlayFigList[i]) PlayFigList[i]->Draw(pOut);
	}
}

int ApplicationManager::countShapeColors(string shape, color c)
{
	int count = 0;

	for (int i = 0; i < FigCount; i++) {
		if (shape == "R") {
			if (dynamic_cast<CRectangle*>(FigList[i]) && FigList[i]->getFillColor() == c && FigList[i]->getGfxInfo().isFilled) count++;
		}

		else if (shape == "S") {
			if (dynamic_cast<CSquare*>(FigList[i]) && FigList[i]->getFillColor() == c && FigList[i]->getGfxInfo().isFilled) count++;
		}

		else if (shape == "C") {
			if (dynamic_cast<CCircle*>(FigList[i]) && FigList[i]->getFillColor() == c && FigList[i]->getGfxInfo().isFilled) count++;
		}

		else if (shape == "H") {
			if (dynamic_cast<CHexagon*>(FigList[i]) && FigList[i]->getFillColor() == c && FigList[i]->getGfxInfo().isFilled) count++;
		}

		else if (shape == "T") {
			if (dynamic_cast<CTriangle*>(FigList[i]) && FigList[i]->getFillColor() == c && FigList[i]->getGfxInfo().isFilled) count++;
		}

	}

	return count;
}

int ApplicationManager::getFillCount()
{
	int count = 0;

	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getGfxInfo().isFilled) count++;
	}

	return count;
}

bool ApplicationManager::getSoundState()
{
	return soundOn;
}

int ApplicationManager::getNonFillCount()
{
	int count = 0;

	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getGfxInfo().isFilled == 0) count++;
	}

	return count;
}

color ApplicationManager::getRandomColor()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int randomIndex = rand() % FigCount;
/*
if (FigList[randomIndex]->getFillStats() == 0) {
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getFillStats()) return FigList[i]->getFillColor();
	}
}
*/
while (FigList[randomIndex]->getGfxInfo().isFilled != 1) {
		randomIndex = rand() % FigCount;
	}



	return FigList[randomIndex]->getFillColor();
}

void ApplicationManager::copyDrawList()
{
	for (int i = 0; i < FigCount; i++) {
		PlayFigList[i] = FigList[i];
	}
}

void ApplicationManager::resetPlayList()
{
	for (int i = 0; i < FigCount; i++) {
		PlayFigList[i] = NULL;
	}
}

int ApplicationManager::GetFigCount()
{
	return FigCount;
}

void ApplicationManager::Saveall(ofstream& fout)
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] != NULL) {
			FigList[i]->save(fout); //It's A Vertual Function To Save Different Parameters Depending On Each Figure Type
		}
	}
}

Action* ApplicationManager::GetLastAction()
{
	if (ActionsCount > 0) {
		ActionsCount--;
		return UndoList[ActionsCount];//
	}
	else
		return NULL;
}
Action* ApplicationManager::GetLastAction_Redo()
{
	if (RedoCount > 0) {
		RedoCount--;
		return RedoList[RedoCount];
	}
	else
		return NULL;
}
void ApplicationManager::AddToUndoList(Action* pAct)
{
	if (pAct) {
		if (pAct->CanUndo()) {
			if (ActionsCount < MaxActionsCount) {
				UndoList[ActionsCount] = pAct;
				ActionsCount++;
			}
			else {
				delete UndoList[0];
				UndoList[0] = NULL;
				UndoList[0] = pAct;
				for (int i = 0; i < MaxActionsCount - 1; i++) {
					if (UndoList[i] && UndoList[i + 1])
						swap(UndoList[i], UndoList[i + 1]);
				}
			}
		}
		else {
			delete pAct;
			pAct = NULL;
		}
	}
}
void ApplicationManager::AddToRedoList(Action* pAct)
{
	if (RedoCount < MaxActionsCount) {
		RedoList[RedoCount++] = pAct;
	}
	
}
void ApplicationManager::DeleteRedoList()
{

		for (int i = 0; i < RedoCount; i++) {
			if (RedoList[i]) {
				delete RedoList[i];
			RedoList[i] = NULL;
			}
		}
	RedoCount = 0;
	
}
void ApplicationManager::DeleteUndoList()
{
		for (int i = 0; i < ActionsCount; i++) {
			if (UndoList[i]) {
			delete UndoList[i];
			UndoList[i] = NULL;
			}
		}
	ActionsCount = 0;

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
	delete FigList[i];

	for (int i = 0; i < FigCount; i++)
		if (PlayFigList[i]) delete PlayFigList[i];

	for (int i = 0; i < ActionsCount; i++) {
		if (UndoList[i])
		delete UndoList[i];
	}
	for (int i = 0; i < RedoCount; i++) {
		if (RedoList[i])
			delete RedoList[i];
	}

	for (int i = 0; i < RecordedActionsCount; i++) {
		if (RecordingActionList[i])
		delete RecordingActionList[i];
	}
	delete pIn;
	delete pOut;
	
}
