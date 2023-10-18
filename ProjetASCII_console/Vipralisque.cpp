#include <windows.h>

#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include <string>
#include <vector>
#include "Entity.h"
#include "Vipralisque.h"
#include "Projectile.h"

#include <set>
#include <string>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"

#include <map>
#include "Level.h"
#include "gameInstance.h"
#include "ExplosiverVenom.h"

Vipralisque::Vipralisque() : _currentStep(0), Entity()
{
	_lookingDirection = TOP;
	_displayedSprite = 0x56; // Letter V, matches Vipralisque
	_originalSpriteColor = 0x0C; // Pink
	changedTrajectory = false;
	_damage = 50;

	calculateShootingDirection();

	_displayedColor = _lookingDirection + _originalSpriteColor;
	
}

Vipralisque::Vipralisque(const COORD& pos, const DIRECTION& lookingDirection) : Vipralisque()
{
	_pos = pos;
	_lookingDirection = lookingDirection;

	calculateShootingDirection();

	_displayedColor = _lookingDirection + _originalSpriteColor;
}

// Update Vipralisque's behavoir; called every frame.
// Every call, the Vipralisque will try to move forward and attack in front of him
// Every 3 call he will turnback and spit a ExplosiverVenom project (always in the same direction)
void Vipralisque::update() {

	attack();
	moveForward();

	
	switch (_currentStep)
	{
	case 1:
		shootExplosiveVenom();
		turnOver();
	default:
		break;
	}

	_currentStep = (1 + _currentStep) % 3;
}


// Changes the looking direction to the invert
void Vipralisque::turnOver()
{
	switch (_lookingDirection)
	{
	case TOP:
		turnToDirection(BOTTOM);
		break;
	case LEFT:
		turnToDirection(RIGHT);
		break;
	case TOP_LEFT:
		turnToDirection(BOTTOM_RIGHT);
		break;
	case RIGHT:
		turnToDirection(LEFT);
		break;
	case TOP_RIGHT:
		turnToDirection(BOTTOM_LEFT);
		break;
	case BOTTOM:
		turnToDirection(TOP);
		break;
	case BOTTOM_LEFT:
		turnToDirection(TOP_RIGHT);
		break;
	case BOTTOM_RIGHT:
		turnToDirection(TOP_LEFT);
		break;
	default:
		break;
	}
}

// Calculate the shooting direction using the looking direction
// the shooting direction is 90° to the right of the original
// looking direction.
void Vipralisque::calculateShootingDirection()
{
	switch (_lookingDirection)
	{
	case TOP:
		_shootingDirection = RIGHT;
		break;
	case LEFT:
		_shootingDirection = TOP;
		break;
	case TOP_LEFT:
		_shootingDirection = TOP_RIGHT;
		break;
	case RIGHT:
		_shootingDirection = BOTTOM;
		break;
	case TOP_RIGHT:
		_shootingDirection = BOTTOM_RIGHT;
		break;
	case BOTTOM:
		_shootingDirection = LEFT;
		break;
	case BOTTOM_LEFT:
		_shootingDirection = TOP_LEFT;
		break;
	case BOTTOM_RIGHT:
		_shootingDirection = BOTTOM_LEFT;
		break;
	default:
		break;
	}
}

// Shoots an ExplosiverVenom in the shooting direction.
void Vipralisque::shootExplosiveVenom()
{

	// Calculate the moving direction of the projectile using the looking
	// direction on the Vipralisque
	COORD direction = { 0,0 };
	switch (_shootingDirection)
	{
	case TOP:
		--direction.X;
		break;
	case TOP_RIGHT:
		--direction.X;
		++direction.Y;
		break;
	case RIGHT:
		++direction.Y;
		break;
	case BOTTOM_RIGHT:
		++direction.Y;
		++direction.X;
		break;
	case BOTTOM:
		++direction.X;
		break;
	case BOTTOM_LEFT:
		--direction.Y;
		++direction.X;
		break;
	case LEFT:
		--direction.Y;
		break;
	case TOP_LEFT:
		--direction.Y;
		--direction.X;
		break;
	default:
		// If for some reason we don't have a looking direction
		return;
	}

	ExplosiverVenom* p = new ExplosiverVenom({ _pos.X, _pos.Y }, direction);

	//Spawn projectile
	GameInstance::Instance().getGameObject().push_back(p);
}
