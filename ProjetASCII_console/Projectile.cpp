#include <windows.h>
#include <wincontypes.h>
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"


#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "vector"
#include <string>
#include "Level.h"
#include "gameInstance.h"

#include "Projectile.h"

Projectile::Projectile() : _movingDirection({ 1,0 }), GameObject() {
	_pos = { 7,10 };
	_displayedSprite = 0x6f;
	_originalSpriteColor = 0x07;
	_displayedColor = 0x07;
	_damage = 1;
}

void Projectile::update() {
	moveToDirection();
}

void Projectile::moveToDirection()
{
	if (_movingDirection.X > 1 || _movingDirection.Y > 1)
	{
		for (short x = 0; x < _movingDirection.X; x++)
		{
			for (short y = 0; y < _movingDirection.Y; y++)
			{
				if (!GameInstance::Instance().getcurrentLevel().isTileWalkable({ _pos.X + x,  _pos.Y + y })) {
					attackAtPos({ _pos.X + x, _pos.Y + y });
					die();
					return;
				}
			}

		}
	}
	else if (!GameInstance::Instance().getcurrentLevel().isTileWalkable({ _pos.X + _movingDirection.X,  _pos.Y + _movingDirection.Y })) {
		attackAtPos({ _pos.X + _movingDirection.X, _pos.Y + _movingDirection.Y });
		die();
		return;
	}
	_pos.X += _movingDirection.X;
	_pos.Y += _movingDirection.Y;
}

void Projectile::attackAtPos(COORD pos) {
	// TODO : optimisation
	PlayerCharacter& playerCharacter = GameInstance::Instance().getPlayerCharacter();
	std::vector<Entity*>& entities = GameInstance::Instance().getEntites();

	if (pos.X == playerCharacter.getPos().X && pos.Y == playerCharacter.getPos().Y) {
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
		
}

void Projectile::recieveDamage(int damage) {
	die();
}