# 🚀 TaskForge Development Plan (3–4 Days)

---

## **Day 1 — Core Data Model & Storage**

### 🎯 Goals
- Design `Task` and `TaskManager` classes.
- Implement task CRUD: add, edit, delete, list.
- Support saving/loading tasks using a JSON file.

### ✅ Tasks
- **Define `Task` class with:**
  - `ID` (unique identifier)
  - `Description` (string)
  - `Tags` (vector of strings)
  - `Due date` (string or timestamp)
  - `Priority` (enum or int)

- **Define `TaskManager` class that:**
  - Stores tasks in a container (e.g., `std::vector<Task>`)
  - Provides methods to add, edit, delete, list tasks

- **Integrate `nlohmann/json` for:**
  - Serializing `Task` objects to JSON
  - Deserializing from JSON (e.g., `data/tasks.json`)

- **Write test in `main.cpp` to:**
  - Add tasks
  - Save and load from file
  - List tasks

---

## **Day 2 — Command Line Interface (CLI)**

### 🎯 Goals
- Parse user input to interact with tasks.
- Support CLI commands: `add`, `edit`, `delete`, `list`, `search`.
- Provide help text or usage guide.

### ✅ Tasks
- Design CLI input parser (simple or use `CLI11`).

- **Implement commands:**
  - `add` — create a new task (description, tags, due date, priority)
  - `list` — show all tasks in a readable format
  - `delete <id>` — remove a task
  - `edit <id>` — update task fields
  - `search <keyword|tag>` — filter tasks

- Add error handling for:
  - Invalid commands
  - Task not found

---

## **Day 3 — Advanced Features & Polishing**

### 🎯 Goals
- Export tasks to CSV or text.
- Implement sorting (e.g., by due date or priority).
- Improve CLI UX: formatting, validation, and confirmations.

### ✅ Tasks
- Add export functionality (`tasks.csv` or `.txt`)
- Add sorting options:
  - Example: `list --sort due_date`
- Improve CLI output:
  - Aligned columns, optional color formatting
- Add input validation
- Add confirmation prompts for deletes
- Write unit tests for core features
- Draft detailed `README.md` with usage examples

---

## **Day 4 (Optional) — Bonus Features & Deployment**

### 🎯 Goals
- Sync tasks via Dropbox/Google Drive (manual method).
- Add task reminders (e.g., console alerts).
- Package the app for easy distribution.

### ✅ Tasks
- Document syncing:
  - Point `tasks.json` to a synced folder
- Implement reminders:
  - Print alerts for overdue tasks on startup
- Create installation instructions or scripts:
  - Windows `.exe`, Linux binary
- Finalize and polish `README.md` for GitHub portfolio