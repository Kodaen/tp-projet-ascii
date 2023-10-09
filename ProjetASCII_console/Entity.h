#pragma once

//#include <wincontypes.h>
//#include "Direction.h"
//#include "GameObject.h"

class Entity : public GameObject
{
public:
	//Constructor (for loading save)
	Entity(COORD pos, int hp, int damage);

	//Default constructor
	Entity();

protected:
	int _hp;
	int _damage;
	
	// Direction the character is looking (ENUM)
	DIRECTION _lookingDirection;

public:
	virtual void update();

	// Moving functions
	void moveRight(short val);
	void moveDown(short val);
	void moveDiagonaly(short valX, short valY);

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