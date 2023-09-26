#define _WIN32_WINNT 0x0501
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

#include <set>
#include "NYTimer.h"
#include "PlayerController.h"

#include "Direction.h"
#include "Entity.h"
#include "PlayerCharacter.h"

#include "BufferHandler.h"

#include "Level.h"

#include "gameInstance.h"

#include "NYTimer.h"
#include <iostream>



LONG_PTR setConsoleWindowStyle(INT, LONG_PTR);

int main()
{
	// Setup window
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW;
	setConsoleWindowStyle(GWL_STYLE, new_style);
	
	BufferHandler &bufferHandler = BufferHandler::Instance();

	bufferHandler.emptyBuffer();

		// Make first frame
	bufferHandler.emptyBuffer();

	bufferHandler.drawAtCoordinate('H', FOREGROUND_RED, { 5,10 });
	//buffer[5][10].Char.UnicodeChar = 'H';
	//buffer[5][10].Attributes = FOREGROUND_RED;

	bufferHandler.drawAtCoordinate('i', FOREGROUND_RED, { 5,11 });
	//buffer[5][11].Char.UnicodeChar = 'i';
	//buffer[5][11].Attributes = FOREGROUND_BLUE;

	bufferHandler.drawAtCoordinate('!', FOREGROUND_RED, { 5,12 });
	//buffer[5][12].Char.UnicodeChar = '!';
	//buffer[5][12].Attributes = 0x05;

	// Display first frame
	bufferHandler.printBuffer();

	// Initiate GameInstance
	GameInstance &gameInstance = GameInstance::Instance();
	Level level = Level("levels/level1.txt");
	gameInstance.setCurrentLevel(level);

	std::vector<std::string> map = gameInstance.getcurrentLevel().getLevel();

	NYTimer nyTimer;

	
	// Game loop
	while (true) {
		nyTimer.start();
		// Empty the buffer
		bufferHandler.emptyBuffer();
		
		// Put the map into the buffer
		bufferHandler.DrawMap(map);

		gameInstance.update();

		// TODO : Sleep is very innacurate, ask what other people
		// use instead
		Sleep(max((16 - nyTimer.getElapsedMs()), 0));

		// Print the buffer on the screen
		bufferHandler.printBuffer();


	}

	// fin du jeu
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