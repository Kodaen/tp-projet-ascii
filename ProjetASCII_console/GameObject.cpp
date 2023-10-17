#include <windows.h>

#include <wincontypes.h>
#include "GameObject.h"

GameObject::GameObject() : _pendingDestruction(false),
_originalSpriteColor(0x07),
_displayedColor(0x0F),
_pos({ 0,0 }),
_displayedSprite(0x50)
{

}

void GameObject::die() {
	_pendingDestruction = true;
}

void GameObject::recieveDamage(int damage) {
	return;
};

void GameObject::refreshDisplayedColor() {
	_displayedColor = _originalSpriteColor;
}