#pragma once

//#include "GameObject.h"
//#include <windows.h>
//#include "Entity.h"
//#include "PlayerCharacter.h"
//#include "vector"
//include "Level.h"

class GameInstance
{
	//////////////////////// Constructors ////////////////////////
private:
	GameInstance();

public:
	~GameInstance();

	// Get Instance

	static GameInstance& Instance();

	//////////////////////// Attributes ////////////////////////

private:

	Level _currentLevel;

	PlayerCharacter _playerCharacter;

	std::vector<GameObject*> _gameObjects;

	bool _gameEnd;

	bool _pause;

public:
	static GameInstance* _gameInstance;

	//////////////////////// Methods ////////////////////////
public:
	void update();

	void restartGame();
	void resetLevel();
	void endOfGame();

	inline void setPlayerColors();
	inline void setGameObjectsColors();

private:
	void spawnLevelEnemies();

	template <typename standardEnnemy, typename bossEnnemy>
	void tryToSpawnEntityFromLevel(short x, short y);
	void changeFloorIfNeeded();

	//////////////////////// Getters and Setters ////////////////////////
public:
	// TODO : make a function getCurrentLevelRef
	inline Level& getCurrentLevel() {
		return _currentLevel;
	};

	inline void setCurrentLevel(Level& newCurrentLevel) {
		_currentLevel = newCurrentLevel;
	};

	// TODO : make a function getPlayerCharacterRef
	inline PlayerCharacter& getPlayerCharacter() {
		return _playerCharacter;
	};

	inline void setPlayerCharacter(const PlayerCharacter& newPlayerCharacter) {
		_playerCharacter = newPlayerCharacter;
	};

	std::vector<GameObject*>& getGameObject() {
		return _gameObjects;
	}

	std::vector<Entity*>& getEntites() {
		std::vector<Entity*>* entities = new std::vector<Entity*>();

		for (size_t i = 0; i < _gameObjects.size(); i++)
		{
			Entity* entity = dynamic_cast<Entity*>(_gameObjects[i]);
			if (entity) {
				entities->push_back(entity);
			}
		}

		return *(entities);
	}

	inline void setGameObjects(const std::vector<GameObject*>& newGameObjects) {
		_gameObjects = newGameObjects;
	}

	inline void finishGame() {
		_gameEnd = true;
	}

	inline bool isGameFinished() {
		return _gameEnd;
	}

	inline void pauseGame(const bool& boolean) {
		_pause = boolean;
	}

	inline bool isGamePaused() {
		return _pause;
	}
};