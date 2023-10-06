#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>

#include "BufferHandler.h"
#include "Level.h"

#include "Direction.h"
#include "Entity.h"
#include <set>
#include "NYTimer.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "GameInstance.h"


Level::Level(int levelNumber)
{
	_levelNumber = levelNumber;
	std::string levelFileName = "levels/level" + std::to_string(levelNumber) + ".txt";
	readFile(levelFileName);
}

void Level::readFile(std::string fileName)
{
	// To read Unicode characters.
	// Source: https://stackoverflow.com/a/9903304.
	const std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wifstream myfile(fileName);
	myfile.imbue(utf8Locale);

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			for (std::wstring line; std::getline(myfile, line); ) {
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

void Level::readLine(std::wstring line)
{
	_level.push_back(line);
}

bool Level::isTileWalkable(COORD coordinates)
{
	// TODO : Not optimal

	// Is there an ennemy on the Tile ?
	bool ennemyOnTile = false;
	std::vector<Entity>& entites = GameInstance::Instance().getEntites();
	for (short i = 0; i < entites.size(); i++)
	{
		if (entites[i].getPos().X == coordinates.X && entites[i].getPos().Y == coordinates.Y)
		{
			ennemyOnTile = true;
			break;
		}
	}

	// Is there ground on this tile ?
	BufferHandler& bufferHandler = BufferHandler::Instance();
	bool tileIsGround = false;

	tileIsGround = bufferHandler.getCharacterAtCoordinate(coordinates) == '.' ||
		bufferHandler.getCharacterAtCoordinate(coordinates) == '+' ||
		bufferHandler.getCharacterAtCoordinate(coordinates) == '#';

	// Result
	return !ennemyOnTile && tileIsGround;

}

