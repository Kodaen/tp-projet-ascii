#pragma once

//#include <vector>
//#include <string>
//#include <windows.h>
//#include <map>

class Level
{
public:
	Level(const int& levelNumber);

	std::map<std::wstring, WORD> &getColors() {
		return _levelColors;
	}

	bool isTileWalkable(const COORD& coordinates);

	void hideSpawners();

	void hideSpawner(const COORD& coordinates);

	std::vector<std::wstring>& getLevel() {
		return _level;
	}

	int getNumber() {
		return _levelNumber;
	}

private:
	std::vector<std::wstring> _level;

	int _levelNumber;

	std::map<std::wstring, WORD> _levelColors;

	void readFile(const std::string& fileName, const int& levelNumber = 1);

	void readLine(std::wstring line);

	void parseColors(const std::wstring& line, std::vector<std::wstring>& colorsKeys, std::vector<WORD>& colorsValues);

	bool isEnemyOnTile(const COORD& coordinates);
};

