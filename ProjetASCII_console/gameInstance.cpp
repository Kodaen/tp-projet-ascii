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

#include "UIWindow.h"
#include "GameUI.h"

#include "gameInstance.h"
#include "Croquecaille.h"
#include "Cabulosaurus.h"

#include <functional>

GameInstance* GameInstance::_gameInstance = 0;

GameInstance::GameInstance() : _currentLevel(1), _gameEnd(false) {
	PlayerCharacter* playerCharacter = new PlayerCharacter();
	_playerCharacter = *playerCharacter;
	_gameObjects = std::vector<GameObject*>();
	spawnLevelEnemies();
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
		_gameInstance = new GameInstance();
	}
	return *_gameInstance;
}

void GameInstance::update() {
	// Update player
	_playerCharacter.update();

	BufferHandler& bufferHandler = BufferHandler::Instance();

	// Update buffer to display player
	bufferHandler.drawAtCoordinate(_playerCharacter.getSprite(),
		_playerCharacter.getDisplayedSpriteColor(),
		{ _playerCharacter.getPos().X, _playerCharacter.getPos().Y });

	// Update all gameObjects
	for (short i = 0; i < _gameObjects.size(); i++)
	{
		// Check if the gameObject died during the frame
		while (_gameObjects[i]->isPendingDestruction())
		{
			delete _gameObjects[i];
			_gameObjects.erase(_gameObjects.begin() + i);

			// We decrease by 1 the index because erasing _gameObjects[i]
			// means that the new _gameObjects[i] is the former _gameObjects[i+1]
			// It avoids skipping a gameobject during the frame
			if (i >= 1) {
				--i;
			}

			// If we don't have any gameObjects in the scene because they all died
			// during the frame, we simply return
			if (_gameObjects.empty()) {
				return;
			}
		}

		// Only update gameObject if player acted (i.e. moved/attacked)
		// since it's a turn based game
		if (_playerCharacter.hasPlayerActed()) {
			_gameObjects[i]->update();
		}

		// Update buffer to display gameObject
		bufferHandler.drawAtCoordinate(_gameObjects[i]->getSprite(),
			_gameObjects[i]->getDisplayedSpriteColor(),
			{ _gameObjects[i]->getPos().X, _gameObjects[i]->getPos().Y });
	}

	// Change floor when the player chooses to use the stairs.
	if (_playerCharacter.isOnStairs()) {
		int currentLevelNumber = _currentLevel.getNumber();
		currentLevelNumber++;
		_currentLevel = Level(currentLevelNumber);
		GameUI::Instance().appendToActionsLog(L"Vous prenez l'escalier");
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

	GameUI::Instance().deactivateUIWindow();

	spawnLevelEnemies();

	setPlayerColors();
}

void GameInstance::setPlayerColors() {
	std::map<std::wstring, WORD> colors = _currentLevel.getColors();
	_playerCharacter.setOriginalSpriteColor(colors[L"player"] | colors[L"groundBg"]); // TODO: Or default.
	_playerCharacter.setDisplayedSpriteColor(colors[L"player"] | colors[L"groundBg"]);
}

void GameInstance::endOfGame()
{
	_playerCharacter.setPendingDestruction(true);
	GameUI::Instance().activateUIWindow(VICTORY);
}

void GameInstance::spawnLevelEnemies()
{
	std::function<void(GameInstance*, short, short)> ptrTryToSpawnEntityFromLevel;

	// Choose what type of ennemy we want depending on the level number
	switch (_currentLevel.getNumber())
	{
	case 1:
		ptrTryToSpawnEntityFromLevel = std::mem_fn(&GameInstance::tryToSpawnEntityFromLevel<Croquecaille, Cabulosaurus>);
		break;
	default:
		ptrTryToSpawnEntityFromLevel = std::mem_fn(&GameInstance::tryToSpawnEntityFromLevel<Entity, Entity>);
		break;
	}

	// For every tile in the map, we look for spawners and try to spawn ennemy at their position
	for (size_t x = 0; x < _currentLevel.getLevel().size(); x++)
	{
		for (size_t y = 0; y < _currentLevel.getLevel()[x].size(); y++)
		{
			ptrTryToSpawnEntityFromLevel(this, x, y);
		}
	}

	// Update ennemy's color to match the level
	std::map<std::wstring, WORD> colors = getcurrentLevel().getColors();
	for (auto gameObject : _gameObjects) {
		gameObject->setOriginalSpriteColor(colors[L"gameObjects"] | colors[L"groundBg"]);
		gameObject->refreshDisplayedColor();
	}
}

// We use a template to avoid writting multiple functions doing the same thing
// Plus it's quicker to change what ennemies we want for the level with this method
template <typename standardEnnemy, typename bossEnnemy>
void GameInstance::tryToSpawnEntityFromLevel(short x, short y)
{
	GameObject* c;

	// Each letter corresponds to the direction the ennemy is going to look at
	// A Z E
	// Q   D
	// W X C
	// I chose those characters because on AZERTY keyboards it's easier to see which
	// letter corresponds to which direction (for instance : a = TOP_LEFT 
	// because that's the one on the top left of the keyboard)
	switch (_currentLevel.getLevel()[x][y])
	{
		// Lowercase for standard ennemis
	case L'a':
		c = new standardEnnemy({ x,y }, TOP_LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'q':
		c = new standardEnnemy({ x,y }, LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'w':
		c = new standardEnnemy({ x,y }, BOTTOM_LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'x':
		c = new standardEnnemy({ x,y }, BOTTOM);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'c':
		c = new standardEnnemy({ x,y }, BOTTOM_RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'd':
		c = new standardEnnemy({ x,y }, RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'e':
		c = new standardEnnemy({ x,y }, TOP_RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'z':
		c = new standardEnnemy({ x,y }, TOP);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

		// Uppercase for boss ennemis
	case L'A':
		c = new bossEnnemy({ x,y }, TOP_LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'Q':
		c = new bossEnnemy({ x,y }, LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'W':
		c = new bossEnnemy({ x,y }, BOTTOM_LEFT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'X':
		c = new bossEnnemy({ x,y }, BOTTOM);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'C':
		c = new bossEnnemy({ x,y }, BOTTOM_RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'D':
		c = new bossEnnemy({ x,y }, RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'E':
		c = new bossEnnemy({ x,y }, TOP_RIGHT);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	case L'Z':
		c = new bossEnnemy({ x,y }, TOP);
		_gameObjects.push_back(c);
		_currentLevel.hideSpawner({ x,y });
		break;

	default:
		break;
	}
}

void GameInstance::resetLevel()
{
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->setPendingDestruction(true);
	}

	std::map<std::wstring, WORD> colors = getcurrentLevel().getColors();
	_playerCharacter.setOriginalSpriteColor(colors[L"player"] | colors[L"groundBg"]);
	_playerCharacter.setDisplayedSpriteColor(colors[L"player"] | colors[L"groundBg"]);
	// TODO: gameObjects colors.
}