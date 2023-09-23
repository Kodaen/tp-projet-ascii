#pragma once

//#include <windows.h>
//#include <vector>
//#include <string>

#define HEIGHT 20 //MAX VALUE = 32,767
#define WIDTH 20  //MAX VALUE = 32,767


class BufferHandler
{
	// Constructor
private:
	BufferHandler();
	void initialize();

	// Attributes
private:

	HANDLE _hOutput;
	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

	CHAR_INFO _buffer[HEIGHT][WIDTH];

	static BufferHandler* _bufferHandlerInstance;

	// Methods
public:
	~BufferHandler();

	static BufferHandler& Instance();

	void fillBuffer(WCHAR character);

	void emptyBuffer();

	void printBuffer();

	void drawAtCoordinate(WCHAR character, WORD color, COORD coordinates);

	void changeColorAtCoordinate(WORD color, COORD coordinates);

	void DrawMap(std::vector<std::string> map);

	void DrawMapRow(std::string row, short x);

	WCHAR& getCharacterAtCoordinate(COORD coordinates);

	WORD& getColorAtCoordinate(COORD coordinates);
};