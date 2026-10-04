# TODO CLI Application

A lightweight, high-performance C++20 command-line task manager designed with **Clean Architecture**, persistent **CSV storage**, and **ISO 8601 UTC timestamps**.

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg?style=flat-square&logo=c%2B%2B)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-064F8C.svg?style=flat-square&logo=cmake)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)

---

## Key Features

- **Clean & Layered Architecture**: Clear separation across Domain Models, Repository, Service, and CLI layers.
- **Persistent CSV Storage**: Custom, robust CSV parser with automatic quote escaping.
- **ISO 8601 UTC Timestamps**: Automatic creation and modification timestamping.
- **Zero External Dependencies**: Built entirely using standard C++ libraries (`<chrono>`, `<filesystem>`, `<sstream>`).
- **Interactive REPL Interface**: Fast, intuitive terminal interface with command parsing.

---

## System Architecture

```text
       ┌─────────────────────────┐
       │   CLI (CommandHandler)  │  <-- Parses interactive user commands
       └────────────┬────────────┘
                    │
       ┌────────────▼────────────┐
       │      TaskService        │  <-- Business logic & status transitions
       └────────────┬────────────┘
                    │
       ┌────────────▼────────────┐
       │     TaskRepository      │  <-- Data CRUD operations & ID generation
       └────────────┬────────────┘
                    │
       ┌────────────▼────────────┐
       │       FileHandler       │  <-- Low-level CSV file I/O & escaping
       └─────────────────────────┘
```
---
# Getting Started
## Prerequisites
- C++ Compiler: GCC 10+, Clang 11+, or MSVC (supporting C++20 standard)
- Build Tool: CMake (>= 3.15)

## Build Instructions
**Clone Repository**
```bash
git clone https://github.com/sutarvaibhav649/todo_cli.git
cd todo_cli
```

**Configure with CMake**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

**Compile the executable**
```bash
cmake --build build
```

**Run the CLI**
```bash
./build/todo_cli
```
---
# Command Reference

| Command  | Syntax                            | Description                                                  |
| -------- | --------------------------------- | ------------------------------------------------------------ |
| `HELP`   | `HELP`                            | Show available commands                                      |
| `ADD`    | `ADD "<title>" [description]`     | Create a new task with title and optional description        |
| `GET`    | `GET *` \| `GET <id>`             | Retrieve all tasks or display detailed info for a single task|
| `START`  | `START <id>`                      | Update task status to `IN_PROGRESS`                          |
| `COM`    | `COM <id>`                        | Update task status to `COMPLETED`                                 |
| `UPDATE` | `UPDATE <id> "<title>" [desc]`    | Modify title and/or description of an existing task          |
| `DEL`    | `DEL <id>` \| `DEL *`             | Delete a specific task or remove all tasks                   |
| `EXIT`   | `EXIT`                            | Exit the CLI application                                     |

---
## Usage Example
```text
=========================================
        TODO CLI Application Ready       
=========================================
Type HELP to view available commands.

todo> ADD "Learn C++ Architecture" Complete repository and service layers
Task created with ID: 1

todo> START 1
Task 1 marked as IN_PROGRESS.

todo> GET 1

ID:          1
Title:       Learn C++ Architecture
Description: Complete repository and service layers
Created At:  2026-10-04T05:15:20Z
Updated At:  2026-10-04T05:16:02Z

todo> COM 1
Task 1 marked as DONE.

todo> GET *

------------------ ALL TASKS ------------------
[1] Learn C++ Architecture | Desc: Complete repository and service layers | Created: 2026-10-04T05:15:20Z
-----------------------------------------------
```
---

## Project Structure
```text
todo_cli/
├── CMakeLists.txt
├── include/
│   ├── todo/
│   │   ├── cli/
│   │   │   └── command_handler.hpp
│   │   ├── entity/
│   │   │   └── task.hpp
│   │   ├── enums/
│   │   │   └── task_status.hpp
│   │   ├── repository/
│   │   │   └── task_repository.hpp
│   │   └── service/
│   │       └── task_service.hpp
│   └── utility/
│       ├── file_handler.hpp
│       └── timestamp.hpp
└── src/
    ├── main.cpp
    ├── todo/
    │   ├── cli/command_handler.cpp
    │   ├── entity/task.cpp
    │   ├── repository/task_repository.cpp
    │   └── service/task_service.cpp
    └── utility/
        ├── file_handler.cpp
        └── timestamp.cpp
```
---

## License
This project is open-source and licensed under the MIT License.