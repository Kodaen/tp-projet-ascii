#pragma once

//#include "Direction.h"
//#include "GameObject.h"
//#include "Entity.h"
//#include "PlayerController.h"
//#include <string>
//#include <vector>s

class PlayerCharacter : public Entity
{
	//////////////////////// Constructors ////////////////////////
public:

	PlayerCharacter();

	//////////////////////// Attributes ////////////////////////
private:
	int _level;

	COORD _nextTile;

	// Recieves input
	PlayerController _playercontroller;
	bool _playerActed;
	bool _isOnStairs;

	//////////////////////// Methods ////////////////////////

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

	//////////////////////// Getters & Setters ////////////////////////
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