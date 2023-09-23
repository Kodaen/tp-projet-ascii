#pragma once

//#include <vector>
//#include <string>
//#include <windows.h>

class Level
{
public:
	Level(std::string levelName);

	std::vector<std::string> getLevel() {
		return _level;
	}

	std::string getLevelName() {
		return _levelName;
	}

	bool isTileWalkable(COORD coordinates);

private:
	std::vector<std::string> _level;
	std::string _levelName;

	void readFile(std::string fileName);

	void readLine(std::string line);

};

