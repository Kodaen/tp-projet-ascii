#include <conio.h>

#include <windows.h>
#include "Direction.h"
#include "Entity.h"

#include <vector>
#include <string>
#include "BufferHandler.h"

#include "Level.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"

#include "PlayerCharacter.h"

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
	_displayedColor = 0x02;
}

void PlayerCharacter::update() {
	_playercontroller.registerPressedKeys();

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
			break;

		case 'q':
			this->moveRight(-1);
			break;

		case 'z':
			this->moveDown(-1);
			break;

		case 's':
			this->moveDown(1);
			break;

		case 'e':
			this->attack();
			break;

		default:
			break;
		}
	}
	
	//char ch = _getch();
	//switch (ch)
	//{
	//case 'd':
	//	this->moveRight(1);
	//	break;

	//case 'q':
	//	this->moveRight(-1);
	//	break;

	//case 'z':
	//	this->moveDown(-1);
	//	break;

	//case 's':
	//	this->moveDown(1);
	//	break;

	//case 'e':
	//	this->attack();
	//	break;

	//default:
	//	break;
	//}
}

void PlayerCharacter::die() {
	// TODO : End of the game ?
	return;
}