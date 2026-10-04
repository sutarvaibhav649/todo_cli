#pragma once

#include "todo/enums/task_status.hpp"
#include "utility/timestamp.hpp"
#include <string>
#include <cstdint>

namespace todo{
    class Task{
        private:
            std::uint64_t id;
            std::string title;
            std::string description;
            TaskStatus status;
            utility::Timestamp createdAt;
            utility::Timestamp updatedAt;

        public:
            Task() = default;
            ~Task() = default;

            // getters
            std::uint64_t getId() const;
            std::string getTitle() const;
            std::string getDescription() const;
            TaskStatus getStatus() const;
            std::string getCreatedAt() const;
            std::string getUpdatedAt() const;

            // setters
            void setId(std::uint64_t id);
            void setTitle(std::string title);
            void setDescription(std::string desc);
            void setStatus(TaskStatus status);
            void setCreatedAt(utility::Timestamp createdAt);
            void setUpdatedAt(utility::Timestamp updatedAt);
    };
}
