#pragma once

#include <string>
#include <ostream>

namespace todo{
    enum class TaskStatus{
        TODO,
        IN_PROGRESS,
        COMPLETED
    };

    inline std::string enumToString(TaskStatus status){
        switch(status){
            case TaskStatus::TODO: return "TODO"; break;
            case TaskStatus::IN_PROGRESS: return "IN_PROGRESS"; break;
            case TaskStatus::COMPLETED: return "COMPLETED"; break;

            default: return "UNKNOWN"; break;
        }
    }

    inline std::ostream& operator<< (std::ostream& os, TaskStatus status){
        os << enumToString(status);
        return os;
    }
};
