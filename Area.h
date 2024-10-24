#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Item.h"
#include "Room.h"
using namespace std;

class Area
{
private:
	map<string, Room*>rooms;
public:
	void AddRoom(const string& name, Room* room);
	Room* GetRoom(const string& name);
	void ConnectRooms(const string& room1Name, const string& room2Name, const string& direction);
	void LoadMapFromFile(const string& filename);
	Room* GetRoomByDescription(const std::string& description);
};

