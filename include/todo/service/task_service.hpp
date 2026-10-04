#pragma once

#include "todo/entity/task.hpp"
#include "todo/repository/task_repository.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace todo {

class TaskService {
private:
    TaskRepository repository;

public:
    explicit TaskService(const std::string& dbPath = "tasks.csv");

    // Business Workflows
    std::optional<Task> addTask(const std::string& title, const std::string& description = "");
    std::optional<Task> getTask(std::uint64_t id) const;
    std::vector<Task> getAllTasks() const;
    std::vector<Task> getTasksByStatus(TaskStatus status) const;

    std::optional<Task> updateTask(std::uint64_t id, const std::string& title, const std::string& description);
    bool removeTask(std::uint64_t id);
    void clearAllTasks();

    // Status Transitions
    bool markAsStarted(std::uint64_t id);
    bool markAsCompleted(std::uint64_t id);
};

} // namespace todo