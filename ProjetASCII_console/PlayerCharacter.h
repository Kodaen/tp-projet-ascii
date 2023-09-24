#pragma once

//#include "Direction.h"
//#include "Entity.h"

class PlayerCharacter : public Entity
{
public :
	//Constructor (for loading save)
	PlayerCharacter(COORD pos, int level, int hp, int damage);

	//Default constructor
	PlayerCharacter();

private:
	int _level;
	//float _xp;

	// Recieves input
	// PlayerController _playercontroller;

public :
	void update();

	// void levelUp();
	// void recieveXp(float xp);

	void die();

	// Getters and Setters
public:

	int getLevel() {
		return _level;
	}

	int setLevel(int newLevel) {
		_level = newLevel;
	}

	//float getXP() {
	//	return _xp;
	//}

	//void setXP(float newXp) {
	//	_xp = newXp;
	//}
};