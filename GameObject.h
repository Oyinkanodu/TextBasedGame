#pragma once
#include <string>
#include <iostream>

    class GameObject {
    public:
        GameObject(const std::string& name) : name(name) {}
        virtual ~GameObject() = default;

        virtual void interact(GameObject& other) = 0; 

        const std::string& getName() const { return name; }

    protected:
        std::string name;
    };

    class Key : public GameObject {
    public:
        Key(const std::string& name) : GameObject(name) {}

        void interact(GameObject& other) override {
            // Implement interaction logic, e.g., unlock a door if 'other' is a Door
            // For simplicity, let's print a message
            std::cout << "Used " << getName() << " to interact with " << other.getName() << std::endl;
        }
    };

    class Door : public GameObject {
    public:
        Door(const std::string& name, bool isOpen = false) : GameObject(name), isOpen(isOpen) {}

        void interact(GameObject& other) override {
            // Implement interaction logic, e.g., open if interacted with a Key
            // For simplicity, let's print a message
            if (auto key = dynamic_cast<Key*>(&other)) {
                std::cout << "Used " << key->getName() << " to open " << getName() << std::endl;
                isOpen = true;
            }
            else {
                std::cout << "Cannot open " << getName() << ". Need a key." << std::endl;
            }
        }

        bool isOpened() const { return isOpen; }

    private:
        bool isOpen;
    };

