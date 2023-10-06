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

	bool isTileWalkable(COORD coordinates);

private:
	std::vector<std::wstring> _level;

	int _levelNumber;

	void readFile(std::string fileName);

	void readLine(std::wstring line);

};

