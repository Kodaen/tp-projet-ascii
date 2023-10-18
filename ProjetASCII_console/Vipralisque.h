#pragma once
//#include <wincontypes.h>
//#include "Direction.h"
//#include "Entity.h"
class Vipralisque :public Entity
{
	//////////////////////// Constructors //////////////////////// 
public:
	Vipralisque();
	Vipralisque(const COORD& pos, const DIRECTION& lookingDirection);

	//////////////////////// Attributes //////////////////////// 
private:
	short _currentStep = 0;
	bool changedTrajectory = false;
	DIRECTION _shootingDirection;

	//////////////////////// Methods //////////////////////// 
public:
	virtual void update();

	void turnOver();
	void calculateShootingDirection();
	void shootExplosiveVenom();
};

