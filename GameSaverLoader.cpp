#include "GameSaverLoader.h"
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Area.h"
#include "Quest.h"
#include <vector>

using namespace std;

void GameSaverLoader::saveGame(const std::string& filename, const Player& player, const Area& gameWorld, const std::vector<Quest>& quests) {
    // Implement saving game state to a file
    ofstream outFile(filename, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    // Save player data
    outFile.write(reinterpret_cast<const char*>(&player), sizeof(Player));

    // Save game world data
    outFile.write(reinterpret_cast<const char*>(&gameWorld), sizeof(Area));

    // Save quests data
    for (const Quest& quest : quests) {
        outFile.write(reinterpret_cast<const char*>(&quest), sizeof(Quest));
    }

    outFile.close();
}

void GameSaverLoader::loadGame(const std::string& filename, Player& player, Area& gameWorld, std::vector<Quest>& quests) {
    // Implement loading game state from a file
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    // Load player data
    inFile.read(reinterpret_cast<char*>(&player), sizeof(Player));

    // Load game world data
    inFile.read(reinterpret_cast<char*>(&gameWorld), sizeof(Area));

    // Load quests data
    Quest quest;
    while (inFile.read(reinterpret_cast<char*>(&quest), sizeof(Quest))) {
        quests.push_back(quest);
    }

    inFile.close();
    }

