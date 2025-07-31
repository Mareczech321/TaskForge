cmake_minimum_required(VERSION 3.14)
project(TaskForge)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main.cpp
    src/commands.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

# Header files (for IDE visibility)
set(HEADERS
    include/CLIHandler.h
    include/colors.h
    include/commands.h
    include/json.hpp
    include/Task.h
    include/TaskManager.h
)

# Create executable
add_executable(TaskForge ${SOURCES} ${HEADERS})

# Platform-specific: Enable virtual terminal processing for Windows (optional)
if (WIN32)
    add_definitions(-D_USE_ANSI_COLORS)
endif()
