#pragma once
#include <string>
#include <iostream>

class Quest {
public:
    enum class Status { NotStarted, InProgress, Completed };

    Quest(const std::string& name, const std::string& description)
        : name(name), description(description), status(Status::NotStarted) {}

    Quest() : status(Status::NotStarted) {}

    void start();
    void update();
    void complete();

    const std::string& getName() const;
    const std::string& getDescription() const;
    Status getStatus() const;

private:
    std::string name;
    std::string description;
    Status status;
};
