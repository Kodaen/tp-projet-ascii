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
#include "UIWindow.h"
#include "GameUI.h"

Projectile::Projectile() : _movingDirection({ 1,0 }), GameObject() {
	_pos = { 7,10 };
	_displayedSprite = 0x6f;
	_originalSpriteColor = 0x0C;
	_displayedColor = 0x0C;
	_damage = 1;

	std::map<std::wstring, WORD> colors = GameInstance::Instance().getCurrentLevel().getColors();
	_displayedColor = _displayedColor | colors[L"groundBg"];
	_originalSpriteColor = _originalSpriteColor | colors[L"groundBg"];
}


Projectile::Projectile(const COORD& pos, const COORD& movingDirection, int damage) : Projectile() {
	_movingDirection = movingDirection;
	_pos = pos;
	_damage = damage;
}

// Moves the projectile according to its movingDirection ; called every frame
void Projectile::update() {
	moveToDirection();
}

// Moves the projectile according to its movingDirection
void Projectile::moveToDirection()
{
	// NOTE : projectiles can destroy each other, this is a desired behavior
	if (_movingDirection.X > 1 || _movingDirection.Y > 1)
	{
		for (short x = 0; x < _movingDirection.X; x++)
		{
			for (short y = 0; y < _movingDirection.Y; y++)
			{
				if (!GameInstance::Instance().getCurrentLevel().isTileWalkable({ _pos.X + x,  _pos.Y + y })) {
					attackAtPos({ _pos.X + x, _pos.Y + y });
					die();
					return;
				}
			}

		}
	}
	else if (!GameInstance::Instance().getCurrentLevel().isTileWalkable({ _pos.X + _movingDirection.X,  _pos.Y + _movingDirection.Y })) {
		attackAtPos({ _pos.X + _movingDirection.X, _pos.Y + _movingDirection.Y });
		die();
		return;
	}
	_pos.X += _movingDirection.X;
	_pos.Y += _movingDirection.Y;
}

// Attacks the entity (player or ennemy) at given position
void Projectile::attackAtPos(const COORD& pos) {
	PlayerCharacter& playerCharacter = GameInstance::Instance().getPlayerCharacter();
	std::vector<Entity*>& entities = GameInstance::Instance().getEntites();

	if (pos.X == playerCharacter.getPos().X && pos.Y == playerCharacter.getPos().Y) {
		GameUI::Instance().appendToActionsLog(L"Un projectile vous heurte");
		playerCharacter.recieveDamage(_damage);
	}
	else {
		for (short i = 0; i < entities.size(); i++)
		{
			if (entities[i]->getPos().Y == pos.Y && entities[i]->getPos().X == pos.X) {
				entities[i]->recieveDamage(_damage);
				return;
			}
		}
	}
	delete& entities;
}

// Kills the projectile (see GameObject::die())
void Projectile::recieveDamage(const int& damage, WCHAR opponent) {
	if (opponent == L'@') {
		GameUI::Instance().appendToActionsLog(L"Vous détruisez le projectile");
	}
	die();
}