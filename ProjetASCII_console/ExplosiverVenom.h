#pragma once
//#include <wincontypes.h>
//#include "Direction.h"
//#include "Projectile.h"

class ExplosiverVenom : public Projectile
{
	//////////////////////// Constructors //////////////////////// 
public:
	ExplosiverVenom();
	ExplosiverVenom(const COORD& pos, const COORD& movingDirection);

	//////////////////////// Attributes //////////////////////// 
private :
	int _timeToLive;

	//////////////////////// Methods //////////////////////// 
	virtual void update();

	void explode();
	void die();
};

