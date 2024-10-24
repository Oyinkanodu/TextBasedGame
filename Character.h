#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Room.h"
#include "Quest.h"

using namespace std;

class Character
{
private:
	string name;
	int health;
	vector<Item> inventory;

public:
	Character(const string& name, int health);
	Character() {health = 0; };
	void TakeDamage(int damage);
	Room* GetLocation();
};


class Player :public Character {
public: 
	//Player(const string& name, int health);
	void setLocation(Room* loc);
	Room* GetLocation();
	Player(const std::string& name, int initialHealth) : health(initialHealth) {}

	int GetHealth() const { return health; }

	int GetTrapRoomHealthDeduction() const { return TRAP_ROOM_HEALTH_DEDUCTION; }

	void DeductHealth(int amount) {
		health -= amount;
		if (health < 0) {
			health = 0; // Ensure health doesn't go below 0
		}
	}
	int GetHealthPoints() const { return health; } // Getter function for health points

private:
	Room* location;
	int health;
	const int TRAP_ROOM_HEALTH_DEDUCTION = 25;
};





