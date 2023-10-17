#pragma once
// #include <wincontypes.h>
// #include "Entity.h"

class Cabulosaurus : public Entity
{
	//////////////////////// Constructors //////////////////////// 
public:
	Cabulosaurus();
	Cabulosaurus(const COORD& pos, const DIRECTION& lookingDirection);

	//////////////////////// Attributes //////////////////////// 
private:
	short _currentStep = 0;

	//////////////////////// Methods //////////////////////// 
public:
	virtual void update();

protected:
	void shootBubles();
};

