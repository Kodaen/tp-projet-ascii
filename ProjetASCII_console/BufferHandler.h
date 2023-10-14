#pragma once

//#include <windows.h>
//#include <vector>
//#include <string>
//#include <map>

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

	void fillBuffer(WCHAR character, WORD color = FOREGROUND_RED);

	void emptyBuffer();

	void printBuffer();

	void drawAtCoordinate(WCHAR character, WORD color, COORD coordinates);

	void changeColorAtCoordinate(WORD color, COORD coordinates);

	void DrawMap(std::vector<std::wstring> map, std::map<std::wstring, WORD> colors = {});

	void DrawMapRow(std::wstring row, short x, std::map<std::wstring, WORD> colors = {});

	bool areDefaultColorsNeeded(std::map<std::wstring, WORD> colors);

	bool isGroundTile(COORD coordinates);

	bool isGround(WCHAR wchar);

	bool isWall(WCHAR wchar);

	bool isBackground(WCHAR wchar);

	WCHAR& getCharacterAtCoordinate(COORD coordinates);

	WORD& getColorAtCoordinate(COORD coordinates);
};