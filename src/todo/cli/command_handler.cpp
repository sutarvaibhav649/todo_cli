#include "todo/cli/command_handler.hpp"

#include <iostream>
#include <sstream>

namespace todo {

CommandHandler::CommandHandler(const std::string& dbPath)
    : service(dbPath) {}

void CommandHandler::execute(const std::string& inputLine) {
    std::istringstream iss(inputLine);
    std::string command;
    iss >> command;

    std::string remainingArgs;
    std::getline(iss >> std::ws, remainingArgs);

    if (command == "ADD") {
        handleAdd(remainingArgs);
    } else if (command == "GET") {
        handleGet(remainingArgs);
    } else if (command == "DEL") {
        handleDel(remainingArgs);
    } else if (command == "UPDATE") {
        handleUpdate(remainingArgs);
    } else if (command == "START") {
        handleStart(remainingArgs);
    } else if (command == "COM") {
        handleComplete(remainingArgs);
    } else if (command == "HELP") {
        printHelp();
    } else {
        std::cout << "Unknown command. Type HELP for available commands.\n";
    }
}

void CommandHandler::handleAdd(const std::string& args) {
    if (args.empty()) {
        std::cout << "Usage: ADD <title> [description]\n";
        return;
    }

    std::string title;
    std::string description;

    if (args.front() == '"') {
        size_t closeQuote = args.find('"', 1);
        if (closeQuote != std::string::npos) {
            title = args.substr(1, closeQuote - 1);
            if (closeQuote + 1 < args.length()) {
                description = args.substr(closeQuote + 1);
                size_t firstNonSpace = description.find_first_not_of(" ");
                description = (firstNonSpace != std::string::npos) ? description.substr(firstNonSpace) : "";
            }
        } else {
            title = args;
        }
    } else {
        std::istringstream iss(args);
        iss >> title;
        std::getline(iss >> std::ws, description);
    }

    auto created = service.addTask(title, description);
    if (created) {
        std::cout << "Task created with ID: " << created->getId() << "\n";
    }
}

void CommandHandler::handleGet(const std::string& args) {
    if (args.empty()) {
        std::cout << "Usage: GET <id> | GET *\n";
        return;
    }

    if (args == "*") {
        auto tasks = service.getAllTasks();
        if (tasks.empty()) {
            std::cout << "No tasks found.\n";
            return;
        }
        std::cout << "\n------------------ ALL TASKS ------------------\n";
        for (const auto& task : tasks) {
            std::cout << "[" << task.getId() << "] " << task.getTitle()
                      << " | Desc: " << task.getDescription()
                      << " | Status: " << task.getStatus()
                      << " | Created: " << task.getCreatedAt() << "\n";
        }
        std::cout << "-----------------------------------------------\n";
    } else {
        try {
            std::uint64_t id = std::stoull(args);
            auto task = service.getTask(id);
            if (task) {
                std::cout << "\nID:          " << task->getId() << "\n"
                          << "Title:       " << task->getTitle() << "\n"
                          << "Description: " << task->getDescription() << "\n"
                          << "Created At:  " << task->getCreatedAt() << "\n"
                          << "Updated At:  " << task->getUpdatedAt() << "\n";
            } else {
                std::cout << "Task with ID " << id << " not found.\n";
            }
        } catch (...) {
            std::cout << "Invalid ID parameter. Use a number or '*'.\n";
        }
    }
}

void CommandHandler::handleDel(const std::string& args) {
    if (args.empty()) {
        std::cout << "Usage: DEL <id> | DEL *\n";
        return;
    }

    if (args == "*") {
        service.clearAllTasks();
        std::cout << "All tasks deleted.\n";
    } else {
        try {
            std::uint64_t id = std::stoull(args);
            if (service.removeTask(id)) {
                std::cout << "Task " << id << " deleted.\n";
            }
        } catch (...) {
            std::cout << "Invalid ID parameter.\n";
        }
    }
}

void CommandHandler::handleUpdate(const std::string& args) {
    std::istringstream iss(args);
    std::uint64_t id;
    if (!(iss >> id)) {
        std::cout << "Usage: UPDATE <id> <title> [description]\n";
        return;
    }

    std::string remaining;
    std::getline(iss >> std::ws, remaining);

    if (remaining.empty()) {
        std::cout << "Usage: UPDATE <id> <title> [description]\n";
        return;
    }

    std::string title;
    std::string description;

    if (remaining.front() == '"') {
        size_t closeQuote = remaining.find('"', 1);
        if (closeQuote != std::string::npos) {
            title = remaining.substr(1, closeQuote - 1);
            if (closeQuote + 1 < remaining.length()) {
                description = remaining.substr(closeQuote + 1);
                size_t startPos = description.find_first_not_of(" ");
                description = (startPos != std::string::npos) ? description.substr(startPos) : "";
            }
        } else {
            title = remaining;
        }
    } else {
        std::istringstream remIss(remaining);
        remIss >> title;
        std::getline(remIss >> std::ws, description);
    }

    auto updated = service.updateTask(id, title, description);
    if (updated) {
        std::cout << "Task " << id << " updated successfully.\n";
    }
}

void CommandHandler::handleStart(const std::string& args) {
    if (args.empty()) {
        std::cout << "Usage: START <id>\n";
        return;
    }

    try {
        std::uint64_t id = std::stoull(args);
        if (service.markAsStarted(id)) {
            std::cout << "Task " << id << " marked as IN_PROGRESS.\n";
        } else {
            std::cout << "Task with ID " << id << " not found.\n";
        }
    } catch (...) {
        std::cout << "Invalid ID parameter. Use a valid integer ID.\n";
    }
}

void CommandHandler::handleComplete(const std::string& args) {
    if (args.empty()) {
        std::cout << "Usage: COM <id>\n";
        return;
    }

    try {
        std::uint64_t id = std::stoull(args);
        if (service.markAsCompleted(id)) {
            std::cout << "Task " << id << " marked as DONE.\n";
        } else {
            std::cout << "Task with ID " << id << " not found.\n";
        }
    } catch (...) {
        std::cout << "Invalid ID parameter. Use a valid integer ID.\n";
    }
}

void CommandHandler::printHelp() const {
    std::cout << "\nAvailable Commands:\n"
              << "  ADD \"<title>\" [description]  - Create new task\n"
              << "  GET *                        - List all tasks\n"
              << "  GET <id>                     - Get task by ID\n"
              << "  START <id>                   - Change task status to IN_PROGRESS\n"
              << "  COM <id>                     - Change task status to DONE\n"
              << "  DEL *                        - Delete all tasks\n"
              << "  DEL <id>                     - Delete task by ID\n"
              << "  UPDATE <id> \"<title>\" [desc] - Update task title/description\n"
              << "  EXIT                         - Exit application\n\n";
}

} // namespace todo