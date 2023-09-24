#include <windows.h>
#include <vector>
#include <string>

#include "Level.h"

#include "Direction.h"
#include <wincontypes.h>
#include "Entity.h"

#include "PlayerCharacter.h"

#include "BufferHandler.h"

#include "gameInstance.h"

GameInstance* GameInstance::_gameInstance = 0;

GameInstance::GameInstance(PlayerCharacter mainChar) : _currentLevel("levels/level1.txt"), _playerCharacter(mainChar){
	_entities = std::vector<Entity>();
}

GameInstance::~GameInstance() {
	_gameInstance = nullptr;
}


GameInstance& GameInstance::Instance()
{
	if (!_gameInstance)
	{
		PlayerCharacter* MainChar = new PlayerCharacter();
		_gameInstance = new GameInstance(*MainChar);
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

	for (short i = 0; i < _entities.size(); i++)
	{
		if (_entities[i].isPendingDestruction())
		{
			_entities.erase(_entities.begin() + i);
			continue;
		}
		_entities[i].update();

		BufferHandler::Instance().drawAtCoordinate(_entities[i].getSprite(),
			_entities[i].getDisplayedSpriteColor(),
			{ _entities[i].getPos().X, _entities[i].getPos().Y });
	}


}

