#pragma once

//#include <windows.h>
//#include "PlayerCharacter.h"
//#include "vector.h"

class GameInstance
{
	// Constructor and Destructor
private:
	GameInstance(PlayerCharacter mainChar);

public :
	~GameInstance();
	
	// Get Instance

	static GameInstance& Instance();

	// Attributes

private:

	Level _currentLevel;

	PlayerCharacter _playerCharacter;

	std::vector<Entity> _entities;
 
public:
	static GameInstance* _gameInstance;

	// Functions
private:


public:
	void update();

	// Getters and Setters

	Level& getcurrentLevel() {
		return _currentLevel;
	};

	void setCurrentLevel(Level &newCurrentLevel) {
		_currentLevel = newCurrentLevel;
	};

	PlayerCharacter& getPlayerCharacter() {
		return _playerCharacter;
	};

	void setPlayerCharacter(PlayerCharacter &newPlayerCharacter) {
		_playerCharacter = newPlayerCharacter;
	};

	std::vector<Entity>& getEntites() {
		return _entities;
	}

	void setEntities(std::vector<Entity> newEntities){
		_entities = newEntities;
	}
};

