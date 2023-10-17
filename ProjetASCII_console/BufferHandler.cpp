#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "BufferHandler.h"


BufferHandler* BufferHandler::_bufferHandlerInstance = 0;

BufferHandler::BufferHandler() {
	initialize();
}

BufferHandler::~BufferHandler() {

}


BufferHandler& BufferHandler::Instance()
{
	if (!_bufferHandlerInstance)
	{
		_bufferHandlerInstance = new BufferHandler();
	}
	return *_bufferHandlerInstance;
}

// Buffer initialization
void BufferHandler::initialize() {
	const short SCREEN_WIDTH = WIDTH;
	const short SCREEN_HEIGHT = HEIGHT;

	_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	_dwBufferCoord = { 0, 0 };
	_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };


	ReadConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize, _dwBufferCoord, &_rcRegion);

}

// Prints what's inside the buffer to the screen
 void BufferHandler::printBuffer() {
	WriteConsoleOutputW(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize,
		_dwBufferCoord, &_rcRegion);
}

// Empty the buffer by filling it with ' ' 
void BufferHandler::emptyBuffer() {
	fillBuffer(' ');
}

// Fills the buffer of parameter character and parameter color
void BufferHandler::fillBuffer(const WCHAR& character, const WORD& color) {
	for (short x = 0; x < WIDTH; x++)
	{
		for (short y = 0; y < HEIGHT; y++)
		{
			drawAtCoordinate(character, color, { x,y });
		}
	}
}

// Put a specific character into the buffer (but doesn't display on screen : see printBuffer())
 void BufferHandler::drawAtCoordinate(const WCHAR& character, const WORD& color, const COORD& coordinate)
{
	_buffer[coordinate.X][coordinate.Y].Char.UnicodeChar = character;
	_buffer[coordinate.X][coordinate.Y].Attributes = color;
}

 // Put the map into the buffer (but doesn't display on screen : see printBuffer())
void BufferHandler::drawMap(const std::vector<std::wstring>& map, std::map<std::wstring, WORD> colors)
{
	// Right part of the background.
	if (!areDefaultColorsNeeded(colors)) {
		fillBuffer(L' ', colors[L"background"]);
	}

	for (short i = 0; i < map.size(); i++)
	{
		drawMapRow(map[i], i, colors);
	}
}

// Put a string into the buffer at a specific row (x), takes 
void BufferHandler::drawMapRow(const std::wstring& row, const short& x, std::map<std::wstring, WORD> colors)
{
	if (areDefaultColorsNeeded(colors)) {
		// Apply default black and white theme.
		colors = { {L"walls", 0x0F}, { L"groundBg", 0x00 }, { L"groundFg", 0x0F }, { L"background", 0x00 } };
	}

	for (short y = 0; y < row.size(); y++)
	{
		if (isWall(row[y])) {
			drawAtCoordinate(row[y], colors[L"walls"], { x, y });
		}
		else if (isGround(row[y])) {
			drawAtCoordinate(row[y], colors[L"groundBg"] | colors[L"groundFg"], { x, y });
		}
		else if (isBackground(row[y])) {
			// Left part of the background or in between ground or walls.
			drawAtCoordinate(row[y], colors[L"background"], { x, y });
		}
		else if (isStair(row[y])) {
			drawAtCoordinate(row[y], colors[L"groundBg"] | colors[L"stair"], { x, y });
		}
		else if (isWater(row[y])) {
			// makes checkerboard pattern
			if ((y + x) % 2 == 0)
			{
				drawAtCoordinate(row[y], colors[L"liquidBg"] | colors[L"liquidFg"], { x, y });
			}
			else {
				drawAtCoordinate(L' ', colors[L"liquidBg"] | colors[L"liquidFg"], { x, y });
			}

		}
		else {
			// Draw UI, always white on black for now.
			drawAtCoordinate(row[y], 0x00F, { x, y });
		}
	}
}

// Check if the map<>colors can be used to color the map, if not then returns true 
 bool BufferHandler::areDefaultColorsNeeded(const std::map<std::wstring, WORD>& colors) {
	return (colors.size() == 0 || (colors.count(L"walls") == 0 || colors.count(L"groundBg") == 0 || colors.count(L"groundFg") == 0
		|| colors.count(L"background") == 0));
}

 // Returns if there is a ground a this coordinate in the buffer, meaning the gameObject can go on it
bool BufferHandler::isTileWalkable(const COORD& coordinates) {
	bool isTileWalkable = false;
	isTileWalkable = isGround(getCharacterAtCoordinate(coordinates)) || isStair(getCharacterAtCoordinate(coordinates));
	return  isTileWalkable;
}

// Returns if the character represents ground or not
 bool BufferHandler::isGround(const WCHAR& wchar) {
	return wchar == L'.' || wchar == L','; // ,  is unused for now. TODO: Delete?
}

// Returns if the character represents a wall or not
 bool BufferHandler::isWall(const WCHAR& wchar) {
	return wchar == L'█';
}

 // Returns if the character represents the background or not
 bool BufferHandler::isBackground(const WCHAR& wchar) {
	return wchar == L'§';
}

 // Returns if the character represents stairs or not
 bool BufferHandler::isStair(const WCHAR& wchar) {
	return wchar == L'#';
}

 // Returns if the character represents water or not
 bool BufferHandler::isWater(const WCHAR& wchar)
{
	return wchar == L'~';
}

 // Returns the character at this coordinate in the buffer
 WCHAR& BufferHandler::getCharacterAtCoordinate(const COORD& coordinates)
{
	return _buffer[coordinates.X][coordinates.Y].Char.UnicodeChar;
}

 // Returns the color of character at this coordinate in the buffer
 WORD& BufferHandler::getColorAtCoordinate(const COORD& coordinates)
{
	return _buffer[coordinates.X][coordinates.Y].Attributes;
}
