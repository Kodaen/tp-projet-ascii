#pragma once

//#include <string>
//#include "NYTimer.h"
//#include <set>
//#include "PlayerController.h"

class GameUI
{
	// Constructor
public:
	GameUI();
	~GameUI();


	static GameUI& Instance();

	void displayUI();

	void displayStats();
	
	void displayGameOverScreen();

	bool updateSelectedChoice();
	void confirmGameOverChoice();

	void activateGameOverScreen(bool boolean);

	void createStats();

private:
	short _selectedChoice;
	std::wstring _choiceIndicator;

	PlayerController _playercontroller;

	std::wstring _stats;
	std::vector<std::wstring> _menuScreen;

	// TODO : Replace with ENUM if we get other UI later
	std::wstring _focusedUI;

	bool _showGameOverScreen = false;

	static GameUI* _gameUIInstance;

private:
	void createMenuGameScreen();

};

