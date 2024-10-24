#include "Area.h"
#include <iostream>
#include <string>

void Area::AddRoom(const string& name, Room* room){
	rooms[name] = room;
}

Room* Area::GetRoom(const string& name)
{
	return nullptr;
}

void Area::ConnectRooms(const string& room1Name, const string& room2Name, const string& direction){
	Room* room1 = GetRoom(room1Name);
	Room* room2 = GetRoom(room2Name);

	if (room1 != nullptr && room2 != nullptr) {
		room1->AddExit(direction, room2);
		room2->AddExit(direction, room1);
	}
}

void Area::LoadMapFromFile(const string& filename)
{
}

Room* Area::GetRoomByDescription(const std::string& description) {
	// Iterate through all rooms in the area
		for (auto& pair : rooms) {
			Room* room = pair.second;
			if (room->GetDescription() == description) {
				return room; // Return a pointer to the room if its description matches
			}
		}
	return nullptr; // Return nullptr if no room with the given description is found
}

