#include "Level.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>

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
