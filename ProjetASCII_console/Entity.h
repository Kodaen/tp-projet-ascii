#pragma once

//#include <wincontypes.h>
//#include "Direction.h"
//#include "GameObject.h"

class Entity : public GameObject
{
public:
	//Constructors
	Entity();

	Entity(COORD pos, DIRECTION lookingDirection);

protected:
	int _hp;
	int _damage;
	
	// Direction the character is looking (ENUM)
	DIRECTION _lookingDirection;

public:
	virtual void update();
	void refreshDisplayedColor();

	// Moving functions
	bool moveRight(short val);
	bool moveDown(short val);
	bool moveDiagonaly(short valX, short valY);
	bool moveForward();

	// Direction functions
	void turnToDirection(DIRECTION newDirection);

	// Attack and recieve damage functions
	void attack();
	void recieveDamage(int Damage);

	virtual void die();

	// Getters and Setters
public:
	int getHP() {
		return _hp;
	}

	void setHP(int newHp) {
		_hp = newHp;
	}

	int getDamage() {
		return _damage;
	}

	void setDamage(int newDamage) {
		_damage = newDamage;
	}
};