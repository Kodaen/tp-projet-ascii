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
}

void PlayerCharacter::update() {
	if (_pendingDestruction)
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

void PlayerCharacter::die() {
	_pendingDestruction = true;
	GameUI::Instance().activateGameOverScreen(true);
}

// TODO : override recieveDamage to update UI when getting hit