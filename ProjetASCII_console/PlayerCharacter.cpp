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
		//std::cout << "moving to right" << std::endl;
		this->moveRight(1);
		//std::cout << "x :" << this->getPos().X << std::endl << "y :" << this->getPos().Y << std::endl;
		break;

	case 'q':
		//std::cout << "moving to left" << std::endl;
		this->moveRight(-1);
		//std::cout << "x :" << this->getPos().X << std::endl << "y :" << this->getPos().Y << std::endl;
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
	this->moveTop(valY);

	// TODO : Change direction
}

void PlayerCharacter::moveRight(int val) {
	// TODO : Check if you can actually go to the right
	_pos.Y += val;

	// TODO : Change direction
}

void PlayerCharacter::moveTop(int val) {
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