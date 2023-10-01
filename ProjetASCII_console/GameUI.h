#pragma once

#include <string>

class GameUI
{
public:
	GameUI();
	void displayStats();

private:
	std::string _stats;
	void createStats();
};

