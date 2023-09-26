#pragma once

//#include <set>
//#include <string>
//#include "NYTimer.h"

class PlayerController
{
	// Constructor
public:

	PlayerController();

	// Attributes
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

	// Functions
public:
	void registerPressedKeys();


	// Getters and Setters
public:

	std::set<char> getPressedKeys();

	bool getIsCtrlHeld();

	bool getIsShiftHeld();
};

