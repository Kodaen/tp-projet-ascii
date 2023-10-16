#pragma once

//#include <string>
//#include "NYTimer.h"
//#include <set>
//#include "PlayerController.h"
//#include "UIWindow.h"

class GameUI
{
	// Constructor
public:
	GameUI();
	~GameUI();


	static GameUI& Instance();

	void displayUI();

	void displayStats();
	
	void displayUIWindow();

	bool updateSelectedChoice();
	void confirmButtonChoice();

	void deactivateUIWindow();
	void activateUIWindow(UIWINDOW test);

	void createStats();

private:
	short _selectedChoice;
	std::wstring _choiceIndicator;

	PlayerController _playercontroller;

	std::wstring _stats;
	std::vector<std::wstring> _menuScreen;

	UIWINDOW _currentUIWindow;

	bool _showGameOverScreen = false;

	static GameUI* _gameUIInstance;

private:
	void createMenuGameScreen();

};

