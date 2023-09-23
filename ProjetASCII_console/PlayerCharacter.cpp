#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "BufferHandler.h"
#include "Level.h"
#include "PlayerCharacter.h"
#include "GameInstance.h"


PlayerCharacter::PlayerCharacter()
{
	_pos = { 10,10 };
	_level = 1;
	//_xp = 0.0f;
	_hp = 1;
	_damage = 1;
	_lookingDirection = TOP;
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

void PlayerCharacter::moveDiagonaly(short valX, short valY) {
	// TODO : Check if you can actually go diagonaly
	this->moveRight(valX);
	this->moveDown(valY);

	// TODO : Change direction
}

void PlayerCharacter::moveRight(short val) {
	//val can take either 1 or -1
	//1 means go to right
	//-1 means go to left
	
	if (GameInstance::Instance().getcurrentLevel().isTileWalkable({ _pos.X ,val + _pos.Y }))
	{
		_pos.Y += val;
	}

	if (val == 1) {
		_lookingDirection = RIGHT;
	}
	else {
		_lookingDirection = LEFT;
	}
	_spriteColor = _lookingDirection + 2;
}

void PlayerCharacter::moveDown(short val) {
	//val can take either 1 or -1
	//1 means go down
	//-1 means go up

	// TODO : Check if you can actually go Down or bottom
	if (GameInstance::Instance().getcurrentLevel().isTileWalkable({ val + _pos.X ,_pos.Y }))
	{
		_pos.X += val;
	}
	
	if (val == 1) {
		_lookingDirection = BOTTOM;
	}
	else {
		_lookingDirection = TOP;
	}
	_spriteColor = _lookingDirection + 2;
}

void PlayerCharacter::attack() {
	// TODO : implementation

};

void PlayerCharacter::recieveDamage() {
	// TODO : implementation
};