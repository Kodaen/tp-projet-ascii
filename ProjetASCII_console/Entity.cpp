#include <windows.h>

#include "Direction.h"
#include <wincontypes.h>
#include "GameObject.h"
#include "Entity.h"

#include <vector>
#include <string>
#include "BufferHandler.h"

#include "Level.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"

#include "Projectile.h"
#include "GameObject.h"

#include "GameInstance.h"
#pragma comment(lib,"winmm.lib")

Entity::Entity() : GameObject()
{
	_pos = { 11,11 };
	_hp = 1;
	_damage = 1;
	_originalSpriteColor = 0x07;
	_lookingDirection = BOTTOM;
	_displayedColor = 0x07;
	_displayedSprite = 0x45; // The 'E' character. It matches both generic "Enemi" or "Entity".
	_pendingDestruction = false;
}

void Entity::update() {
	// TODO : Implementation
}

void Entity::moveDiagonaly(short valX, short valY) {
	if (valX == 0 && valY == 0) {
		return;
	}

	this->moveRight(valX);
	this->moveDown(valY);

	if (!(valX == 0 && valY == 0)) {
		if (_lookingDirection == TOP) {
			if (valX == 1) {
				_lookingDirection = TOP_RIGHT;
			}
			else {
				_lookingDirection = TOP_LEFT;
			}
		}
		else {
			if (valX == 1) {
				_lookingDirection = BOTTOM_RIGHT;
			}
			else {
				_lookingDirection = BOTTOM_LEFT;
			}
		}
	}
	_displayedColor = _lookingDirection + _originalSpriteColor;
}

void Entity::moveRight(short val) {
	//val can take either 1 or -1
	//1 means go to right
	//-1 means go to left

	if (val == 0) {
		return;
	}

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

	if (val == 0) {
		return;
	}

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
	PlaySound(TEXT("SFX/Normal-Attack.wav"), NULL, SND_FILENAME | SND_ASYNC);
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

	// Search among all gameObjects which one is on the tile (if there is one)
	std::vector<GameObject*>& gameObjects = GameInstance::Instance().getGameObject();

	for (short i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->getPos().Y == tileInFront.Y && gameObjects[i]->getPos().X == tileInFront.X) {
			gameObjects[i]->recieveDamage(_damage);
			return;
		}
	}

};

void Entity::recieveDamage(int damage) {
	_hp -= damage;
	if (_hp <= 0)
	{
		die();
	}
};

void Entity::die(){
	_pendingDestruction = true;
	_originalSpriteColor = 0x08;
}