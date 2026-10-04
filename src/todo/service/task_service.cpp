#include "todo/service/task_service.hpp"

#include <algorithm>
#include <iostream>

namespace todo {

    TaskService::TaskService(const std::string& dbPath)
        : repository(dbPath) {}

    std::optional<Task> TaskService::addTask(const std::string& title, const std::string& description) {
        if (title.empty()) {
            std::cerr << "[Error] Task title cannot be empty.\n";
            return std::nullopt;
        }

        Task task;
        task.setTitle(title);
        task.setDescription(description);
        task.setStatus(TaskStatus::TODO);

        return repository.create(task);
    }

    std::optional<Task> TaskService::getTask(std::uint64_t id) const {
        return repository.readById(id);
    }

    std::vector<Task> TaskService::getAllTasks() const {
        return repository.readAll();
    }

    std::vector<Task> TaskService::getTasksByStatus(TaskStatus status) const {
        auto allTasks = repository.readAll();
        std::vector<Task> filtered;

        for (const auto& task : allTasks) {
            if (task.getStatus() == status) {
                filtered.push_back(task);
            }
        }
        return filtered;
    }

    std::optional<Task> TaskService::updateTask(std::uint64_t id, const std::string& title, const std::string& description) {
        auto taskOpt = repository.readById(id);
        if (!taskOpt) {
            std::cerr << "[Error] Task with ID " << id << " not found.\n";
            return std::nullopt;
        }

        if (title.empty()) {
            std::cerr << "[Error] Task title cannot be empty.\n";
            return std::nullopt;
        }

        Task task = *taskOpt;
        task.setTitle(title);
        task.setDescription(description);

        return repository.updateById(id, task);
    }

    bool TaskService::removeTask(std::uint64_t id) {
        auto taskOpt = repository.readById(id);
        if (!taskOpt) {
            std::cerr << "[Error] Cannot delete: Task with ID " << id << " does not exist.\n";
            return false;
        }

        repository.deleteById(id);
        return true;
    }

    void TaskService::clearAllTasks() {
        repository.deleteAll();
    }

    bool TaskService::markAsStarted(std::uint64_t id) {
        return repository.start(id);
    }

    bool TaskService::markAsCompleted(std::uint64_t id) {
        return repository.complete(id);
    }

} // namespace todo