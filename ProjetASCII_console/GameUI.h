#pragma once

//#include <string>
//#include "NYTimer.h"
//#include <set>
//#include "PlayerController.h"
//#include "UIWindow.h"

class GameUI
{
	//////////////////////// Constructors ////////////////////////
public:
	GameUI();
	~GameUI();


	static GameUI& Instance();

	//////////////////////// Methods ////////////////////////

	void displayUI();

	void displayStats();

	void displayActionsLog();
	
	void displayUIWindow();

	bool updateSelectedChoice();
	void confirmButtonChoice();

	void deactivateUIWindow();
	void activateUIWindow(const UIWINDOW& test);

	void createStats();

	void appendToActionsLog(std::wstring action);

	//////////////////////// Attributes ////////////////////////
private:
	short _selectedChoice;
	std::wstring _choiceIndicator;

	PlayerController _playercontroller;

	std::wstring _stats;

	std::vector<std::wstring> _actionsLog;

	std::vector<std::wstring> _menuScreen;

	UIWINDOW _currentUIWindow;

	bool _showGameOverScreen = false;

	static GameUI* _gameUIInstance;

private:
	void createMenuGameScreen();

};

