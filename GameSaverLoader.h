#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Character.h"
#include "Area.h"
using namespace std;
class GameSaverLoader
{
private:
	vector<Item> items;
public:
	void saveGame(const string& filename, const Player& player, const Area& gameWorld, const vector<Quest>& quests);
	void loadGame(const string& filename, Player& player, Area& gameWorld, vector<Quest>& quests);
};
// Usage example: GameSaverLoader gsl; gsl.saveGame("savefile.dat");
//gsl.loadGame("savefile.dat");


