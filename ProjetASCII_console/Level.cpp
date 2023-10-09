#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>

#include "BufferHandler.h"
#include "Level.h"

#include "Direction.h"
#include "GameObject.h"
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
	// TODO : Not optimal

	// Is there an ennemy on the Tile ?
	bool ennemyOnTile = false;
	std::vector<Entity*>& entites = GameInstance::Instance().getEntites();
	for (short i = 0; i < entites.size(); i++)
	{
		if (entites[i]->getPos().X == coordinates.X && entites[i]->getPos().Y == coordinates.Y)
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

