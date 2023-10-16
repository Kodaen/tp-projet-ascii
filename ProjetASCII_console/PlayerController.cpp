#include <windows.h>

#include <set>
#include <string>
#include "NYTimer.h"
#include "PlayerController.h"


PlayerController::PlayerController() :
	_isCtrlHeld(false),
	_pressedKeys(),
	_oldPressedKeys(),
	_bufferPressedKeys(),
	_timerBetweenKeys(),
	_timerBetweenRepetitiveKeys(),
	_timerKeyBuffer(),
	_minDelayBetweenKeys(50),
	_minDelayBetweenRepetitiveKeys(400),
	_bufferDuration(25)
{
	_timerBetweenKeys.start();
	_timerBetweenRepetitiveKeys.start();
	_timerKeyBuffer.start();
}

void PlayerController::registerPressedKeys()
{
	// TODO : make a buffer to allow player to easily input 2 keys at once
	_pressedKeys.clear();

	// Check if the delay between each key registering is passed or not
	// If you could register new keys every frames, it would be harder
	// for players to do basics things like moving since you would go
	// very fast
	if (_timerBetweenKeys.getElapsedMs() < _minDelayBetweenKeys)
		return;

	// Check if Ctrl is Held or not
	GetAsyncKeyState(17) ? _isCtrlHeld = true : _isCtrlHeld = false;
	GetAsyncKeyState(VK_LSHIFT) ? _isShiftHeld = true : _isShiftHeld = false;

	// Put into the set of keys all the pressed keys
	if (GetAsyncKeyState(0x5A)) _pressedKeys.insert('z');
	if (GetAsyncKeyState(0x51)) _pressedKeys.insert('q');
	if (GetAsyncKeyState(0x53)) _pressedKeys.insert('s');
	if (GetAsyncKeyState(0x44)) _pressedKeys.insert('d');
	if (GetAsyncKeyState(0x45)) _pressedKeys.insert('e');
	if (GetAsyncKeyState(VK_RETURN)) _pressedKeys.insert('*'); // Will represent the enter key because we can only use a char.

	// Just Quality of life
	// If the previous registered input are the same as the current one
	// then wait a bit longer before actually registering the keys.
	// This means we can have a shorter time between registering individual key press
	// (stored in _timerBetweenKeys) and making the player able to act quickly if he is
	// fast when typing on his keyboard (i.e : press z, release z, press z).
	// while still avoid weird behavoir where the character does something
	// the player don't want because he didn't release the key fast enough.
	if (_oldPressedKeys == _pressedKeys) {
		if (_timerBetweenRepetitiveKeys.getElapsedMs() < _minDelayBetweenRepetitiveKeys / (1.5 * _isShiftHeld + 1)) {
			_pressedKeys.clear();
			return;
		}		
	}

	// We reset the timers for the next frame if any key were input
	_oldPressedKeys = _pressedKeys;
	if (_pressedKeys.size() != 0) { 
		_timerBetweenKeys.start(); 
		_timerBetweenRepetitiveKeys.start();
	};
}

std::set<char> PlayerController::getPressedKeys()
{
	return _pressedKeys;
}

bool PlayerController::getIsCtrlHeld()
{
	return _isCtrlHeld;
}

bool PlayerController::getIsShiftHeld()
{
	return _isShiftHeld;
}

