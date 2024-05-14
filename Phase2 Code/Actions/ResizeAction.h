#pragma once
#include "Action.h"
class ResizeAction :
    public Action
{
private:
    Point P,P2;
    int num;
    int ID;
    bool IsDone;
public:
    ResizeAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual bool CanUndo();
    virtual void Undo();
    virtual void Redo();
    virtual void PlayRecording();
};

