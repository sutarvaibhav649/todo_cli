cmake_minimum_required(VERSION 3.22)

project(todo
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()


add_library(${PROJECT_NAME} STATIC
    src/main.cpp
    src/todo/entity/task.cpp
    src/utility/timestamp.cpp
    src/utility/file_handler.cpp
    src/todo/repository/task_repository.cpp
    src/todo/service/task_service.cpp
    src/todo/cli/command_handler.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(todo_cli 
        src/main.cpp
    )

target_link_libraries(todo_cli PRIVATE todo)
