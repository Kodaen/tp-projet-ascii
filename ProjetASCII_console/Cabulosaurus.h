#pragma once
// #include <wincontypes.h>
// #include "Entity.h"

class Cabulosaurus : public Entity
{
	// Constructors
public:
	Cabulosaurus();
	Cabulosaurus(COORD pos, DIRECTION lookingDirection);

	// Attributes
private:
	short _currentStep = 0;

	// Functions
public:
	virtual void update();

protected:
	void shootBubles();
};

