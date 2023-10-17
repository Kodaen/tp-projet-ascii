#pragma once
//#include <wincontypes.h>
//#include "Direction.h"
//#include "Entity.h"
class Sertrail :public Entity
{
	// Constructors
public:
	Sertrail();
	Sertrail(COORD pos, DIRECTION lookingDirection);

	// Attributes
private:
	short _currentStep = 0;
	bool changedTrajectory = false;


	// Functions
public:
	virtual void update();

	void turnToRight();
};

