#pragma once

//#include <vector>
//#include <string>
//#include <windows.h>

class Level
{
public:
	Level(int levelNumber);

	std::vector<std::wstring> getLevel() {
		return _level;
	}

	int getNumber() {
		return _levelNumber;
	}

	std::map<std::wstring, WORD> getColors() {
		return _levelColors;
	}

	bool isTileWalkable(COORD coordinates);

private:
	std::vector<std::wstring> _level;

	int _levelNumber;

	std::map<std::wstring, WORD> _levelColors;

	void readFile(std::string fileName);

	void readLine(std::wstring line);

	void parseColors(std::wstring line, std::vector<std::wstring>& colorsKeys, std::vector<WORD>& colorsValues);

	bool isEnemyOnTile(COORD coordinates);
};

