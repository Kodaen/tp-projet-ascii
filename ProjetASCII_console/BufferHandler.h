#pragma once

//#include <windows.h>

#define HEIGHT 20 //MAX VALUE = 32,767
#define WIDTH 20  //MAX VALUE = 32,767


class BufferHandler
{
	// Constructor and destructor
private:
	BufferHandler();
	void initialize();

private:

	HANDLE _hOutput;
	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

	CHAR_INFO _buffer[HEIGHT][WIDTH];

	static BufferHandler* _bufferHandlerInstance;

public:
	~BufferHandler();

	static BufferHandler& Instance();

	void fillBuffer(WCHAR character);

	void emptyBuffer();

	void printBuffer();

	void drawAtCoordinate(WCHAR character, WORD color, COORD coordinates);


};