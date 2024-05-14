#pragma once
#include "Action.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
class DeleteAction :
    public Action
{
    //to make a Copy of the deleted figure
    CFigure* DeletedFig;
    int ID;
public:
    DeleteAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
    virtual bool CanUndo() { return true; }
    virtual void PlayRecording();

    ~DeleteAction();
};


