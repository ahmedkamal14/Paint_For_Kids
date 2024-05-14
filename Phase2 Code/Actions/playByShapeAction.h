#pragma once
#include "Action.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
class playByShapeAction : public Action
{
	int correct, wrong, numOfShapes;
	int RectCount, SquareCount, HexCount, TriangleCount, CircleCount;
	Point p;
	Output* pOut;
	Input* pIn;

	enum Shapes
	{
		SQUARE,
		RECTANGLE,
		HEXAGON,
		CIRCLE,
		TRIANGLE,
		COUNT
	};

public:
	playByShapeAction(ApplicationManager* app);
	virtual void ReadActionParameters();
	virtual void Execute();
	void playSquare();
	void playRectangle();
	void playHexagon();
	void playCircle();
	void playTriangle();
	virtual bool CanUndo() { return false; }
	virtual void Undo() {}
	virtual void Redo() {}
};

