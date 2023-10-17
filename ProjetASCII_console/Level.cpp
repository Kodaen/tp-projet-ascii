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

// Constructor, takes the level of a number then read the file named "level<levelNumber>.txt"
Level::Level(const int& levelNumber)
{
	_levelNumber = levelNumber;
	std::string levelFileName = "levels/level" + std::to_string(levelNumber) + ".txt";
	readFile(levelFileName, levelNumber);
}

// Tries to read given file and parse the colors mentionned in it (used for
// coloring the level and GameObjects).
// If the levelNumber is greater than 1 and the function couldn't find or read
// any file. Then we trigger the end of the game.
void Level::readFile(const std::string& fileName, const int& levelNumber)
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
			std::string levelFileName = "levels/level" + std::to_string(levelNumber - 1) + ".txt";
			readFile(levelFileName, levelNumber);
		}
	}
}

// Push given line in the _level attribute
void Level::readLine(std::wstring line)
{
	_level.push_back(line);
}

// Parses colors in given line and put them in a map. 
// This map is the one used for coloring the level and the Game Objects.
void Level::parseColors(const std::wstring& line, std::vector<std::wstring>& colorsKeys, std::vector<WORD>& colorsValues) {
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

// Checks if given tile is ground or if there is a GameObject on it
// if there is not the tile is walkable : returns true
bool Level::isTileWalkable(const COORD& coordinates)
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	return !isEnemyOnTile(coordinates) && bufferHandler.isTileWalkable(coordinates);
}

// Checks if there is an Entity (a.k.a ennemy) on the given tile.
// Returns true if there is.
bool Level::isEnemyOnTile(const COORD& coordinates)
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
	delete& entites;
	return enemyOnTile;
}

// Replace every spawner character contained in the buffer by the ground character.
// Making them disapear from the map.
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

// Replace spawner character contained in the buffer at give coordinates by the ground character.
// Making it disapear from the map.
void Level::hideSpawner(const COORD& coordinates)
{
	_level[coordinates.X][coordinates.Y] = L'.';
}



