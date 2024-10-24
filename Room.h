#pragma once
#include "Item.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Room
{
private:
	string description;
	map<string, Room*> exits;
	vector<Item> items;
	bool isTrapRoom; // Add a flag to indicate if the room is a trap room
public:
	Room(const string& desc);
	string GetName() const;
	void AddItem(const Item& item);
	void RemoveItem(const Item& item);
	void AddExit(string direction, Room* room);
	Room* GetExit(const string& direction);
	string GetDescription() const;
	vector<Item>& GetItems();
	map<string, Room*> GetExits() const;
	bool IsTrapRoom() const;
};
