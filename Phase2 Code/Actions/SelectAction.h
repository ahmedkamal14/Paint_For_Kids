#pragma once
#include "Action.h"

class SelectAction :
    public Action
{
private: Point P;
       

public:
    SelectAction(ApplicationManager*);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void PlayRecording();

};

