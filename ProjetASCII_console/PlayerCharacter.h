#pragma once

//#include <windows.h>

enum DIRECTION
{
	TOP,
	RIGHT,
	LEFT,
	BOTTOM
};

class PlayerCharacter
{
public :
	//Constructor
	PlayerCharacter(COORD pos, int level, int hp, int damage);

	//Default constructor
	PlayerCharacter();

private:
	COORD _pos;
	int _level;
	int _hp;
	//float _xp;
	int _damage;

	WCHAR _displayedSprite = 0x40; // @

	// Direction the character is looking (ENUM)
	// DIRECTION _lookingDirection;

	// Recieves input
	// PLAYERCONTROLLER _playercontroller;

public :
	void update();

	// Moving functions
	void moveRight(int val);
	void moveDown(int val);
	void moveDiagonaly(int valX, int valY);

	// Attack and recieve damage functions
	void attack();
	void recieveDamage();

	void levelUp();
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


};