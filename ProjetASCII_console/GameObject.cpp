#include <windows.h>

#include <wincontypes.h>
#include "GameObject.h"

#include <vector>
#include <string>
#include <map>
#include "BufferHandler.h"

GameObject::GameObject() : _pendingDestruction(false),
_originalSpriteColor(0x07),
_displayedColor(0x0F),
_pos({ 0,0 }),
_displayedSprite(0x50)
{

}

// Put the character associated with the Game Object and it's color into the buffer at the location of the
// Game Object (but doesn't print it on the screen, see BufferHandler::printBuffer())
void GameObject::draw() {
	BufferHandler& bufferHandler = BufferHandler::Instance();

	bufferHandler.drawAtCoordinate(getSprite(), getDisplayedSpriteColor(), { getPos().X, getPos().Y });
}

// Set the attribute _pendingDestruction to true. 
// Before the next update the game instance will check if the
// the ennemy is _pendingDestruction, if yes it will destroy it
void GameObject::die() {
	_pendingDestruction = true;
}

// Inherited functions for child classes.
// Generally allow them to die when recieving a certain amount
// of damages
void GameObject::recieveDamage(const int& damage) {
	return;
};

// Refresh the displayed color using the original sprite color
// Best used by child classes to allow displaying their looking direction
void GameObject::refreshDisplayedColor() {
	_displayedColor = _originalSpriteColor;
}