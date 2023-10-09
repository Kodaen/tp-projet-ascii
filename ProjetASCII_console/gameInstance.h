#pragma once

//#include "GameObject.h"
//#include <windows.h>
//#include "PlayerCharacter.h"
//#include "vector"
//include "Level.h"

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

	std::vector<GameObject*> _gameObjects;

public:
	static GameInstance* _gameInstance;

	// Functions
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

	std::vector<GameObject*>& getGameObject() {
		return _gameObjects;
	}

	std::vector<Entity*>& getEntites() {
		std::vector<Entity*> *entities = new std::vector<Entity*>();

		for (size_t i = 0; i < _gameObjects.size(); i++)
		{
			Entity* entity = dynamic_cast<Entity*>(_gameObjects[i]);
			if (entity) {
				entities->push_back(entity);
			}
		}

		return *(entities);
	}

	void setGameObjects(std::vector<GameObject*> newGameObjects){
		_gameObjects = newGameObjects;
	}
};