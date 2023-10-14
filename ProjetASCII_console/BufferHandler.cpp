#include <windows.h>
#include <vector>
#include <string>

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

void BufferHandler::fillBuffer(WCHAR character) {
	for (short x = 0; x < WIDTH; x++)
	{
		for (short y = 0; y < HEIGHT; y++)
		{
			drawAtCoordinate(character, FOREGROUND_RED, { x,y });
		}
	}
}

void BufferHandler::drawAtCoordinate(WCHAR character, WORD color, COORD coordinate)
{
	_buffer[coordinate.X][coordinate.Y].Char.UnicodeChar = character;
	_buffer[coordinate.X][coordinate.Y].Attributes = color;
}

void BufferHandler::DrawMap(std::vector<std::wstring> map)
{
	for (short i = 0; i < map.size(); i++)
	{
		DrawMapRow(map[i], i);
	}
}

void BufferHandler::DrawMapRow(std::wstring row, short x)
{
	for (short y = 0; y < row.size(); y++)
	{
		drawAtCoordinate(row[y], FOREGROUND_RED, { x, y });
	}
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
