<p align="center">
  <h1 align="center">📋 TaskForge - C++ CLI Task Manager</h1>
</p>
<p align="center">
  A colorful and intuitive C++ command-line tool for managing tasks with JSON persistence.
</p>

<div align="center">
  <img src="https://img.shields.io/badge/code-C++-blue.svg" />
  <img src="https://img.shields.io/badge/status-active-brightgreen.svg" />
  <img src="https://img.shields.io/github/languages/count/Mareczech321/TaskForge.svg" />
  <img src="https://img.shields.io/github/last-commit/Mareczech321/TaskForge.svg" />
</div>

---

## 📖 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Future Work](#future-work)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## 📌 Overview

**TaskForge** is a cross-platform, modern C++ task manager that runs entirely in your terminal. It allows you to organize, track, and manage your tasks using a colorful CLI and `nlohmann/json` for structured data storage. Designed for simplicity and functionality, it's perfect for developers and CLI enthusiasts.

---

## ✨ Features

- ✅ Add, edit, delete, and list tasks
- ✅ Tag-based filtering and management
- ✅ Search by description, tags, due date, priority, or ID
- ✅ Configurable file path storage using `config.cfg`
- ✅ JSON-based persistence using `nlohmann/json`
- ✅ Color-coded CLI output (Windows/macOS/Linux compatible)
- ✅ Built with modern C++17 and `std::filesystem`

---

## 🛠️ Getting Started

### 🔧 Prerequisites

- C++17 compatible compiler (`g++`, MSVC, Clang, etc.)
- CMake 3.10+
- A terminal that supports ANSI escape codes
- [nlohmann/json](https://github.com/nlohmann/json) (header-only)

### 📦 Installation

#### Option 1: Build with CMake

~~~bash
git clone https://github.com/Mareczech321/TaskForge.git
cd TaskForge
mkdir build && cd build
cmake ..
cmake --build .
~~~

#### Option 2: Compile Manually

~~~bash
g++ -std=c++17 -o taskforge src/*.cpp -Iinclude
~~~

---

## ⚙️ Usage

Launch the program:

~~~bash
./taskforge
~~~

Then use the interactive CLI to manage your tasks:

~~~bash
TaskForge >> help
TaskForge >> add
TaskForge >> list
TaskForge >> edit
TaskForge >> delete
TaskForge >> search
TaskForge >> quit
~~~

---

## 📁 Project Structure

~~~plaintext
/
├── include/
│   ├── TaskManager.h      ← Task manager class declarations
│   ├── colors.h           ← Terminal color functions
├── src/
│   ├── TaskManager.cpp    ← Core logic (add/edit/delete/search)
│   ├── commands.cpp       ← CLI parsing and command routing
├── main.cpp               ← CLI entry point
├── config.cfg             ← Path to task storage file (auto-generated)
├── tasks.json             ← JSON data store for tasks
├── CMakeLists.txt         ← CMake build configuration
├── README.md              ← Project documentation
~~~

---

## 🚧 Future Work

- 🔍 Advanced search filters (date ranges, tag logic)
- 🗂️ Support for multiple task folders/projects
- 🔔 Notifications or reminders
- 🖼️ GUI frontend using Qt or Electron (future milestone)
- 📦 Packaging for Linux and Windows (e.g., `.deb`, `.exe`, `brew`)

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository  
2. Create a new branch: `feature/your-feature`  
3. Make your changes and commit  
4. Open a Pull Request

---

## 📄 License

This project is licensed under the MIT License.  
See the [`LICENSE`](LICENSE) file for details.

---

## 📬 Contact

- GitHub: [@Mareczech321](https://github.com/Mareczech321)
- Issues & Suggestions: [Open a GitHub Issue](https://github.com/Mareczech321/TaskForge/issues)

---

Built with ❤️ in C++ for CLI productivity.
