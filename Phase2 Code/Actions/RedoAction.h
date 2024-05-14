#pragma once
#include "Action.h"
class RedoAction :
    public Action
{public:
    RedoAction(ApplicationManager* pApp);
    virtual void Execute();
    virtual void ReadActionParameters();
    virtual void PlayRecording();

};

