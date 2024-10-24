#include "Room.h"
#include "Item.h"
#include <iostream>
#include <string>
#include "NPC.h"
using namespace std;

Room::Room(const string& desc) {
	description = desc;
}


void Room::AddItem(const Item& item) {
	items.push_back(item);
}


void::Room::RemoveItem(const Item& item) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		if (it->GetName() == item.GetName()) {
			items.erase(it);
			break;
		}
	}
}
void Room::AddExit(string direction, Room* room) {
	exits[direction] = room;
};

string Room::GetDescription() const {
	return description;
}

Room* Room::GetExit(const string& direction) {
	auto it = exits.find(direction);
	return (it != exits.end()) ? it->second : nullptr;
}

map<string, Room*> Room::GetExits() const {
	return exits;
}

 vector<Item>& Room::GetItems() {
	return items;
}

 bool Room::IsTrapRoom() const {
	 return description.find("trap") != std::string::npos;
 }
