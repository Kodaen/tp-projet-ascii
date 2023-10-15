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
#include "GameUI.h"
#include "Level.h"
#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "gameInstance.h"
#include "BufferHandler.h"

GameUI* GameUI::_gameUIInstance = 0;

GameUI::GameUI() : _showGameOverScreen(false)
{
	_choiceIndicator = L">                     ";
	createStats();
	createEndGameScreen();
}

GameUI::~GameUI()
{
}

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

	if (_showGameOverScreen)
	{
		updateSelectedChoice();
		displayGameOverScreen();
		confirmGameOverChoice();
	}

}

void GameUI::displayStats()
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	// Hard coded value because HEIGHT can't be used now that it's greater than the console's height.
	// TODO: find how to retrieve it instead.
	bufferHandler.DrawMapRow(_stats, 29);
}

void GameUI::displayGameOverScreen() {
	BufferHandler& bufferHandler = BufferHandler::Instance();

	for (size_t i = 0; i < _gameOverScreen.size(); i++)
	{
		bufferHandler.DrawMapRow(_gameOverScreen[i], 1 + i);
	}
}

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
			break;
		}

		createEndGameScreen();
		return true;
	}
	return false;
}

void GameUI::createStats()
{
	GameInstance& gameInstance = GameInstance::Instance();
	std::wstringstream wstats;
	wstats << "Étage : ";
	wstats << gameInstance.getcurrentLevel().getNumber();

	wstats << "            -- Joueur --";
	wstats << " Pv : ";
	wstats << gameInstance.getPlayerCharacter().getHP();
	wstats << " Dégâts : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	wstats << " Niveau : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	_stats.append(wstats.str());
}

void GameUI::createEndGameScreen()
{
	_gameOverScreen.clear();

	std::wstring EndGameScreenTitle = L"   GAME OVER   ";
	std::wstring restartButton = L" Recommencer  ";
	std::wstring quitButton = L" Quitter      ";

	if (_choiceIndicator.size() >= 2)
	{
		restartButton.insert(0, _choiceIndicator, 0, 1);
		quitButton.insert(0, _choiceIndicator, 1, 1);
	}

	_gameOverScreen.push_back(EndGameScreenTitle);
	_gameOverScreen.push_back(restartButton);
	_gameOverScreen.push_back(quitButton);
}

void GameUI::activateGameOverScreen(bool boolean)
{
	_showGameOverScreen = boolean;
}

void GameUI::confirmGameOverChoice() {
	std::set<char> inputKeys = _playercontroller.getPressedKeys();
	if (inputKeys.size() > 0) {
		std::set<char>::iterator it = inputKeys.begin();
		if (*it == 'e') {
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