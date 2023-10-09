#pragma once

//#include <wincontypes.h>

class GameObject
{
	//Constructors
public:
	GameObject();

	// Attributes
protected:
	bool _pendingDestruction;
	COORD _pos;

	WORD _originalSpriteColor = 0x07;
	WORD _displayedColor;
	WCHAR _displayedSprite;

	// Functions
public :
	virtual void update() = 0;
	virtual void die();
	virtual void recieveDamage(int damage);

	// Getters & Setters
public :
	COORD getPos() {
		return _pos;
	}

	void setPos(COORD newPos) {
		_pos = newPos;
	}

	WCHAR getSprite() {
		return _displayedSprite;
	}

	void setSprite(int newSprite) {
		_displayedSprite = newSprite;
	}

	WORD getOriginalSpriteColor() {
		return _originalSpriteColor;
	}

	void setOriginalSpriteColor(WORD newSpriteColor) {
		_originalSpriteColor = newSpriteColor;
	}

	WORD getDisplayedSpriteColor() {
		return _displayedColor;
	}

	void setDisplayedSpriteColor(WORD newDisplayedColor) {
		_displayedColor = newDisplayedColor;
	}

	bool isPendingDestruction() {
		return _pendingDestruction;
	}

};