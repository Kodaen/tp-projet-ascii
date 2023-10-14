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


void BufferHandler::initialize() {
	const short SCREEN_WIDTH = WIDTH;
	const short SCREEN_HEIGHT = HEIGHT;

	_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	_dwBufferCoord = { 0, 0 };
	_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };


	ReadConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize, _dwBufferCoord, &_rcRegion);

}

void BufferHandler::printBuffer() {
	WriteConsoleOutputW(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize,
		_dwBufferCoord, &_rcRegion);
}

void BufferHandler::emptyBuffer() {
	fillBuffer(' ');
}

void BufferHandler::fillBuffer(WCHAR character, WORD color) {
	for (short x = 0; x < WIDTH; x++)
	{
		for (short y = 0; y < HEIGHT; y++)
		{
			drawAtCoordinate(character, color, { x,y });
		}
	}
}

void BufferHandler::drawAtCoordinate(WCHAR character, WORD color, COORD coordinate)
{
	_buffer[coordinate.X][coordinate.Y].Char.UnicodeChar = character;
	_buffer[coordinate.X][coordinate.Y].Attributes = color;
}

void BufferHandler::DrawMap(std::vector<std::wstring> map, std::map<std::wstring, WORD> colors)
{
	// Right part of the background.
	if (!areDefaultColorsNeeded(colors)) {
		fillBuffer(L' ', colors[L"background"]);
	}

	for (short i = 0; i < map.size(); i++)
	{
		DrawMapRow(map[i], i, colors);
	}
}

void BufferHandler::DrawMapRow(std::wstring row, short x, std::map<std::wstring, WORD> colors)
{
	if (areDefaultColorsNeeded(colors)) {
		// Apply default black and white theme.
		colors = { {L"walls", 0x00F}, { L"ground", 0x00F }, { L"background", 0x000 } };
	}

	for (short y = 0; y < row.size(); y++)
	{
		if (isWall(row[y])) {
			drawAtCoordinate(row[y], colors[L"walls"], { x, y });
		}
		else if (isGround(row[y])) {
			drawAtCoordinate(row[y], colors[L"ground"], { x, y });
		}
		else if (isBackground(row[y])) {
			// Left part of the background or in between ground or walls.
			drawAtCoordinate(row[y], colors[L"background"], { x, y });
		}
		else {
			// Draw UI, always white on black for now.
			drawAtCoordinate(row[y], 0x00F, { x, y });
		}
	}
}

bool BufferHandler::areDefaultColorsNeeded(std::map<std::wstring, WORD> colors) {
	return (colors.size() == 0 || (colors.count(L"walls") == 0 || colors.count(L"ground") == 0 || colors.count(L"background") == 0));
}

bool BufferHandler::isGroundTile(COORD coordinates) {
	// Is there ground on this tile?
	bool isGroundTile = false;

	isGroundTile = isGround(getCharacterAtCoordinate(coordinates));

	return  isGroundTile;
}

bool BufferHandler::isGround(WCHAR wchar) {
	return wchar == L'.' || wchar == L',' || wchar == L'#';
}

bool BufferHandler::isWall(WCHAR wchar) {
	return wchar == L'█';
}

bool BufferHandler::isBackground(WCHAR wchar) {
	return wchar == L'§';
}

void BufferHandler::changeColorAtCoordinate(WORD color, COORD coordinates)
{
}

WCHAR& BufferHandler::getCharacterAtCoordinate(COORD coordinates)
{
	return _buffer[coordinates.X][coordinates.Y].Char.UnicodeChar;
}

WORD& BufferHandler::getColorAtCoordinate(COORD coordinates)
{
	return _buffer[coordinates.X][coordinates.Y].Attributes;
}
