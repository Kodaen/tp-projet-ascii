#include <windows.h>

#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"

#include "Croquecaille.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include <vector>
#include <string>
#include <map>
#include "Level.h"
#include "gameInstance.h"

#include "Projectile.h"

Croquecaille::Croquecaille() : _currentStep(0), Entity()
{
	_lookingDirection = TOP;
	_displayedSprite = 0x43; // Letter C, matches Croquecaille
	_originalSpriteColor = 0x0C; // Pink

	_displayedColor = _lookingDirection + _originalSpriteColor;
}

Croquecaille::Croquecaille(const COORD& pos, const DIRECTION& lookingDirection) : Croquecaille()
{
	_pos = pos;
	_lookingDirection = lookingDirection;

	_displayedColor = _lookingDirection + _originalSpriteColor;
}

// Update player's behavoir; called every frame.
// Every 3 update call, the Croquecaille shoots a buble (see shootBuble()).
void Croquecaille::update()
{
	switch (_currentStep)
	{
	case 0:
		shootBuble();
		break;

	default:
		break;
	}

	// repeat pattern every 3 "playerActed" frames
	_currentStep = (1 + _currentStep) % 3;
}

// Shoot a basic projectile in front of the Croquecaille
void Croquecaille::shootBuble()
{

	// Calculate the moving direction of the projectile using the looking
	// direction on the croquecaille
	COORD direction = { 0,0 };
	switch (_lookingDirection)
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

	Projectile* p = new Projectile({ _pos.X, _pos.Y }, direction, 50);

	//Spawn projectile
	GameInstance::Instance().getGameObject().push_back(p);
}