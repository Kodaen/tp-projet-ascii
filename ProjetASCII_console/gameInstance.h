#pragma once

//#include <wincontypes.h>

class GameInstance
{
	// Constructor and Destructor
private:
	GameInstance(PlayerCharacter mainChar);

public :
	~GameInstance();
	
	// Get Instance

	static GameInstance& Instance();

	// Attributes

private:

	Level _currentLevel;

	PlayerCharacter _playerCharacter;
 
public:
	static GameInstance* _gameInstance;


private:


public:
	void update();

	Level& getcurrentLevel() {
		return _currentLevel;
	};

	void setCurrentLevel(Level &newCurrentLevel) {
		_currentLevel = newCurrentLevel;
	};

	PlayerCharacter& getPlayerCharacter() {
		return _playerCharacter;
	};

	void setPlayerCharacter(PlayerCharacter &newPlayerCharacter) {
		_playerCharacter = newPlayerCharacter;
	};
};

