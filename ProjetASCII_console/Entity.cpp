#include <windows.h>

#include "Direction.h"
#include <wincontypes.h>
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

Entity::Entity()
{
	_pos = { 11,11 };
	_hp = 1;
	_damage = 1;
	_originalSpriteColor = 0x07;
	_lookingDirection = BOTTOM_LEFT;
	_displayedColor = 0x07;
	_pendingDestruction = false;
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
	_displayedColor = _lookingDirection + _originalSpriteColor;
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
	_displayedColor = _lookingDirection + _originalSpriteColor;
}

void Entity::attack() {
	// Get tile in front of character
	COORD tileInFront = _pos;
	switch (_lookingDirection)
	{
	case TOP:
		--tileInFront.X;
		break;
	case TOP_RIGHT:
		--tileInFront.X;
		++tileInFront.Y;
		break;
	case RIGHT:
		++tileInFront.Y;
		break;
	case BOTTOM_RIGHT:
		++tileInFront.Y;
		++tileInFront.X;
		break;
	case BOTTOM:
		++tileInFront.X;
		break;
	case BOTTOM_LEFT:
		--tileInFront.Y;
		++tileInFront.X;
		break;
	case LEFT:
		--tileInFront.Y;
		break;
	case TOP_LEFT:
		--tileInFront.Y;
		--tileInFront.X;
		break;
	default:
		return;
	}

	// Search among all entities which one is on the tile (if there is one)
	std::vector<Entity>& entities = GameInstance::Instance().getEntites();

	for (short i = 0; i < entities.size(); i++)
	{
		if (entities[i].getPos().Y == tileInFront.Y && entities[i].getPos().X == tileInFront.X) {
			entities[i].recieveDamage(_damage);
			return;
		}
	}

};

void Entity::recieveDamage(int Damage) {
	--_hp;
	if (_hp <= 0)
	{
		die();
	}
};

void Entity::die(){
	_pendingDestruction = true;
	_originalSpriteColor = 0x08;
}