#include <iostream>
#include <conio.h>
#include <windows.h>

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	_pos = { 10,10 };
	_level = 1;
	//_xp = 0.0f;
	_hp = 1;
	_damage = 1;
}

void PlayerCharacter::update() {
	//Get input and make action accordingly
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

void PlayerCharacter::moveDiagonaly(int valX, int valY) {
	// TODO : Check if you can actually go to the right
	this->moveRight(valX);
	this->moveDown(valY);

	// TODO : Change direction
}

void PlayerCharacter::moveRight(int val) {
	// TODO : Check if you can actually go to the right
	_pos.Y += val;

	// TODO : Change direction
}

void PlayerCharacter::moveDown(int val) {
	// TODO : Check if you can actually go to the right
	_pos.X += val;

	// TODO : Change direction
}

void PlayerCharacter::attack() {
	// TODO : implementation
};

void PlayerCharacter::recieveDamage() {
	// TODO : implementation
};