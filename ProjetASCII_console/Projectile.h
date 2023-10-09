#pragma once
//#include <wincontypes.h>
//#include "Direction.h"

class Projectile : public GameObject
{
public:
	//Default Constructor 
	Projectile();

	//Attributes
protected :
	COORD _movingDirection;

	int _damage;

	//Functions
protected:
	virtual void update();
	void attackAtPos(COORD pos);

public :
	void moveToDirection();
	void recieveDamage(int damage);

	// Getters and Setters
public :
	COORD getMovingDirection() {
		return _movingDirection;
	}
};

