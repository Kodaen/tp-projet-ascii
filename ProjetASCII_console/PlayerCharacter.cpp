#include <conio.h>

#include <windows.h>
#include "Direction.h"
#include "Entity.h"

#include <vector>
#include <string>
#include "BufferHandler.h"

#include "Level.h"


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
}

void PlayerCharacter::update() {
	// TODO : change _getch to getasynckey
	// Have an input class that get the keys
	// and control player accordingly
	// Axel also said that with the input
	// class I can try to have frames that
	// last the same time, or atleast
	// have a limit of frame
	char ch = _getch();
	switch (ch)
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

	default:
		break;
	}


	// ça marche aussi
	//do {
	//	std::cout << "waiting for input d" << std::endl;
	//} while (!GetAsyncKeyState(0x44));
}