#pragma once
#include <vector>
#include "Quest.h"
#include <iostream>
#include "Character.h"
#include "Room.h"
using namespace std;

class NPC {
private:
    enum State { Idle, Aggressive, Fleeing };
    State currentState;
    string name;
    vector<Quest> quests;
public:
    NPC(const string& npcName) : name(npcName), quests() {} // Initialize quests vector in the constructor
    void interactWithPlayer(const vector<Quest>& playerQuests);
    void addQuest(const Quest& quest);
};

