#include "GameObject.h"
#include <iostream> 

void GameObject::interact(GameObject& other) {
    std::cout << "Default interaction between " << getName() << " and " << other.getName() << std::endl;
}
