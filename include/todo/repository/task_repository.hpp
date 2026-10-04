#pragma once

#include "todo/entity/task.hpp"
#include "utility/file_handler.hpp"

#include <vector>
#include <optional>

namespace todo{
    class TaskRepository{
        private:
            utility::FileHandler fileHandler;

        public:
            TaskRepository(std::string path = "tasks.csv");

            std::optional<Task> save(const Task& task);
            std::optional<Task> create(const Task& task);
            std::optional<Task> readById(std::uint64_t id) const;
            std::vector<Task> readAll() const;
            std::optional<Task> updateById(std::uint64_t, const Task& task);
            void deleteById(std::uint64_t id);
            void deleteAll();

            bool start(std::uint64_t id);
            bool complete(std::uint64_t id);
    };
};
