# TaskForge

TaskForge is a command-line task manager that helps you organize, track, and manage your daily tasks efficiently using a JSON-based storage system.

## 🚀 Features

- Add, edit, delete, and list tasks
- Search tasks by description, due date, priority, ID, or tags
- Tagging system for better task categorization
- Persistent storage using JSON
- Configurable file paths via `config.cfg`
- Colored terminal output (cross-platform support via virtual terminal enabling)

## 📁 Project Structure

```
include/        → Header files (TaskManager, color handling)
src/            → Source code for the TaskManager logic and command handling
main.cpp        → Entry point and command-line interface logic
config.cfg      → Stores the path to your active tasks JSON file
tasks.json      → JSON file where tasks are saved
```

## 🔧 Build Instructions

This project uses **CMake** as a build system.

### Requirements

- C++17 compatible compiler
- [nlohmann/json](https://github.com/nlohmann/json) (header-only, used for JSON operations)
- [CMake](https://cmake.org/) 3.10 or later

### Build Steps

```
git clone https://github.com/yourusername/TaskForge.git
cd TaskForge
mkdir build && cd build
cmake ..
cmake --build .
```

Run the executable:

```
./TaskForge
```

## 🧪 Example Usage

```
TaskForge >> add
TaskForge >> list
TaskForge >> edit
TaskForge >> del
TaskForge >> search
TaskForge >> help
TaskForge >> quit
```

## 📝 License

This project is licensed under the MIT License.

---

Built with ❤️ for command-line productivity.
