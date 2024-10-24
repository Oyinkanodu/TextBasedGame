#include <iostream>
#include <vector>
#include <map>
#include "Room.h"
#include "Item.h"
#include "Character.h"
#include "Area.h"
#include "NPC.h"
#include "Quest.h"
#include "Inventory.h"
#include "GameObject.h"
#include "GameSaverLoader.h"
using namespace std;

int main() {
	// Define an NPC named "Villager"
	NPC villager("Villager");

	//Create Rooms
	Room startRoom("You are in a dimly lit room.");
	Room hallway("You are in a long hallway");
	Room treasureRoom("You have entered a treasure room!");
	Room trapRoom("You have entered a trap room! Spikes line the walls.");
	Room villagerRoom("Room with Villager");

	//Define exists between rooms
	startRoom.AddExit("north", &hallway);
	hallway.AddExit("south", &treasureRoom);
	treasureRoom.AddExit("south", &hallway);
	hallway.AddExit("west", &trapRoom);
	trapRoom.AddExit("east", &hallway);
	treasureRoom.AddExit("north", &villagerRoom);
	villagerRoom.AddExit("east", &hallway);

	// Create Items
	Item key("Key", "A shiny key that looks important.");
	Item sword("Sword", "A sharp sword with a golden hit.");
	Item potion("Potion", "A healing potion to restore health.");
	Item map("Map", "A detailed map of the area.");
	Item lostArtifact("Lost Artifact", "A valuable artifact lost in the dungeon.");
	Item PestRepellent("Pest Repellent", "A potent spray formulated to repel pests of all kinds");

	// Add items to rooms
	startRoom.AddItem(key);
	hallway.AddItem(map);
	treasureRoom.AddItem(sword);
	treasureRoom.AddItem(potion);
	treasureRoom.AddItem(lostArtifact);
	villagerRoom.AddItem(PestRepellent);

	// Create shared pointers for the items
	shared_ptr<Item> keyPtr = make_shared<Item>(key);
	shared_ptr<Item> swordPtr = make_shared<Item>(sword);
	shared_ptr<Item> potionPtr = make_shared<Item>(potion);
	shared_ptr<Item> mapPtr = make_shared<Item>(map);


	// Create an instance of the Inventory class
	Inventory playerInventory;

	// Create a player
	Player player("Alice", 100);

	//set the player's starting location
	player.setLocation(&startRoom);


	//Create quests
	vector<Quest> availableQuests;
	availableQuests.push_back(Quest("Main Quest", "Defeat the final boss"));
	availableQuests.push_back(Quest("Side Quest 1", "Retrieve a lost artifact"));
	availableQuests.push_back(Quest("Side Quest 2", "Help a villager in need"));


	// Create an instance of the GameSaverLoader class
	GameSaverLoader gameSaverLoader;

	//Create an instance of the Area class
	Area gameWorld;

	// Load the game map from a text file
	gameWorld.LoadMapFromFile("game_map.txt");

	// Set the player's starting room (you can modify this room name)
	Room* currentRoom = gameWorld.GetRoom("StartRoom");

	//Create an instance of an NPC class
	NPC npc("Bob");

	// Create instances of Key and Door
	Key goldenKey("Golden Key");
	Door door("Secret Door");

	// Interact with GameObjects
	cout << "Interacting with the door using the key..." << endl;
	goldenKey.interact(door);


	// Game loop
	while (true)
	{
		// Display player's health
		cout << "Player's Health: " << player.GetHealth() << endl;

		// Display current location information, including items in the room
		cout << "Current Location: " << player.GetLocation()->GetDescription() << endl;
		cout << "Items in the room: ";
		const vector<Item>& roomItems = player.GetLocation()->GetItems();
		if (roomItems.empty()) {
			cout << "There are no items in the room." << endl;
		}
		else {
			for (const Item& item : roomItems) {
				cout << item.GetName() << ", ";
			}
			cout << endl;
		}

		// Display exits available
		cout << "Exits available: ";
		for (const auto& exit : player.GetLocation()->GetExits()) {
			cout << exit.first << " ";
		}
		cout << endl;

		cout << "| ";
		cout << "Options: ";
		cout << "1. Look around | ";
		cout << "2. Interact with an item | ";
		cout << "3. Move to another room | ";
		cout << "4. Pick a quest |";
		cout << "5. Save game | ";
		cout << "6. View inventory | "; 
		cout << "7. Interact with NPC |"; 
		cout << "8. Quit |" << endl;



		int choice;
		cin >> choice;

		if (choice == 1) {
			//Player looks around (no action required)
			cout << "You look around the room." << endl;
		}
		else if (choice == 2) {
			// Get the items in the room
			const vector<Item>& roomItems = player.GetLocation()->GetItems();

			// Check if there are items in the room
			if (roomItems.empty()) {
				cout << "There are no items in the room to interact with." << endl;
			}
			else {
				// Display available items in the room
				cout << "Items in the room:" << endl;
				for (size_t i = 0; i < roomItems.size(); ++i) {
					cout << i + 1 << ". " << roomItems[i].GetName() << endl;
				}

				cout << "Enter the number of the item you want to interact with (or 0 to cancel): ";
				size_t index;
				cin >> index;

				if (index >= 1 && index <= roomItems.size()) {
					// Get the shared pointer to the item
					shared_ptr<Item> selectedItem = make_shared<Item>(roomItems[index - 1]);

					// Add the item to the inventory
					playerInventory.addItem(selectedItem);
					cout << "Item picked up and added to inventory." << endl;

					// Check if the item retrieved is the Lost Artifact
					if (selectedItem->GetName() == "Lost Artifact") {
						// Mark Side Quest 1 as completed
						for (Quest& quest : availableQuests) {
							if (quest.getName() == "Side Quest 1") {
								quest.complete();
								cout << "Quest 'Side Quest 1' completed!" << endl;
								break;
							}
						}
					}
				}
				else if (index != 0) {
					cout << "Invalid item number." << endl;
				}
			}
		}



		else if (choice == 3) {
			// Player moves to another room
			cout << "Enter the direction (e.g., north, south): ";
			string direction;
			cin >> direction;
			Room* nextRoom = player.GetLocation()->GetExit(direction);
			if (nextRoom != nullptr) {
				player.setLocation(nextRoom);
				cout << "You move to the next room." << endl;

				// Check if it's a trap room
				if (nextRoom->IsTrapRoom()) {
					// Deduct health
					player.DeductHealth(25);
					cout << "You stepped into a trap! Health reduced by 25 points." << endl;

					// Check if player's health is zero or less
					if (player.GetHealth() <= 0) {
						cout << "Player's Health: 0" << endl;
						cout << "Game Over! Defeated by the dragon." << endl;
						return 0; // Exit the game
					}
				}
			}
			else {
				cout << "You attempted to go " << direction << ", but there's no path in that direction." << endl;
				// Deduct health for wrong exit
				player.DeductHealth(25);
				cout << "You got injured for taking the wrong direction! Health reduced by 25 points." << endl;

				// Check if player's health is zero or less
				if (player.GetHealth() <= 0) {
					cout << "Player's Health: 0" << endl;
					cout << "Game Over! Defeated by the dragon." << endl;
					return 0; // Exit the game
				}
			}
		}


		else if (choice == 4) {
			// Display available quests with their status
			cout << "Available quests:" << endl;
			size_t availableCount = 0; // Track the number of available quests

			for (const Quest& quest : availableQuests) {
				cout << availableCount + 1 << ". " << quest.getName() << ": " << quest.getDescription() << " - ";
				switch (quest.getStatus()) {
				case Quest::Status::NotStarted:
					cout << "Not Started" << endl;
					break;
				case Quest::Status::InProgress:
					cout << "In Progress" << endl;
					break;
				case Quest::Status::Completed:
					cout << "Completed" << endl;
					break;
				}
				++availableCount;
			}

			// Pick a quest if available quests exist
			if (availableCount > 0) {
				cout << "Enter the number of the quest you want to pick: ";
				size_t questChoice;
				cin >> questChoice;

				// Validate the quest choice
				if (questChoice >= 1 && questChoice <= availableCount) {
					// Get the selected quest
					Quest& selectedQuest = availableQuests[questChoice - 1];

					// Check player's health before starting any quest
					if (player.GetHealth() < 50) {
						cout << "Your health is too low to undertake any quest. You were instantly defeated." << endl;
						return 0; // End the game
					}

					// Start or complete the selected quest
					if (selectedQuest.getName() == "Side Quest 1") {
						bool hasLostArtifact = playerInventory.hasItem("Lost Artifact");
						if (hasLostArtifact) {
							selectedQuest.complete();
							cout << "Quest 'Side Quest 1' completed!" << endl;
						}
						else {
							selectedQuest.start();
							cout << "Quest 'Side Quest 1' started!" << endl;
						}
					}
					else if (selectedQuest.getName() == "Side Quest 2") {
						bool hasPestRepellent = playerInventory.hasItem("Pest Repellent");
						if (hasPestRepellent) {
							selectedQuest.complete();
							cout << "Quest 'Side Quest 2' completed!" << endl;
						}
						else {
							selectedQuest.start();
							cout << "Quest 'Side Quest 2' started!" << endl;
						}
					}
					else if (selectedQuest.getName() == "Main Quest") {
						bool allSideQuestsCompleted = true;
						for (const Quest& sideQuest : availableQuests) {
							if (sideQuest.getName().find("Side Quest") != string::npos && sideQuest.getStatus() != Quest::Status::Completed) {
								allSideQuestsCompleted = false;
								break;
							}
						}
						if (allSideQuestsCompleted) {
							// Start the main quest
							selectedQuest.start();
							cout << "Main Quest started!" << endl;

							// Prompt the player to interact with the NPC dragon
							cout << "You have completed all side quests! The fearsome Dragon approaches!" << endl;
							cout << "Do you dare to face the Dragon? (Enter 'Y' for yes, 'N' for no): ";
							char dragonChoice;
							cin >> dragonChoice;

							if (dragonChoice == 'Y') {
								bool hasGoldenSword = playerInventory.hasItem("Golden Sword");
								if (hasGoldenSword) {
									// Player wins the game
									cout << "You wield the legendary Golden Sword and strike down the Dragon! Victory is yours!" << endl;
									cout << "Congratulations! You have defeated the Dragon and completed the game!" << endl;
								}
								else {
									// Player loses the game
									cout << "You face the Dragon unprepared and are swiftly defeated. Game Over!" << endl;
								}
								return 0; // End the game
							}
							else {
								cout << "You wisely choose not to face the Dragon just yet. Proceed with caution!" << endl;
							}
						}
						else {
							cout << "You need to complete all the side quests to undertake the main quest." << endl;
						}
					}
				}
				else {
					cout << "Invalid quest choice." << endl;
				}
			}
			else {
				cout << "No available quests." << endl;
			}
		}



		else if (choice == 5) {
			// Save game
			gameSaverLoader.saveGame("savefile.dat", player, gameWorld, availableQuests);
			cout << "Game saved successfully." << endl;
			}
		else if (choice == 6) {
			// View inventory
			cout << "Inventory:" << endl;
			playerInventory.displayItems();

			// Ask the user to select an item to remove
			if (playerInventory.getNumItems() > 0) {
				cout << "Enter the number of the item you want to remove (or 0 to cancel): ";
				size_t index;
				cin >> index;

				if (index >= 1 && index <= playerInventory.getNumItems()) {
					// Remove the item from the inventory
					playerInventory.removeItem(index - 1); // Adjust index to 0-based
					cout << "Item removed from inventory." << endl;
				}
				else if (index != 0) {
					cout << "Invalid item number." << endl;
				}
			}
			else {
				cout << "Inventory is empty." << endl;
			}
	}


		else if (choice == 7) {
    // Interact with NPC for hints or quest completion
    cout << "You see a villager in need. They seem distressed." << endl;
    cout << "1. Talk to the villager." << endl;
    cout << "2. Give an item to the villager." << endl;
    cout << "3. Ask for information on how to defeat the dragon boss." << endl; // New option
    int npcChoice;
    cin >> npcChoice;
    if (npcChoice == 1) {
        // Provide some dialogue or information
        cout << "Villager: Oh, kind adventurer, I'm in desperate need of pest repellent. Those pesky creatures have infested my home." << endl;
    }
    else if (npcChoice == 2) {
        // Check if the player has the Pest Repellent
        bool hasPestRepellent = playerInventory.hasItem("Pest Repellent");
        if (hasPestRepellent) {
            // Remove the Pest Repellent from the player's inventory
            playerInventory.removeItem("Pest Repellent");

            // Provide feedback to the player
            cout << "You give the Pest Repellent to the villager." << endl;
            cout << "Villager: Oh, thank you so much! Please take this as a token of my gratitude." << endl;



            // Mark Side Quest 2 as completed
            for (Quest& quest : availableQuests) {
                if (quest.getName() == "Side Quest 2") {
                    quest.complete();
                    break;
                }
            }

            // Add the golden sword to the player's inventory as a reward
            Item goldenSword("Golden Sword", "A legendary sword with the power to slay dragons.");
            playerInventory.addItem(make_shared<Item>(goldenSword));
            cout << "You receive the Golden Sword as a reward!" << endl;
        }
        else {
            // Inform the player that they don't have the required item
            cout << "You don't have the Pest Repellent to give to the villager." << endl;
        }
    }
    else if (npcChoice == 3) {
        // Provide information on how to defeat the dragon boss
        cout << "Villager: Ah, defeating the dragon boss requires a powerful weapon. Legends say that only the Golden Sword, a legendary weapon hidden deep within the dungeon, can vanquish the mighty dragon. But be warned, the dragon's strength is formidable, and it won't be an easy battle." << endl;
    }
    else {
        // Invalid choice
        cout << "Invalid choice." << endl;
    }
}



		else if (choice == 8) {
			// Quit
			cout << "Goodbye!" << endl;
			return 0;
			break;
		}
		else {
			// Invalid choice
			cout << "Invalid choice. Try again." << endl;
		}


	}
		
	}

