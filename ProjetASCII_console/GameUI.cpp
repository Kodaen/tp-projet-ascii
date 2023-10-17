#include <windows.h>
#include "vector"
#include <set>
#include <string>
#include <sstream>
#include <map>

#include "NYTimer.h"

#include <string>
#include <set>
#include "PlayerController.h"
#include "UIWindow.h"
#include "GameUI.h"
#include "Level.h"
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "gameInstance.h"
#include "BufferHandler.h"
#include "UIWindow.h"

GameUI* GameUI::_gameUIInstance = 0;

GameUI::GameUI() : _showGameOverScreen(false), _currentUIWindow(TITLE_SCREEN)
{
	_choiceIndicator = L">                     ";
	createStats();
	createMenuGameScreen();
	appendToActionsLog(L"Vous devriez essayer de trouver la sortie");
}

GameUI::~GameUI()
{
}

// Returns singleton instance
GameUI& GameUI::Instance()
{
	if (!_gameUIInstance)
	{
		_gameUIInstance = new GameUI();
	}
	return *_gameUIInstance;
}

void GameUI::displayUI() {
	displayStats();
	displayActionsLog();

	if (_showGameOverScreen)
	{
		updateSelectedChoice();
		displayUIWindow();
		confirmButtonChoice();
	}

}

// Puts stats line into the buffer (but doesn't display on screen : see printBuffer())
void GameUI::displayStats()
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	// Hard coded value because HEIGHT can't be used now that it's greater than the console's height.
	// TODO: find how to retrieve it instead.
	bufferHandler.drawMapRow(_stats, 29);
}

// Puts action log line into the buffer (but doesn't display on screen : see printBuffer())
void GameUI::displayActionsLog()
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	bufferHandler.drawMapRow(_actionsLog.back(), 0);
}

// Puts UIWindow into the buffer (but doesn't display on screen : see printBuffer())
void GameUI::displayUIWindow() {
	BufferHandler& bufferHandler = BufferHandler::Instance();

	for (size_t i = 0; i < _menuScreen.size(); i++)
	{
		bufferHandler.drawMapRow(_menuScreen[i], 7 + i);
	}
}

// Updates selected button by the player according to if he pressed Z or S
// Returns true if the player tried to select a choice (i.e : if pressed Z or S)
bool GameUI::updateSelectedChoice()
{
	_playercontroller.registerPressedKeys();
	std::set<char> inputKeys = _playercontroller.getPressedKeys();
	if (inputKeys.size() > 0)
	{
		std::set<char>::iterator it = inputKeys.begin();

		switch (*it)
		{
		case 'z':
			_selectedChoice = 0;
			_choiceIndicator = L"> ";
			break;

		case 's':
			_selectedChoice = 1;
			_choiceIndicator = L" >";
			break;

		default:
			return false;
			break;
		}

		createMenuGameScreen();
		return true;
	}
	return false;
}

// Create the stats line and put player's attribute values in it
void GameUI::createStats()
{
	_stats = L"";
	GameInstance& gameInstance = GameInstance::Instance();
	std::wstringstream wstats;
	wstats << "Étage : ";
	wstats << gameInstance.getCurrentLevel().getNumber();

	wstats << "            -- Joueur --";
	wstats << " Pv : ";
	wstats << gameInstance.getPlayerCharacter().getHP();
	wstats << " Dégâts : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	wstats << " Niveau : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	_stats.append(wstats.str());
	_stats += std::wstring(WIDTH - _stats.size(), L' ');
}

// Put a text in the action log
void GameUI::appendToActionsLog(std::wstring action)
{
	action += std::wstring(WIDTH - action.size(), L' ');
	_actionsLog.push_back(action);
}

