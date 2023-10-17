#pragma once

//#include <set>
//#include <string>
//#include "NYTimer.h"

class PlayerController
{
	//////////////////////// Constructors ////////////////////////
public:

	PlayerController();

	//////////////////////// Attributes ////////////////////////
private:
	bool _isCtrlHeld;
	bool _isShiftHeld;
	std::set<char> _pressedKeys;
	std::set<char> _oldPressedKeys;
	std::set<char> _bufferPressedKeys;
	
	NYTimer _timerBetweenKeys;
	NYTimer _timerBetweenRepetitiveKeys;
	NYTimer _timerKeyBuffer;

	int _minDelayBetweenRepetitiveKeys = 200;
	int _minDelayBetweenKeys = 100;
	int _bufferDuration = 25;

	//////////////////////// Methods ////////////////////////
public:
	void registerPressedKeys();


	//////////////////////// Getters & Setters //////////////////////// 
public:

	std::set<char> getPressedKeys()
	{
		return _pressedKeys;
	}

	bool getIsCtrlHeld()
	{
		return _isCtrlHeld;
	}

	bool getIsShiftHeld()
	{
		return _isShiftHeld;
	}

};

