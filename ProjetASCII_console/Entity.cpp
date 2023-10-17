#include <windows.h>

#include "Direction.h"
#include <wincontypes.h>
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

	refreshDisplayedColor();
}

Entity::Entity(COORD pos, DIRECTION lookingDirection) : Entity()
{
	_pos = pos;
	_lookingDirection = lookingDirection;

	refreshDisplayedColor();
}

void Entity::update() {
}

void Entity::refreshDisplayedColor()
{
	_displayedColor = _lookingDirection + _originalSpriteColor;
}

bool Entity::moveDiagonaly(const short& valX, const short& valY) {
	//returns if character could move or not as a bool

	if (valX == 0 && valY == 0) {
		return false;
	}

	bool entityMoved = moveRight(valY);
	entityMoved = moveDown(valX) || entityMoved;

	if (!(valX == 0 && valY == 0)) {
		if (_lookingDirection == TOP) {
			if (valY == 1) {
				turnToDirection(TOP_RIGHT);
			}
			else {
				turnToDirection(TOP_LEFT);
			}
		}
		else {
			if (valY == 1) {
				turnToDirection(BOTTOM_RIGHT);
			}
			else {
				turnToDirection(BOTTOM_LEFT);
			}
		}
	}

	// check if entity moved
	if (entityMoved)
	{
		return true;
	}
	else {
		return false;
	}

}

bool Entity::moveRight(const short& val) {
	//val can take either 1 or -1
	//1 means go to right
	//-1 means go to left

	//returns if character could move or not as a bool

	if (val == 0) {
		return false;
	}

	if (val == 1) {
		turnToDirection(RIGHT);
	}
	else {
		turnToDirection(LEFT);
	}

	if (GameInstance::Instance().getCurrentLevel().isTileWalkable({ _pos.X ,val + _pos.Y }))
	{
		_pos.Y += val;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::moveDown(const short& val) {
	//val can take either 1 or -1
	//1 means go down
	//-1 means go up

	//returns if character could move or not as a bool

	if (val == 0) {
		return false;
	}

	if (val == 1) {
		turnToDirection(BOTTOM);
	}
	else {
		turnToDirection(TOP);
	}

	if (GameInstance::Instance().getCurrentLevel().isTileWalkable({ val + _pos.X ,_pos.Y }))
	{
		_pos.X += val;
		return true;
	}
	else {
		return false;
	}

}

bool Entity::moveForward() {
	// Move to its looking direction

	//returns if character could move or not as a bool

	switch (_lookingDirection)
	{
	case TOP:
		return moveDown(-1);
		break;
	case TOP_RIGHT:
		return moveDiagonaly(-1, 1);
		break;
	case RIGHT:
		return moveRight(1);
		break;
	case BOTTOM_RIGHT:
		return moveDiagonaly(1, 1);
		break;
	case BOTTOM:
		return moveDown(1);
		break;
	case BOTTOM_LEFT:
		return moveDiagonaly(1, -1);
		break;
	case LEFT:
		return moveRight(-1);
		break;
	case TOP_LEFT:
		return moveDiagonaly(-1, -1);
		break;
	default:
		return false;
		break;
	}
}

void Entity::turnToDirection(const DIRECTION& newDirection) {
	_lookingDirection = newDirection;

	refreshDisplayedColor();
}

void Entity::attack() {
	// TODO : playsound when player attacks

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

	PlayerCharacter& playerCharacter = GameInstance::Instance().getPlayerCharacter();

	// Search among all gameObjects which one is on the tile (if there is one)
	std::vector<GameObject*>& gameObjects = GameInstance::Instance().getGameObject();

	if (playerCharacter.getPos().Y == tileInFront.Y && playerCharacter.getPos().X == tileInFront.X) {
		playerCharacter.recieveDamage(_damage);
	}

	for (short i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->getPos().Y == tileInFront.Y && gameObjects[i]->getPos().X == tileInFront.X) {
			gameObjects[i]->recieveDamage(_damage);
			return;
		}
	}

};

void Entity::recieveDamage(const int& damage) {
	_hp -= damage;
	// TODO : Playsound when players gets damaged
	if (_hp <= 0)
	{
		die();
	}
};

void Entity::die() {
	_pendingDestruction = true;
	_originalSpriteColor = 0x08;
}