#include "Character.h"
#include "Room.h"
#include <iostream>
#include <string>
using namespace std;

Character::Character(const string& name, int health) : name(name), health(health)
{
}

void Character::TakeDamage(int damage){
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}



void Player:: setLocation(Room* loc) {
	location = loc;
}



Room* Player::GetLocation(){
	return location;  
}


