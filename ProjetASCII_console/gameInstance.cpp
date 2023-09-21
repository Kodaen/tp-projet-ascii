#include "Level.h"
#include "PlayerCharacter.h"

#include "gameInstance.h"
#include "BufferHandler.h"

GameInstance* GameInstance::_gameInstance = 0;

GameInstance::GameInstance(PlayerCharacter mainChar) : _currentLevel("levels/level1.txt"), _playerCharacter(mainChar){
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
		_playerCharacter.getSpriteColor(),
		{ _playerCharacter.getPos().X, _playerCharacter.getPos().Y });
}

