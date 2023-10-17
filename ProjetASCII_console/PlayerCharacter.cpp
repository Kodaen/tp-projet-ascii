#include <conio.h>

#include <windows.h>
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"

#include <vector>
#include <string>
#include <map>
#include "BufferHandler.h"

#include "Level.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"

#include "PlayerCharacter.h"

#include "UIWindow.h"
#include "GameUI.h"

#include "GameInstance.h"


PlayerCharacter::PlayerCharacter()
{
	_pos = { 10,10 };
	_level = 1;
	//_xp = 0.0f;
	_originalSpriteColor = 0x02;
	_hp = 1;
	_damage = 1;
	_lookingDirection = BOTTOM_LEFT;
	_displayedSprite = 0x40; // The @ character. It is reserved for the player.
	_displayedColor = 0x02;
	_playerActed = false;
	_isOnStairs = false;
	_nextTile = _pos;
}

// Update player's behavoir; called every frame.
// It receives inputs from the player and act accordingly (move/attack).
// If the game is paused or the player is pendingDestruction : doesn't do anything.
void PlayerCharacter::update() {
	if (_pendingDestruction ||
		GameInstance::Instance().isGamePaused())
	{
		return;
	}
	_playercontroller.registerPressedKeys();
	_playerActed = false;

	std::set<char> inputKeys = _playercontroller.getPressedKeys();

	// if played didn't press any key, then just return
	if (inputKeys.size() == 0) return;

	// otherwise switch on which key he pressed
	if (inputKeys.size() == 1) {
		std::set<char>::iterator it = inputKeys.begin();

		// Check if the next tile is a stair before moving the player.
		setNextTile(it);
		BufferHandler& bufferHandler = BufferHandler::Instance();
		WCHAR nextTileChar = bufferHandler.getCharacterAtCoordinate(_nextTile);
		_isOnStairs = bufferHandler.isStair(nextTileChar);

		// Update player position.
		switch (*it)
		{
		case 'd':
			this->moveRight(1);
			_playerActed = true;
			break;

		case 'q':
			this->moveRight(-1);
			_playerActed = true;
			break;

		case 'z':
			this->moveDown(-1);
			_playerActed = true;
			break;

		case 's':
			this->moveDown(1);
			_playerActed = true;
			break;

		case 'e':
			this->attack();
			_playerActed = true;
			break;

		default:
			break;
		}
	}
}

// Set what the nextTile the player is going to move to during the frame
void PlayerCharacter::setNextTile(const std::set<char>::iterator& it) {
	switch (*it)
	{
	case 'd':
		_nextTile = { _pos.X ,1 + _pos.Y };
		break;
	case 'q':
		_nextTile = { _pos.X ,-1 + _pos.Y };
		break;
	case 'z':
		_nextTile = { -1 + _pos.X ,_pos.Y };
		break;
	case 's':
		_nextTile = { 1 + _pos.X ,_pos.Y };
		break;
	default:
		break;
	}
}

// Set the attribute _pendingDestruction to true. 
// End the game and display the game over menu window.
void PlayerCharacter::die() {
	_pendingDestruction = true;
	GameInstance::Instance().pauseGame(true);
	GameUI::Instance().activateUIWindow(GAMEOVER);
}