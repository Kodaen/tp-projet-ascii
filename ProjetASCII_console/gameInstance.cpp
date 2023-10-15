#include <windows.h>
#include <vector>
#include <string>
#include <map>

#include "Level.h"

#include "Direction.h"
#include <wincontypes.h>
#include "GameObject.h"
#include "Entity.h"


#include "GameObject.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"

#include "BufferHandler.h"

#include "GameUI.h"

#include "gameInstance.h"

GameInstance* GameInstance::_gameInstance = 0;

GameInstance::GameInstance(PlayerCharacter mainChar) : _currentLevel(1), _playerCharacter(mainChar), _gameEnd(false) {
	_gameObjects = std::vector<GameObject*>();
}

GameInstance::~GameInstance() {
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		delete _gameObjects[i];
	}
	_gameObjects.clear();
}


GameInstance& GameInstance::Instance()
{
	if (!_gameInstance)
	{
		PlayerCharacter MainChar;
		_gameInstance = new GameInstance(MainChar);
	}
	return *_gameInstance;
}

void GameInstance::update() {
	// Update player
	_playerCharacter.update();

	// Update buffer to display player
	BufferHandler::Instance().drawAtCoordinate(_playerCharacter.getSprite(),
		_playerCharacter.getDisplayedSpriteColor(),
		{ _playerCharacter.getPos().X, _playerCharacter.getPos().Y });

	// Update all gameObjects
	for (short i = 0; i < _gameObjects.size(); i++)
	{
		// Check if the gameObject died during the frame
		if (_gameObjects[i]->isPendingDestruction())
		{
			delete _gameObjects[i];
			_gameObjects.erase(_gameObjects.begin() + i);
			continue;
		}

		// Only update gameObject if player acted (i.e. moved/attacked)
		// since it's a turn based game
		if (_playerCharacter.hasPlayerActed()) {
			_gameObjects[i]->update();
		}

		// Update buffer to display gameObject
		BufferHandler::Instance().drawAtCoordinate(_gameObjects[i]->getSprite(),
			_gameObjects[i]->getDisplayedSpriteColor(),
			{ _gameObjects[i]->getPos().X, _gameObjects[i]->getPos().Y });
	}


}

void GameInstance::restartGame()
{
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->setPendingDestruction(true);
	}
	_playerCharacter = PlayerCharacter();

	_currentLevel = Level(1);

	GameUI::Instance().activateGameOverScreen(false);

}