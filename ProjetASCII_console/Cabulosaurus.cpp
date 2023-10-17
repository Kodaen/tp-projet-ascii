#include <windows.h>

#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"

#include "Cabulosaurus.h"

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

Cabulosaurus::Cabulosaurus() : _currentStep(0), Entity()
{
	_lookingDirection = TOP;
	_displayedSprite = 0x42; // Letter B, matches caBulosaurus
	_originalSpriteColor = 0x0C; // Pink


	_displayedColor = _lookingDirection + _originalSpriteColor;
}

Cabulosaurus::Cabulosaurus(const COORD& pos, const DIRECTION& lookingDirection) : Cabulosaurus()
{
	_pos = pos;
	_lookingDirection = lookingDirection;

	_displayedColor = _lookingDirection + _originalSpriteColor;
}

// Update player's behavoir; called every frame.
// Every 6 update call, the Cabulausorus shoot bubles (see shootBubles()).
void Cabulosaurus::update()
{
	switch (_currentStep)
	{
	case 0:
		shootBubles();
		break;

	default:
		break;
	}

	// repeat pattern every 6 "playerActed" frames
	_currentStep = (1 + _currentStep) % 6;
}

// Shoot 3 basic projectiles in front of the Cabulosaurus
void Cabulosaurus::shootBubles()
{

	// Calculate the moving direction of the projectile using the looking
	// direction on the Cabulosaurus
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
	// Make a perpendicular vector to the one where the Cabulausorus is looking
	// This way we can spawn 3 projectiles next to each others in his looking
	// direction
	COORD perpendicularDirection = { 0,0 };
	perpendicularDirection.X = -direction.Y;
	perpendicularDirection.Y = direction.X;

	Projectile* p1 = new Projectile({ (_pos.X + perpendicularDirection.X), (_pos.Y + perpendicularDirection.Y) }, direction);
	Projectile* p2 = new Projectile({ _pos.X, _pos.Y }, direction);
	Projectile* p3 = new Projectile({ (_pos.X - perpendicularDirection.X), (_pos.Y - perpendicularDirection.Y) }, direction);

	//Spawn projectile
	GameInstance::Instance().getGameObject().push_back(p1);
	GameInstance::Instance().getGameObject().push_back(p2);
	GameInstance::Instance().getGameObject().push_back(p3);
}