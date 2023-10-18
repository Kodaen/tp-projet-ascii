#pragma once

//#include <wincontypes.h>
//#include "Direction.h"
//#include "GameObject.h"
//#include <string>
//#include <vector>

class Entity : public GameObject
{
public:
	//////////////////////// Constructors ////////////////////////
	Entity();

	Entity(COORD pos, DIRECTION lookingDirection);

	//////////////////////// Attributes ////////////////////////
protected:
	int _hp;
	int _damage;

	// Direction the character is looking (ENUM)
	DIRECTION _lookingDirection;

	//////////////////////// Methods ////////////////////////
public:
	virtual void update();
	void refreshDisplayedColor();

	// Moving functions
	bool moveDiagonaly(const short& valX, const short& valY);
	bool moveRight(const short& val);
	bool moveDown(const short& val);

	bool moveForward();

	// Direction functions
	void turnToDirection(const DIRECTION& newDirection);

	// Attack and recieve damage functions
	virtual void attack();
	virtual void recieveDamage(const int& Damage, WCHAR opponent = L' ');

	virtual void die();

private:
	std::wstring getRandomVerb(const std::vector<std::wstring>& verbs);

	void setRandomSentence(const std::vector<std::wstring>& verbs);

	//////////////////////// Getters & Setters ////////////////////////
public:
	int getHP() {
		return _hp;
	}

	void setHP(const int& newHp) {
		_hp = newHp;
	}

	int getDamage() {
		return _damage;
	}

	void setDamage(const int& newDamage) {
		_damage = newDamage;
	}
};