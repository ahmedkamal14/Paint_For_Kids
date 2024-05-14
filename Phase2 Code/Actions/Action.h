#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job

public:

	Action(ApplicationManager *pApp) { pManager = pApp; }	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() =0;
	
	//Execute action (code depends on action type)
	virtual void Execute() =0;

	// Undo function
	virtual void Undo() {}

	//Redo Function
	virtual void Redo() {}

	// Checks if we can undo the action and if not it doesn't undo it or add it to undo list
	virtual bool CanUndo() { return false; }

	// Play The Record
	virtual void PlayRecording() {};
};

#endif