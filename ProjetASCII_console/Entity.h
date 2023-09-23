#pragma once

//#include <wincontypes.h>
//#include "Direction.h"

class Entity
{
public:
	//Constructor (for loading save)
	Entity(COORD pos, int hp, int damage);

	//Default constructor
	Entity();

protected:
	COORD _pos;
	int _hp;
	int _damage;

	WCHAR _displayedSprite = 0x40; // 0x40 : @ // 708 for arrow going to top
	WORD _spriteColor = 0x07;

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
	void recieveDamage();

	// Getters and Setters
public:
	COORD getPos() {
		return _pos;
	}

	void setPos(COORD newPos) {
		_pos = newPos;
	}

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


	WCHAR getSprite() {
		return _displayedSprite;
	}

	void setSprite(int newSprite) {
		_displayedSprite = newSprite;
	}

	WORD getSpriteColor() {
		return _spriteColor;
	}

	void setSpriteColor(WORD newSpriteColor) {
		_spriteColor = newSpriteColor;
	}
};