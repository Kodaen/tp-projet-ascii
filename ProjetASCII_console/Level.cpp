#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <map>

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
	readFile(levelFileName, levelNumber);
}

void Level::readFile(std::string fileName, int levelNumber)
{
	// To read Unicode characters.
	// Source: https://stackoverflow.com/a/9903304.
	const std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wifstream myfile(fileName);
	myfile.imbue(utf8Locale);

	if (myfile.is_open())
	{
		std::vector<std::wstring> colorsKeys;
		std::vector<WORD> colorsValues;
		while (myfile.good())
		{
			int i = 0;
			for (std::wstring line; std::getline(myfile, line); ) {
				// Colors are always on the first line of the file.
				if (i == 0) {
					i++;

					parseColors(line, colorsKeys, colorsValues);
				}
				else {
					// Map is the rest of the file.
					readLine(line);
				}
			}

		}
		myfile.close();

		// Build the colors property.
		for (int i = 0; i < colorsKeys.size(); i++) {
			_levelColors.insert(std::pair < std::wstring, WORD >(colorsKeys[i], colorsValues[i]));
		}
	}
	else
	{	
		//std::cout << "Unable to open file";

		// If we couldn't open the file and it wasn't the first file.
		// Then it means it's the end of the game
		// We open the previous level(which is technically the current one) to
		// avoid weird display bugs 
		if (levelNumber > 1)
		{
			GameInstance::Instance().endOfGame();
			std::string levelFileName = "levels/level" + std::to_string(levelNumber-1) + ".txt";
			readFile(levelFileName, levelNumber);
		}
	}
}

void Level::readLine(std::wstring line)
{
	_level.push_back(line);
}

void Level::parseColors(std::wstring line, std::vector<std::wstring>& colorsKeys, std::vector<WORD>& colorsValues) {
	std::wstring pair;
	std::wstring item;
	std::wstringstream lineStream(line);

	while (std::getline(lineStream, pair, L',')) {
		std::wstringstream lineStream(pair);
		int i = 0;
		while (std::getline(lineStream, item, L':')) {
			if (i == 0) {
				colorsKeys.push_back(item);
				i++;
			}
			else if (i == 1) {
				std::wstringstream stream(item);
				WORD word;
				stream >> std::hex >> word;

				colorsValues.push_back(word);
			}
		}
	}
}

bool Level::isTileWalkable(COORD coordinates)
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	return !isEnemyOnTile(coordinates) && bufferHandler.isTileWalkable(coordinates);
}

bool Level::isEnemyOnTile(COORD coordinates)
{
	// TODO: Not optimal but required as the enemies update after the player.

	// Is there an enemy on the tile?
	bool enemyOnTile = false;
	std::vector<Entity*>& entites = GameInstance::Instance().getEntites();
	for (short i = 0; i < entites.size(); i++)
	{
		if (entites[i]->getPos().X == coordinates.X && entites[i]->getPos().Y == coordinates.Y)
		{
			enemyOnTile = true;
			break;
		}
	}

	return enemyOnTile;
}

void Level::hideSpawners()
{
	for (size_t x = 0; x < _level.size(); x++)
	{
		for (size_t y = 0; y < _level[x].size(); y++)
		{
			if (_level[x][y] == L'a' || _level[x][y] == L'q' || _level[x][y] == L'w' ||
				_level[x][y] == L'x' || _level[x][y] == L'c' || _level[x][y] == L'd' ||
				_level[x][y] == L'e' || _level[x][y] == L'z' || _level[x][y] == L'A' ||
				_level[x][y] == L'Q' || _level[x][y] == L'W' || _level[x][y] == L'X' ||
				_level[x][y] == L'C' || _level[x][y] == L'D' || _level[x][y] == L'E' ||
				_level[x][y] == L'Z') {
				_level[x][y] = L'.';
			}
		}
	}
}

void Level::hideSpawner(COORD coordinates)
{
	_level[coordinates.X][coordinates.Y] = L'.';
}



