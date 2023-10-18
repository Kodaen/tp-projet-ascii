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
	//////////////////////// Constructors ////////////////////////
private:
	BufferHandler();
	void initialize();
public:
	~BufferHandler();


	//////////////////////// Attributes ////////////////////////
private:

	HANDLE _hOutput;
	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

	CHAR_INFO _buffer[HEIGHT][WIDTH];

	static BufferHandler* _bufferHandlerInstance;

	//////////////////////// Methods ////////////////////////
public:

	static BufferHandler& Instance();

	void fillBuffer(const WCHAR& character, const WORD& color = FOREGROUND_RED);

	void emptyBuffer();

	void printBuffer();

	inline void drawAtCoordinate(const WCHAR& character, const WORD& color, const COORD& coordinates);

	void drawMap(const std::vector<std::wstring>& map, std::map<std::wstring, WORD> colors = {});

	void drawMapRow(const std::wstring& row, const short& x, std::map<std::wstring, WORD> colors = {});

	inline bool areDefaultColorsNeeded(const std::map<std::wstring, WORD>& colors);

	bool isTileWalkable(const COORD& coordinates);

	//////////////////////// Getters and Setters ////////////////////////

	inline bool isGround(const WCHAR& wchar);

	inline bool isWall(const WCHAR& wchar);

	inline bool isBackground(const WCHAR& wchar);

	inline bool isStair(const WCHAR& wchar);

	inline bool isWater(const WCHAR& wchar);

	bool isHealthPositive(const WCHAR& wchar);

	bool isHealthNegative(const WCHAR& wchar);

	inline WCHAR& getCharacterAtCoordinate(const COORD& coordinates);

	inline WORD& getColorAtCoordinate(const COORD& coordinates);
};