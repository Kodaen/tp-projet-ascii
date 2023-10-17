#pragma once

//#include <wincontypes.h>

class GameObject
{
	//////////////////////// Constructors ////////////////////////
public:
	GameObject();

	//////////////////////// Attributes ////////////////////////
protected:
	bool _pendingDestruction;
	COORD _pos;

	WORD _originalSpriteColor = 0x07;
	WORD _displayedColor;
	WCHAR _displayedSprite;

	//////////////////////// Methods ////////////////////////
public:
	virtual void update() = 0;
	virtual void draw();
	virtual void die();
	virtual void recieveDamage(const int& damage, WCHAR opponent = L' ');

	virtual void refreshDisplayedColor();

	//////////////////////// Getters & Setters ////////////////////////
public:
	COORD getPos() {
		return _pos;
	}

	void setPos(const COORD& newPos) {
		_pos = newPos;
	}

	WCHAR getSprite() {
		return _displayedSprite;
	}

	void setSprite(const int& newSprite) {
		_displayedSprite = newSprite;
	}

	WORD getOriginalSpriteColor() {
		return _originalSpriteColor;
	}

	void setOriginalSpriteColor(const WORD& newSpriteColor) {
		_originalSpriteColor = newSpriteColor;
	}

	WORD getDisplayedSpriteColor() {
		return _displayedColor;
	}

	void setDisplayedSpriteColor(const WORD& newDisplayedColor) {
		_displayedColor = newDisplayedColor;
	}

	bool isPendingDestruction() {
		return _pendingDestruction;
	}

	void setPendingDestruction(const bool& boolean) {
		_pendingDestruction = boolean;
	}

};