#include <windows.h>

#include "Direction.h"
#include <wincontypes.h>
#include "Entity.h"

#include <vector>
#include <string>
#include "BufferHandler.h"

#include "Level.h"

#include "PlayerCharacter.h"

#include "GameInstance.h"

Entity::Entity()
{
	_pos = { 11,11 };
	_hp = 1;
	_damage = 1;
	_lookingDirection = TOP;
}

void Entity::update() {
	// TODO : Implementation
}

void Entity::moveDiagonaly(short valX, short valY) {
	// TODO : Check if you can actually go diagonaly
	this->moveRight(valX);
	this->moveDown(valY);

	// TODO : Change direction
}

void Entity::moveRight(short val) {
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

void Entity::moveDown(short val) {
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

void Entity::attack() {
	// TODO : implementation

};

void Entity::recieveDamage() {
	// TODO : implementation
};