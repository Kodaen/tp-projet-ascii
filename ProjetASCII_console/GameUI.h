#pragma once

#include <string>

class GameUI
{
public:
	GameUI();
	void displayStats();

private:
	std::wstring _stats;
	void createStats();
};

