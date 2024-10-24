#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"
#include <memory>
#include "Item.h"
using namespace std;

class Inventory
{
private:
    vector<shared_ptr<Item>> items; // Use shared_ptr for polymorphic behavior
public:
    void addItem(const shared_ptr<Item>& item);
    void removeItem(size_t index);
    void removeItem(const string& itemName);
    void useItem(const shared_ptr<Item>& item, GameObject& target);
    void displayItems() const;
    size_t getNumItems() const; // New method declaration
    bool hasItem(const string& itemName) const;
};

