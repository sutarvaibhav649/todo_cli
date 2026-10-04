#include "todo/cli/command_handler.hpp"

#include <iostream>
#include <string>

int main() {
    todo::CommandHandler cli("tasks.csv");

    std::cout << "=========================================\n";
    std::cout << "        TODO CLI Application Ready       \n";
    std::cout << "=========================================\n";
    std::cout << "Type HELP to view available commands.\n\n";

    std::string line;
    while (true) {
        std::cout << "todo> ";
        if (!std::getline(std::cin, line) || line == "EXIT" || line == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (line.empty()) continue;

        cli.execute(line);
    }

    return 0;
}