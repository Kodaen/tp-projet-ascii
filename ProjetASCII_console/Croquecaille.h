#pragma once
// #include <wincontypes.h>
// #include "Entity.h"

class Croquecaille : public Entity
{
	//////////////////////// Constructors //////////////////////// 
public:
	Croquecaille();
	Croquecaille(const COORD& pos, const DIRECTION& lookingDirection);

	//////////////////////// Attributes //////////////////////// 
private:
	short _currentStep = 0;

	//////////////////////// Methods //////////////////////// 
public:
	virtual void update();

protected:
	void shootBuble();
};

