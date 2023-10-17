#define _WIN32_WINNT 0x0501
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>
#include <map>

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"

#include "Direction.h"
#include "GameObject.h"
#include "Entity.h"
#include "PlayerCharacter.h"

#include "BufferHandler.h"

#include "Level.h"

#include "NYTimer.h"
#include <iostream>
#include "UIWindow.h"
#include "GameUI.h"
#include "gameInstance.h"

#include "Projectile.h"

#pragma comment(lib,"winmm.lib")


LONG_PTR setConsoleWindowStyle(INT, LONG_PTR);

int main()
{
	// Setup window
	LONG_PTR new_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	setConsoleWindowStyle(GWL_STYLE, new_style);

	// Initialisation
	BufferHandler* bufferHandler = &BufferHandler::Instance();
	GameInstance* gameInstance = &GameInstance::Instance();
	GameUI* gameUI = &GameUI::Instance();
	NYTimer nyTimer;

	// Prepare resources for the map.
	std::vector<std::wstring>& map = gameInstance->getCurrentLevel().getLevel();
	std::map<std::wstring, WORD>& colors = gameInstance->getCurrentLevel().getColors();

	gameInstance->setPlayerColors();

	//Create title screen and pause game
	gameUI->activateUIWindow(TITLE_SCREEN);
	gameInstance->pauseGame(true);

	// Game loop
	while (!gameInstance->isGameFinished()) {
		// Start timer to calculate the frame's duration
		nyTimer.start();

		// Has to come before drawing the map.
		if (gameInstance->getPlayerCharacter().isOnStairs()) {

			gameInstance->getPlayerCharacter().setIsOnStairs(false);
			gameInstance->resetLevel();
		}

		// Put the map into the buffer
		bufferHandler->drawMap(map, colors);

		gameInstance->update();

		// To keep stats updated in real time like HP and floor.
		gameUI->createStats();
		gameUI->displayUI();

		bufferHandler->printBuffer();

		// Use timer to cap to 60 fps
		Sleep(max((16 - (long)nyTimer.getElapsedMs()), 0));
	}

	delete bufferHandler;
	delete gameInstance;
	delete gameUI;

	// End of the game
	return EXIT_SUCCESS;
}

//Si le new style est à 0, la fenetre n'a absolument rien à part son contenu
LONG_PTR setConsoleWindowStyle(INT n_index, LONG_PTR new_style)
{
	/*The function does not clear the last error information. if last value was zero.*/
	SetLastError(NO_ERROR);

	HWND hwnd_console = GetConsoleWindow();

	LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

	//show window after updating
	ShowWindow(hwnd_console, SW_SHOW);

	return style_ptr;
}