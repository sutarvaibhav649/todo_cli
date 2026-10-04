#include "todo/repository/task_repository.hpp"

#include <algorithm>
#include <sstream>

namespace todo {

    TaskRepository::TaskRepository(const std::string path): fileHandler(path) {}

    // Helper method to parse CSV lines into Task objects
    std::vector<Task> TaskRepository::readAll() const {
        std::vector<Task> tasks;
        auto lines = fileHandler.readLine();

        bool isHeader = true;
        for (const auto& line : lines) {
            // Skip CSV header line
            if (isHeader) {
                isHeader = false;
                continue;
            }

            auto fields = utility::FileHandler::parseCsvLine(line);
            if (fields.size() < 6) {
                continue;
            }

            Task task;
            task.setId(std::stoull(fields[0]));
            task.setTitle(fields[1]);
            task.setDescription(fields[2]);
            task.setStatus(static_cast<TaskStatus>(std::stoi(fields[3])));

            // Parse epoch timestamps back into utility::Timestamp
            std::time_t createdEpoch = static_cast<std::time_t>(std::stoll(fields[4]));
            std::time_t updatedEpoch = static_cast<std::time_t>(std::stoll(fields[5]));

            task.setCreatedAt(utility::Timestamp(createdEpoch));
            task.setUpdatedAt(utility::Timestamp(updatedEpoch));

            tasks.push_back(task);
        }
        return tasks;
    }

    // Helper method to write a list of Task objects back to the file
    static void persistTasks(const utility::FileHandler& fileHandler, const std::vector<Task>& tasks) {
        std::vector<std::string> lines;
        lines.reserve(tasks.size() + 1);

        // CSV Header
        lines.push_back("id,title,description,status,createdAt,updatedAt");

        for (const auto& task : tasks) {
            std::ostringstream ss;
            ss << task.getId() << ","
            << utility::FileHandler::escapeCsv(task.getTitle()) << ","
            << utility::FileHandler::escapeCsv(task.getDescription()) << ","
            << static_cast<int>(task.getStatus()) << ","
            << task.getCreatedAt() << ","
            << task.getUpdatedAt();

            lines.push_back(ss.str());
        }

        fileHandler.writeLines(lines);
    }

    std::optional<Task> TaskRepository::create(const Task& task) {
        auto tasks = readAll();

        std::uint64_t maxId = 0;
        for (const auto& t : tasks) {
            if (t.getId() > maxId) {
                maxId = t.getId();
            }
        }

        Task newTask = task;
        newTask.setId(maxId + 1);

        utility::Timestamp now;
        newTask.setCreatedAt(now);
        newTask.setUpdatedAt(now);

        tasks.push_back(newTask);
        persistTasks(fileHandler, tasks);

        return newTask;
    }

    std::optional<Task> TaskRepository::save(const Task& task) {
        if (task.getId() == 0) {
            return create(task);
        }
        return updateById(task.getId(), task);
    }

    std::optional<Task> TaskRepository::readById(std::uint64_t id) const {
        auto tasks = readAll();
        for (const auto& task : tasks) {
            if (task.getId() == id) {
                return task;
            }
        }
        return std::nullopt;
    }

    std::optional<Task> TaskRepository::updateById(std::uint64_t id, const Task& updatedTask) {
        auto tasks = readAll();
        for (auto& task : tasks) {
            if (task.getId() == id) {
                task.setTitle(updatedTask.getTitle());
                task.setDescription(updatedTask.getDescription());
                task.setStatus(updatedTask.getStatus());
                task.setUpdatedAt(utility::Timestamp{}); // Touch updatedAt timestamp

                persistTasks(fileHandler, tasks);
                return task;
            }
        }
        return std::nullopt;
    }

    void TaskRepository::deleteById(std::uint64_t id) {
        auto tasks = readAll();
        auto initialSize = tasks.size();

        tasks.erase(
            std::remove_if(tasks.begin(), tasks.end(), [id](const Task& t) {
                return t.getId() == id;
            }),
            tasks.end()
        );

        if (tasks.size() < initialSize) {
            persistTasks(fileHandler, tasks);
        }
    }

    void TaskRepository::deleteAll() {
        fileHandler.writeLines({"id,title,description,status,createdAt,updatedAt"});
    }

    bool TaskRepository::start(std::uint64_t id) {
        auto taskOpt = readById(id);
        if (!taskOpt) return false;

        Task task = *taskOpt;
        task.setStatus(TaskStatus::IN_PROGRESS);
        return updateById(id, task).has_value();
    }

    bool TaskRepository::complete(std::uint64_t id) {
        auto taskOpt = readById(id);
        if (!taskOpt) return false;

        Task task = *taskOpt;
        task.setStatus(TaskStatus::COMPLETED);
        return updateById(id, task).has_value();
    }

} // namespace todo