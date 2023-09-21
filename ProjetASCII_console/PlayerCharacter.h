#pragma once

//#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>

enum DIRECTION
{
	TOP			= 1024,	
	TOP_RIGHT	= 5120,	
	RIGHT		= 4096,	
	BOTTOM_RIGHT= 36864,	
	BOTTOM		= 40960,	
	BOTTOM_LEFT	= 34816,
	LEFT		= 2048,		
	TOP_LEFT	= 3072,		
};

class PlayerCharacter
{
public :
	//Constructor (for loading save)
	PlayerCharacter(COORD pos, int level, int hp, int damage);

	//Default constructor
	PlayerCharacter();

private:
	COORD _pos;
	int _level;
	int _hp;
	//float _xp;
	int _damage;

	WCHAR _displayedSprite = 0x40; // 0x40 : @ // 708 for arrow going to top
	WORD _spriteColor = 0x02;

	// Direction the character is looking (ENUM)
	 DIRECTION _lookingDirection;

	// Recieves input
	// PLAYERCONTROLLER _playercontroller;

public :
	void update();

	// Moving functions
	void moveRight(short val);
	void moveDown(short val);
	void moveDiagonaly(short valX, short valY);

	// Attack and recieve damage functions
	void attack();
	void recieveDamage();

	// void levelUp();
	// void recieveXp(float xp);

	// Getters and Setters
public:
	COORD getPos() {
		return _pos;
	}

	void setPos(COORD newPos) {
		_pos = newPos;
	}

	int getLevel() {
		return _level;
	}

	void setPos(int newLevel) {
		_level = newLevel;
	}

	int getHP() {
		return _hp;
	}

	void setHP(int newHp) {
		_hp = newHp;
	}

	//float getXP() {
	//	return _xp;
	//}

	//void setXP(float newXp) {
	//	_xp = newXp;
	//}

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