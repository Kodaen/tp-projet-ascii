#pragma once
//#include <wincontypes.h>
//#include "Direction.h"
//#include "Projectile.h"

class VenomSplash : public Projectile
{
	//////////////////////// Constructors //////////////////////// 
public:
	VenomSplash();
	VenomSplash(const COORD& pos, const COORD& movingDirection);

	//////////////////////// Attributes //////////////////////// 
private:
	int _timeToLive;

	//////////////////////// Methods //////////////////////// 
	virtual void update();
};

