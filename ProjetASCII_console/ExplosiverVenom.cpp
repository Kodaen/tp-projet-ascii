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
#include <map>
#include "Level.h"
#include "gameInstance.h"

#include "Projectile.h"
#include "ExplosiverVenom.h"

#include "VenomSplash.h"


ExplosiverVenom::ExplosiverVenom() : _timeToLive(12), Projectile()
{
	_pos = { 7,10 };
	_displayedSprite = 0xA4;
	_originalSpriteColor = 0x0C;
	_displayedColor = 0x0C;
	_damage = 50;

	std::map<std::wstring, WORD> colors = GameInstance::Instance().getCurrentLevel().getColors();
	_displayedColor = _displayedColor | colors[L"groundBg"];
	_originalSpriteColor = _originalSpriteColor | colors[L"groundBg"];
}

ExplosiverVenom::ExplosiverVenom(const COORD& pos, const COORD& movingDirection) : ExplosiverVenom()
{
	_movingDirection = movingDirection;
	_pos = pos;
}

// Moves the projectile according to its movingDirection ; called every frame.
// This projectile only live for a certain number of frame, then die and explode into
// multiple subProjectiles (see explode()).
void ExplosiverVenom::update() {
	--_timeToLive;

	if (_timeToLive <= 0)
	{
		die();
	}
	else
	{
		moveToDirection();
	}
}

// Spawns 4 subprojectile (see class VenomSplash) in a cross pattern
void ExplosiverVenom::explode() {
	//If projectile moves diagonally, then explode in + patern
	if (_movingDirection.X != 0 && _movingDirection.Y != 0) {
		VenomSplash* p1 = new VenomSplash({ _pos.X, _pos.Y }, {1,0});
		VenomSplash* p2 = new VenomSplash({ _pos.X, _pos.Y }, {-1,0});
		VenomSplash* p3 = new VenomSplash({ _pos.X, _pos.Y }, {0,1});
		VenomSplash* p4 = new VenomSplash({ _pos.X, _pos.Y }, {1,-1});

		GameInstance::Instance().getGameObject().push_back(p1);
		GameInstance::Instance().getGameObject().push_back(p2);
		GameInstance::Instance().getGameObject().push_back(p3);
		GameInstance::Instance().getGameObject().push_back(p4);
	}
	//else then explode in x patern
	else {
		VenomSplash* p1 = new VenomSplash({ _pos.X, _pos.Y }, { 1,1 });
		VenomSplash* p2 = new VenomSplash({ _pos.X, _pos.Y }, { -1,-1 });
		VenomSplash* p3 = new VenomSplash({ _pos.X, _pos.Y }, { -1,1 });
		VenomSplash* p4 = new VenomSplash({ _pos.X, _pos.Y }, { 1,-1 });

		GameInstance::Instance().getGameObject().push_back(p1);
		GameInstance::Instance().getGameObject().push_back(p2);
		GameInstance::Instance().getGameObject().push_back(p3);
		GameInstance::Instance().getGameObject().push_back(p4);
	}
}

// Makes the ExplosiverVenom explode then die on the same frame
void ExplosiverVenom::die()
{
	explode();
	GameObject::die();
}