// Create the menu window for either start of the game, lose screen or victory screen
// according to the current UI Window
void GameUI::createMenuGameScreen()
{
	_menuScreen.clear();

	// Tools initialisation
	std::wstring emptyLine(WIDTH, L' ');
	std::wstring buttonPaddingLeft(52, L' ');

	// Text initialisation
	std::vector<std::wstring> endGameScreenTitleText;
	std::wstring messageText;
	std::wstring restartButtonText;
	std::wstring quitButtonText;

	switch (_currentUIWindow)
	{
	case TITLE_SCREEN:
		endGameScreenTitleText.push_back(L"███ ███ ███ ███ ███     ███ █   █ ███ ███ ███ █   █");
		endGameScreenTitleText.push_back(L"█ █ █   █    █   █      █   ██  █ █    █  █ █ ██  █");
		endGameScreenTitleText.push_back(L"███ ███ █    █   █  ███ ██  █ █ █ ███  █  █ █ █ █ █");
		endGameScreenTitleText.push_back(L"█ █   █ █    █   █      █   █  ██   █  █  █ █ █  ██");
		endGameScreenTitleText.push_back(L"█ █ ███ ███ ███ ███     ███ █   █ ███ ███ ███ █   █");

		// Placeholder
		messageText = L"Move : ZQSD - Attack : E - Confirm : [Enter]";
		restartButtonText = L" Jouer";
		quitButtonText = L" Quitter";
		break;
	case GAMEOVER:
		endGameScreenTitleText.push_back(L"███ ███ ██ ██ ███   ███ █   █ ███ ███");
		endGameScreenTitleText.push_back(L"█   █ █ █ █ █ █     █ █ █   █ █   █ █");
		endGameScreenTitleText.push_back(L"█ █ ███ █   █ ██    █ █ █   █ ██  ██ ");
		endGameScreenTitleText.push_back(L"█ █ █ █ █   █ █     █ █  █ █  █   █ █");
		endGameScreenTitleText.push_back(L"███ █ █ █   █ ███   ███   █   ███ █ █");

		messageText = L"N'abandonnez pas...";
		restartButtonText = L" Recommencer";
		quitButtonText = L" Quitter";
		break;
	case VICTORY:
		endGameScreenTitleText.push_back(L"█   █ ███ █ █   █ █ █ ███ █   █ █");
		endGameScreenTitleText.push_back(L" █ █  █ █ █ █   █ █ █ █ █ ██  █ █");
		endGameScreenTitleText.push_back(L"  █   █ █ █ █   █ █ █ █ █ █ █ █ █");
		endGameScreenTitleText.push_back(L"  █   █ █ █ █   █ █ █ █ █ █  ██  ");
		endGameScreenTitleText.push_back(L"  █   ███ ███   ██ ██ ███ █   █ █");

		// Placeholder
		messageText = L"Bravo vous avez gagné la partie !";
		restartButtonText = L" Recommencer";
		quitButtonText = L" Quitter";
		break;
	default:
		return;
		break;
	}

	// Put choice indicator arrow
	if (_choiceIndicator.size() >= 2)
	{
		restartButtonText.insert(0, _choiceIndicator, 0, 1);
		quitButtonText.insert(0, _choiceIndicator, 1, 1);
	}

	// Assemble strings to create UI
	std::wstring restartButton;
	std::wstring quitButton;
	std::wstring message;
	std::vector<std::wstring> endGameScreenTitle;

	// Center screen title
	std::wstring tempPaddingTitle(((WIDTH - 81) / 2) - (endGameScreenTitleText[0].size() / 2), L' ');
	std::wstring tempEndGameScreenTitle;
	for (size_t i = 0; i < endGameScreenTitleText.size(); i++)
	{
		tempEndGameScreenTitle = tempPaddingTitle;
		tempEndGameScreenTitle += endGameScreenTitleText[i];
		tempEndGameScreenTitle += tempPaddingTitle;
		tempEndGameScreenTitle += std::wstring(WIDTH - tempEndGameScreenTitle.size(), L' ');

		endGameScreenTitle.push_back(tempEndGameScreenTitle);
	}

	// Center message
	std::wstring tempPaddingMessage(((WIDTH - 81) / 2) - (messageText.size() / 2), L' ');
	message = tempPaddingMessage;
	message += messageText;
	message += tempPaddingMessage;
	message += std::wstring(WIDTH - tempPaddingMessage.size(), L' ');

	// Put padding left and right
	restartButton = buttonPaddingLeft;
	restartButton += restartButtonText;
	restartButton += std::wstring(WIDTH - restartButton.size(), L' ');

	// Put padding left and right
	quitButton = buttonPaddingLeft;
	quitButton += quitButtonText;
	quitButton += std::wstring(WIDTH - quitButton.size(), L' ');

	// Margin top
	for (size_t i = 0; i < 3; i++)
	{
		_menuScreen.push_back(emptyLine);
	}

	for (size_t i = 0; i < endGameScreenTitle.size(); i++)
	{
		_menuScreen.push_back(endGameScreenTitle[i]);
	}

	// Margin between menu title and menu text
	for (size_t i = 0; i < 2; i++)
	{
		_menuScreen.push_back(emptyLine);
	}

	_menuScreen.push_back(message);

	// Margin between menu text and buttons
	for (size_t i = 0; i < 2; i++)
	{
		_menuScreen.push_back(emptyLine);
	}

	_menuScreen.push_back(restartButton);
	_menuScreen.push_back(quitButton);

	// Margin bottom
	for (size_t i = 0; i < 2; i++)
	{
		_menuScreen.push_back(emptyLine);
	}
}

// Disables the menu window
void GameUI::deactivateUIWindow()
{
	_showGameOverScreen = false;
}

// Activates given UI Window (menu window)
void GameUI::activateUIWindow(const UIWINDOW& newUIWindow)
{
	_currentUIWindow = newUIWindow;
	_showGameOverScreen = true;
	createMenuGameScreen();
}

// Executes the code associated with the selected button on the menu window
void GameUI::confirmButtonChoice() {
	std::set<char> inputKeys = _playercontroller.getPressedKeys();
	if (inputKeys.size() > 0) {
		std::set<char>::iterator it = inputKeys.begin();
		if (*it == '*') {
			if (_selectedChoice == 0)
			{
				GameInstance::Instance().restartGame();
			}
			else {
				GameInstance::Instance().finishGame();
			}
		}
	}
}