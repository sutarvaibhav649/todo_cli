#pragma once

#include "todo/service/task_service.hpp"
#include <string>

namespace todo {

class CommandHandler {
private:
    TaskService service;

    void handleAdd(const std::string& args);
    void handleGet(const std::string& args);
    void handleDel(const std::string& args);
    void handleUpdate(const std::string& args);
    void handleStart(const std::string& args);
    void handleComplete(const std::string& args);
    void printHelp() const;

public:
    explicit CommandHandler(const std::string& dbPath = "tasks.csv");
    void execute(const std::string& inputLine);
};

} // namespace todo