#pragma once

//#include <windows.h>
//#include <vector>
//#include <string>

// HEIGHT must be greater or equal to WIDTH.
#define HEIGHT 220 //MAX VALUE = (to be tested)
#define WIDTH 200  //MAX VALUE = (to be tested)


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