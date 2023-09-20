#define _WIN32_WINNT 0x0501
#include <stdio.h>
#include <iostream>
#include <windows.h>

#include "PlayerCharacter.h"
#include "BufferHandler.h"
#include "Level.h"

LONG_PTR setConsoleWindowStyle(INT, LONG_PTR);

template <size_t rows, size_t cols>
void FillBuffer(CHAR_INFO(&buffer)[rows][cols], WCHAR character);
template <size_t rows, size_t cols>
void DrawMap(CHAR_INFO(&buffer)[rows][cols], std::vector<std::string> map);
template <size_t rows, size_t cols>
void DrawMapRow(CHAR_INFO(&buffer)[rows][cols], std::string row, int x);


int main()
{
	// Setup window
	LONG_PTR new_style = WS_OVERLAPPEDWINDOW;
	setConsoleWindowStyle(GWL_STYLE, new_style);

	// Set buffer size
	const short SCREEN_WIDTH = 20;
	const short SCREEN_HEIGHT = 100;

	//std::string nextStep;

	// Initiate buffer and its data
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];


	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	// Empty buffer
	FillBuffer(buffer, ' ');

	// Make first frame
	buffer[5][10].Char.UnicodeChar = 'H';
	buffer[5][10].Attributes = FOREGROUND_RED;

	buffer[5][11].Char.UnicodeChar = 'i';
	buffer[5][11].Attributes = FOREGROUND_BLUE;

	buffer[5][12].Char.UnicodeChar = '!';
	buffer[5][12].Attributes = 0x05;

	// Display first frame
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
	//std::cin >> nextStep;

	// Make second frame
	buffer[5][10].Char.AsciiChar = NULL;
	buffer[5][10].Attributes = NULL;

	buffer[6][10].Char.AsciiChar = 'T';
	buffer[6][10].Attributes = 0x0E;

	buffer[5][11].Char.AsciiChar = 'e';
	buffer[5][11].Attributes = FOREGROUND_GREEN;

	buffer[5][12].Char.AsciiChar = '!';
	buffer[5][12].Attributes = 0x05;

	// Display second frame
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);

	//std::cin >> nextStep;

	// Cacher le curseur
	//CONSOLEE_CURSOR_INFO cursorInfo;
	//cursorInfo.bVisible = FALSE;

	PlayerCharacter MainChar;

	Level level = Level("levels/level1.txt");
	std::vector<std::string> map = level.getLevel();

	while (true) {
		FillBuffer(buffer, ' ');

		DrawMap(buffer, map);

		MainChar.update();
		buffer[MainChar.getPos().X][MainChar.getPos().Y].Char.UnicodeChar = MainChar.getSprite();
		buffer[MainChar.getPos().X][MainChar.getPos().Y].Attributes = FOREGROUND_GREEN;

		WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
			dwBufferCoord, &rcRegion);
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

template <size_t rows, size_t cols>
void FillBuffer(CHAR_INFO(&buffer)[rows][cols], WCHAR character) {
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			buffer[x][y].Char.UnicodeChar = character;
			buffer[x][y].Attributes = FOREGROUND_RED;
		}
	}
}

// TODO: Move to bufferHandler class method when created.
template <size_t rows, size_t cols>
void DrawMap(CHAR_INFO(&buffer)[rows][cols], std::vector<std::string> map) {
	for (int i = 0; i < map.size(); i++)
	{
		DrawMapRow(buffer, map[i], i);
	}
}

template <size_t rows, size_t cols>
void DrawMapRow(CHAR_INFO(&buffer)[rows][cols], std::string row, int x) {
	for (int y = 0; y < row.size(); y++)
	{
		buffer[x][y].Char.UnicodeChar = row[y];
		buffer[x][y].Attributes = FOREGROUND_RED;
	}
}