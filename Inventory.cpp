#include "Inventory.h"
#include <iostream>
#include "Item.h"
#include <memory>
#include <vector>
#include "GameObject.h"
using namespace std;

void Inventory::addItem(const shared_ptr<Item>& item) {
    // Implement logic to add item to inventory
    items.push_back(item);
}



void Inventory::removeItem(size_t index) {
    // Validate the index
    if (index >= 0 && index < items.size()) {
        // Remove the item at the specified index
        items.erase(items.begin() + index);
    }
    else {
        cout << "Invalid index. Item not removed." << endl;
    }
}

void Inventory::removeItem(const string& itemName) {
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const shared_ptr<Item>& itemPtr) {
        return itemPtr->GetName() == itemName;
        });

    if (it != items.end()) {
        items.erase(it);
    }
}



void Inventory::displayItems() const {
    // Display items in the inventory with numbers
    cout << "Inventory Items:" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i]->GetName() << ": " << items[i]->GetDescription() << endl;
    }
}


size_t Inventory::getNumItems() const {
    return items.size();
}

bool Inventory::hasItem(const string& itemName) const {
    for (const auto& item : items) {
        if (item->GetName() == itemName) {
            return true;
        }
    }
    return false;
}
