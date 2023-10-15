#pragma once

//#include "Direction.h"
//#include "GameObject.h"
//#include "Entity.h"
//#include "PlayerController.h"

class PlayerCharacter : public Entity
{
public:
	//Constructor (for loading save)
	PlayerCharacter(COORD pos, int level, int hp, int damage);

	//Default constructor
	PlayerCharacter();

private:
	int _level;
	//float _xp;

	COORD _nextTile;

	// Recieves input
	PlayerController _playercontroller;
	bool _playerActed;
	bool _isOnStairs;


	void setNextTile(std::set<char>::iterator& it);

public:
	void update();

	// void levelUp();
	// void recieveXp(float xp);

	bool isOnStairs() {
		return _isOnStairs;
	}

	void setIsOnStairs(bool isOnStairs) {
		_isOnStairs = isOnStairs;
	}

	void die();

	// Getters and Setters
public:

	int getLevel() {
		return _level;
	}

	int setLevel(int newLevel) {
		_level = newLevel;
	}

	bool hasPlayerActed() {
		return _playerActed;
	}

	//float getXP() {
	//	return _xp;
	//}

	//void setXP(float newXp) {
	//	_xp = newXp;
	//}
};