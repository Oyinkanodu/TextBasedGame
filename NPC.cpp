#include "NPC.h"
#include "Quest.h"
#include <iostream>
using namespace std;

void NPC::addQuest(const Quest& quest) {
    quests.push_back(quest);
}

void NPC::interactWithPlayer(const vector<Quest>& playerQuests) {
    // Display available quests to the player
    cout << "Available Quests:" << endl;
    for (const Quest& quest : quests) {
        if (quest.getStatus() == Quest::Status::NotStarted) {
            cout << "- " << quest.getName() << ": " << quest.getDescription() << endl;
        }
    }

    // Check if the player has completed any quests
    for (const Quest& playerQuest : playerQuests) {
        for (Quest& npcQuest : quests) {
            if (npcQuest.getName() == playerQuest.getName() && npcQuest.getStatus() == Quest::Status::InProgress) {
                npcQuest.update(); // Update NPC quest based on player's progress
                if (npcQuest.getStatus() == Quest::Status::Completed) {
                    // Implement interaction based on completed quest
                    cout << "NPC: Thank you for completing the quest '" << npcQuest.getName() << "'!" << endl;
                }
            }
        }
    }
}
