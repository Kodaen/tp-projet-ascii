#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>

#include "BufferHandler.h"
#include "Level.h"

Level::Level(std::string levelName)
{
	readFile(levelName);
}

void Level::readFile(std::string fileName)
{
	std::ifstream myfile(fileName, std::ifstream::in);
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			for (std::string line; std::getline(myfile, line); ) {
				readLine(line);
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void Level::readLine(std::string line)
{
	_level.push_back(line);
}

bool Level::isTileWalkable(COORD coordinates)
{
	return BufferHandler::Instance().getCharacterAtCoordinate(coordinates) == '.' ||
		BufferHandler::Instance().getCharacterAtCoordinate(coordinates) == '+' ||
		BufferHandler::Instance().getCharacterAtCoordinate(coordinates) == '#';
}

