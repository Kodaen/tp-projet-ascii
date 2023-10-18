#include <windows.h>
#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include <string>
#include <vector>
#include "Entity.h"

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "vector"
#include <string>
#include <map>
#include "Level.h"
#include "gameInstance.h"

#include "Projectile.h"
#include "VenomSplash.h"

VenomSplash::VenomSplash() : _timeToLive(3), Projectile()
{
	_pos = { 7,10 };
	_displayedSprite = 0xD7;
	_originalSpriteColor = 0x0C;
	_displayedColor = 0x0C;
	_damage = 25;

	std::map<std::wstring, WORD> colors = GameInstance::Instance().getCurrentLevel().getColors();
	_displayedColor = _displayedColor | colors[L"groundBg"];
	_originalSpriteColor = _originalSpriteColor | colors[L"groundBg"];
}

VenomSplash::VenomSplash(const COORD& pos, const COORD& movingDirection) : VenomSplash()
{
	_movingDirection = movingDirection;
	_pos = pos;
}

// Moves the projectile according to its movingDirection ; called every frame.
// This projectile only live for a certain number of frame, then die
void VenomSplash::update() {
	--_timeToLive;

	if (_timeToLive <= 0)
	{
		die();
	}
	else {
		moveToDirection();
	}

}