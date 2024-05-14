#include "muteAction.h"
#include "..\GUI\Output.h"

muteAction::muteAction(ApplicationManager* app):Action(app)
{
}

void muteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();

	if (!pManager->getSoundState())
		pOut->PrintMessage("Sound Muted. You can click again to unMute");

	else pOut->PrintMessage("Sound Unmuted");
}

void muteAction::Execute()
{
	ReadActionParameters();
}
