#pragma once

//#include "Direction.h"
//#include "GameObject.h"
//#include "Entity.h"
//#include "PlayerController.h"

class PlayerCharacter : public Entity
{
public:
	//Default constructor
	PlayerCharacter();

private:
	int _level;

	COORD _nextTile;

	// Recieves input
	PlayerController _playercontroller;
	bool _playerActed;
	bool _isOnStairs;


	void setNextTile(const std::set<char>::iterator& it);

public:
	void update();

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

	int setLevel(const int& newLevel) {
		_level = newLevel;
	}

	bool hasPlayerActed() {
		return _playerActed;
	}

};