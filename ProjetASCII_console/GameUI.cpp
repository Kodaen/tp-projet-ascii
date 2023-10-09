#include <windows.h>
#include "vector"
#include <set>
#include <string>
#include <sstream>

#include "NYTimer.h"
#include "GameUI.h"
#include "Level.h"
#include "Direction.h"
#include "GameObject.h"
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
	std::wstringstream wstats;
	wstats << "Étage : ";
	wstats << gameInstance.getcurrentLevel().getNumber();

	wstats << "            -- Joueur --";
	wstats << " Pv : ";
	wstats << gameInstance.getPlayerCharacter().getHP();
	wstats << " Dégâts : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	wstats << " Niveau : ";
	wstats << gameInstance.getPlayerCharacter().getDamage();
	_stats.append(wstats.str());
}
