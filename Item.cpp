#include "Item.h"
#include <iostream>
#include <string>
#include "GameObject.h"

Item::Item(const string& name, const string& desc) : name(name), description(desc) {}

void Item::Interact(GameObject& target) const {
	cout << "Interacting with " << name << ": " << description << endl;
}

string Item::GetName() const
{
	return name;
}

string Item::GetDescription() const {
	return description;
}
