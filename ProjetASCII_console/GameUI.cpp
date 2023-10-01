#include <windows.h>
#include "vector"
#include <set>
#include <string>

#include "NYTimer.h"
#include "GameUI.h"
#include "Level.h"
#include "Direction.h"
#include "Entity.h"
#include "PlayerController.h"
#include "PlayerCharacter.h"
#include "gameInstance.h"
#include "BufferHandler.h"

#include "GameUI.h"


GameUI::GameUI()
{
	createStats();
}

void GameUI::displayStats()
{
	BufferHandler& bufferHandler = BufferHandler::Instance();
	// Hard coded value because HEIGHT can't be used now that it's greater than the console's height.
	// TODO: find how to retrieve it instead.
	bufferHandler.DrawMapRow(_stats, 29);
}

void GameUI::createStats()
{
	GameInstance& gameInstance = GameInstance::Instance();
	_stats.append("Level: ");
	_stats.append(std::to_string(gameInstance.getcurrentLevel().getNumber()));

	// Can't display more info with current buffer width.
	// TODO: fix the bug for different buffer HEIGHT and WIDTH.
	_stats.append(" -- Player --");
	_stats.append(" Hp: ");
	_stats.append(std::to_string(gameInstance.getPlayerCharacter().getHP()));
	_stats.append(" Damage: ");
	_stats.append(std::to_string(gameInstance.getPlayerCharacter().getDamage()));
	_stats.append(" Level: ");
	_stats.append(std::to_string(gameInstance.getPlayerCharacter().getDamage()));

}
