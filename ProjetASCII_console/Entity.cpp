#include <windows.h>

#include "Direction.h"
#include <wincontypes.h>
#include "GameObject.h"
#include <vector>
#include <string>
#include "Entity.h"

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
#include "UIWindow.h"
#include "GameUI.h"
#include <time.h>
#include <sstream>
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

// Updates the behavoir of the Entity
void Entity::update() {
}

// Refresh the displayed color by calculating it with the looking direction color and the original sprite color
void Entity::refreshDisplayedColor()
{
	_displayedColor = _lookingDirection + _originalSpriteColor;
}

// Allows the entity to move diagonally on the map, updates the looking direction depending on which direction
// the entity is moving
// Return false if it couldn't move at all
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

// Allows the entity to move horizontally on the map, updates the looking direction depending on which direction
// the entity is moving
// Return false if it couldn't move at all
// 1 means right, -1 means left
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

// Allows the entity to move vertically on the map, updates the looking direction depending on which direction
// the entity is moving
// Return false if it couldn't move at all
// 1 means down, -1 means right
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

// Move the entity by 1 tile on the map depending on which the entity is looking at
// Return false if it couldn't move at all
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

// Changes looking direction and update direction sprite
void Entity::turnToDirection(const DIRECTION& newDirection) {
	_lookingDirection = newDirection;

	refreshDisplayedColor();
}

// Attacks the GameObject in front of the Entity
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
		GameUI::Instance().appendToActionsLog(L"L'attaque au corps à corps vous heurte");
		playerCharacter.recieveDamage(_damage);
	}

	for (short i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->getPos().Y == tileInFront.Y && gameObjects[i]->getPos().X == tileInFront.X) {
			gameObjects[i]->recieveDamage(_damage, _displayedSprite);
			return;
		}
	}

}

// Lowers hp by damages. If hp reach 0 or less, the entity dies (see die()).
void Entity::recieveDamage(const int& damage, WCHAR opponent) {
	_hp -= damage;

	// Negative health is not a valid value.
	if (_hp < 0) {
		_hp = 0;
	}

	// TODO : Playsound when players gets damaged
	if (_hp == 0)
	{
		if (opponent == L'@') {
			std::vector<std::wstring> verbs = { L"abattez", L"achevez", L"tuez" };
			setRandomSentence(verbs);
		}

		die();
	}
	else {
		if (opponent == L'@') {
			std::vector<std::wstring> verbs = { L"estropiez", L"frappez", L"blessez" };
			setRandomSentence(verbs);
		}
	}
};

void Entity::setRandomSentence(const std::vector<std::wstring>& verbs) {
	std::wstring message;
	std::wstringstream stream;
	stream << "Vous ";
	stream << getRandomVerb(verbs);

	switch (_displayedSprite) {
	case L'B':
		stream << " le Cabulosaurus";
		break;
	case L'C':
		stream << " le Croquecaille";
		break;
	case L'S':
		stream << " le Sertrail";
		break;
	default:
		break;
	}

	message.append(stream.str());
	GameUI::Instance().appendToActionsLog(message);
}

std::wstring Entity::getRandomVerb(const std::vector<std::wstring>& verbs) {
	srand(time(nullptr));
	int wordPos = rand() % verbs.size();

	return verbs[wordPos];
}

// Set the attribute _pendingDestruction to true. 
// Before the next update the game instance will check if the
// the ennemy is _pendingDestruction, if yes it will destroy it
void Entity::die() {
	_pendingDestruction = true;
	_originalSpriteColor = 0x08;
}