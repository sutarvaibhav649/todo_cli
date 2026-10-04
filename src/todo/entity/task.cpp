#include "todo/entity/task.hpp"

namespace todo{

    //getters
    std::uint64_t Task::getId() const{
        return id;
    }

    std::string Task::getTitle() const{
        return title;
    }

    std::string Task::getDescription() const{
        return description;
    }

    TaskStatus Task::getStatus() const{
        return status;
    }

    std::string Task::getCreatedAt() const{
        return createdAt.toString();
    }

    std::string Task::getUpdatedAt() const{
        return updatedAt.toString();
    }

    //setters
    void Task::setId(std::uint64_t id){
        this->id = id;
    }

    void Task::setTitle(std::string title){
        this->title = title;
    }

    void Task::setDescription(std::string desc){
        this->description = desc;
    }

    void Task::setStatus(TaskStatus status){
        this->status = status;
    }
    
    void Task::setCreatedAt(utility::Timestamp createdAt){
        this->createdAt = createdAt;
    }

    void Task::setUpdatedAt(utility::Timestamp updatedAt){
        this->updatedAt = updatedAt;
    }
}
