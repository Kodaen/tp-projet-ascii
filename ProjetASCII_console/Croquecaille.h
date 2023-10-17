#pragma once
// #include <wincontypes.h>
// #include "Entity.h"

class Croquecaille : public Entity
{
	// Constructors
public:
	Croquecaille();
	Croquecaille(COORD pos, DIRECTION lookingDirection);

	// Attributes
private :
	short _currentStep = 0;

	// Functions
public :
	virtual void update();

protected:
	void shootBuble();
};

