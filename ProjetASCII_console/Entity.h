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

	WORD _originalSpriteColor = 0x07;
	WORD _displayedColor;
	WCHAR _displayedSprite = 0x40; // 0x40 : @ // 708 for arrow going to top
	

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

	void die();

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

	WORD getOriginalSpriteColor() {
		return _originalSpriteColor;
	}

	void setOriginalSpriteColor(WORD newSpriteColor) {
		_originalSpriteColor = newSpriteColor;
	}

	WORD getDisplayedSpriteColor() {
		return _displayedColor;
	}

	void setDisplayedSpriteColor(WORD newDisplayedColor) {
		_displayedColor = newDisplayedColor;
	}
};