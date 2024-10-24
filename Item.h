#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
using namespace std;

class Item {
private:
	string name;
	string description;
public:
	Item(const string& name, const string& desc);
	void Interact(GameObject& target) const;
	string GetName() const;
	string GetDescription() const;
};
