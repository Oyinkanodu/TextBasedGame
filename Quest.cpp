#include "Quest.h"
#include <iostream>
using namespace std;

// Start the quest
void Quest::start() {
    if (status == Status::NotStarted) {
        status = Status::InProgress;
    }
}


// Update the quest progress
void Quest::update() {
    if (status == Status::InProgress) {
        cout << "Quest '" << name << "' is in progress..." << endl;
    }
    else {
        cout << "Quest '" << name << "' is not in progress." << endl;
    }
}

// Complete the quest
void Quest::complete() {
    if (status == Status::InProgress) {
        cout << "Quest '" << name << "' completed!" << endl;
        status = Status::Completed;
    }
    else {
        cout << "Quest '" << name << "' cannot be completed, it has not been started or is already completed." << endl;
    }
}

// Getters
const string& Quest::getName() const {
    return name;
}

const string& Quest::getDescription() const {
    return description;
}

Quest::Status Quest::getStatus() const {
    return status;
}
