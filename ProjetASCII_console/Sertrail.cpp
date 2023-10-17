#include <windows.h>

#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"
#include "Sertrail.h"

Sertrail::Sertrail() : _currentStep(0), Entity()
{
	_lookingDirection = TOP;
	_displayedSprite = 0x53; // Letter S, matches Sertrail
	_originalSpriteColor = 0x0C; // Pink
	changedTrajectory = false;


	_displayedColor = _lookingDirection + _originalSpriteColor;
}

Sertrail::Sertrail(COORD pos, DIRECTION lookingDirection) : Sertrail()
{
	_pos = pos;
	_lookingDirection = lookingDirection;

	_displayedColor = _lookingDirection + _originalSpriteColor;
}

void Sertrail::update() {
	// Attack and go forward
	// until it hits a wall or the player.
	// After hitting a wall (changed Trajectory = true)
	// it turns arround
	// by turning 90 degrees to the right twice

	if (changedTrajectory)
	{
		turnToRight();
		changedTrajectory = false;
	}
	// Attacks in front of him
	attack();

	// If it couldn't move forward, starts 
	// its turn arround
	if (!moveForward()) {
		turnToRight();
		attack();
		moveForward();

		changedTrajectory = true;
	}
}

void Sertrail::turnToRight()
{
	switch (_lookingDirection)
	{
	case TOP:
		turnToDirection(RIGHT);
		break;
	case LEFT:
		turnToDirection(TOP);
		break;
	case TOP_LEFT:
		turnToDirection(TOP_RIGHT);
		break;
	case RIGHT:
		turnToDirection(BOTTOM);
		break;
	case TOP_RIGHT:
		turnToDirection(BOTTOM_RIGHT);
		break;
	case BOTTOM:
		turnToDirection(LEFT);
		break;
	case BOTTOM_LEFT:
		turnToDirection(TOP_LEFT);
		break;
	case BOTTOM_RIGHT:
		turnToDirection(BOTTOM_LEFT);
		break;
	default:
		break;
	}
}
