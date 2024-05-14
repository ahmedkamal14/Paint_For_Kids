#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions/Action.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200, MaxRecords = 20};	//Max no of figures
	enum { MaxActionsCount = 5 };
private:
	int FigCount;		//Actual number of figures
	int loopCount;     // Count to loop on in PlayMode
	int ID;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* PlayFigList[MaxFigCount]; // List of all figures in playMode
	bool soundOn; // true if sound if on and false otherwise 

	CFigure* SelectedFig; //Pointer to the selected figure

	bool isPlayMode; 
	bool isPlaying; 
	Action* UndoList[MaxActionsCount];
	Action* RedoList[MaxActionsCount];
	int RedoCount;
	int ActionsCount;//Actual Actions in the 
	int RecordedActionsCount;
	Action* RecordingActionList[MaxRecords]; // Array Of Recorded Actions
	bool RecordStarted;
	bool PlayingRecord;

	
	//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure* GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* GetFigure(int id); //Searches for a Figure given its ID
	CFigure* GetSelectedFigure() const;
	void SetSelectedFigure(CFigure*);
	int GetFigureCount() const;
	void DeleteAllFigures();
	void DeleteAllRecordedActions();
	void SetPlayingRecord(bool b);
	bool IsPlayingRecord();
	Action* GetLastAction();
	Action* GetLastAction_Redo();
	void AddToUndoList(Action*);
	void AddToRedoList(Action*);
	void DeleteRedoList();
	void DeleteUndoList();
	void AddActionToRecordingList(Action*);
	Action** GetRecordedActions();
	bool IsRecording(); // Return true if we start recording and false if we didn't
	void SetRecordingStatus(bool s); // Turns On and of recording
	int GetRecordedActionsCount();
	int GetUndoActionsCount();
	int GetRedoActionsCount();
	void sortByID();


	// -- Interface Management Functions
	Input* GetInput() const; //Return pointer to the input
	Output* GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	int GetSelectedFigureIndex();
	CFigure* DeleteFigure();

	// -- Play Related functions ***** 
	void createPlayArea() const; // Draw shapes for playing
	int getFigCount() const; // returns numOfShapes
	CFigure* getRandomFig() const; // returns random Figure from the FigList
	void getShapesCount(int &RC, int& SC, int& CC, int& HC, int& TC) const; // gets the count of every shape
	void getColorsCount(int& BlackC, int& YC, int& OC, int& RC, int& GC, int& BlueC); // gets the count of every color
	void deleteChosenFig(Point p); // Deletes the figure chosen while playing
	int countShapeColors(string shape, color c); // count the number of every shape in every volor
	int getFillCount(); // returns the number of filled shapes
	bool getSoundState(); // returns true if sound is on and false otherwise 
	int getNonFillCount(); // returns the number of non-filled shpes
	color getRandomColor(); // returns a random fill color from the FigList
	void copyDrawList(); // makes a copy of the FigList to play from 
	void resetPlayList(); // resets the PlayList to be empty again 


	// save load Functions
	int GetFigCount();
	void Saveall(ofstream& fout);
	
};

#endif