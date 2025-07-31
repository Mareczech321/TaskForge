cmake_minimum_required(VERSION 3.10)
project(TaskForge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Helpful compiler warnings
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Include directory
include_directories(include)

# Header files
set(HEADERS
    include/CLIHandler.h
    include/colors.h
    include/commands.h
    include/json.hpp
    include/Task.h
    include/TaskManager.h
)

# Source files
set(SOURCES
    main.cpp
    src/commands.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

# Define the executable
add_executable(TaskForge ${SOURCES})

# Link stdc++fs for older GCC versions (optional for GCC 9+)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(TaskForge stdc++fs)
endif()
