#pragma once
//#include <wincontypes.h>
//#include "Direction.h"

class Projectile : public GameObject
{
public:
	//////////////////////// Constructors //////////////////////// 
	Projectile();
	Projectile(const COORD& pos, const COORD& movingDirection);

	//////////////////////// Attributes //////////////////////// 
protected:
	COORD _movingDirection;

	int _damage;

	//////////////////////// Methods //////////////////////// 
protected:
	virtual void update();
	void attackAtPos(const COORD& pos);

public:
	void moveToDirection();
	void recieveDamage(const int& damage, WCHAR opponent = L' ');

	//////////////////////// Getters & Setters //////////////////////// 
public:
	COORD getMovingDirection() {
		return _movingDirection;
	}
};

