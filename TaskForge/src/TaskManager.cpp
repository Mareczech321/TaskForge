#define NOMINMAX

#include "../include/TaskManager.h"
#include "../include/Task.h"
#include "json.hpp"
#include "../include/colors.cpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <limits>
#include <tuple>

using json = nlohmann::json;
namespace fs = filesystem;

bool endsWith(const string& fullString, const string& ending);

TaskMNGR::TaskMNGR() {
    
}

void TaskMNGR::addTask() {
    string fileName, folderPath, confirm, input, description, dueDate, tag;
    vector<string> tags;
    int priority = 0;

    auto [tasks, fullPath, jsonFile] = loadFile();
    if (tasks.empty() || fullPath.empty()) {
        return;
    }

    if (!fs::exists(fullPath)) {
        Color("File does not exist.\nCreating a new one!\n", "red");
        fstream newFile(fileName, ios::out);
    }

    Color("Enter description of new task:\n> ", "bright_green");
    getline(cin, description);

    Color("Enter due date of new task:\n> ", "bright_green");
    getline(cin, dueDate);

    Color("Enter priority of new task (number):\n> ", "bright_green");
    while (!(cin >> priority)) {
        Color("Invalid input. Enter a number:\n> ", "red");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    Color("Enter up to 3 tags (comma-separated):\n> ", "bright_green");
    getline(cin, input);
    istringstream iss(input);
    while (getline(iss, tag, ',')) {
        if (!tag.empty()) tags.push_back(tag);
        if (tags.size() == 3) break;
    }

    int newId = 1;
    if (jsonFile.contains("tasks")) {
        for (const auto& item : jsonFile["tasks"]) {
            if (item.contains("id") && item["id"].is_number_integer()) {
                newId = max(newId, static_cast<int>(item["id"]) + 1);
            }
        }
    }

    Task task(newId, description);
    task.setTags(tags);
    task.setDueDate(dueDate);
    task.setPriority(priority);

    jsonFile["tasks"].push_back(task.toJson());

    ofstream fileOut(fullPath);
    if (fileOut) {
        fileOut << setw(4) << jsonFile << "\n";
        Color("Task added successfully.\n", "green");
    }
    else {
        Color("Failed to write to file.\n", "red", true);
    }
}

void TaskMNGR::listTasks() {
    string folderPath, fileName, confirm;

    auto [tasks, fullPath, jsonFile] = loadFile();
    if (tasks.empty() || fullPath.empty()) {
        return;
    }

    Color("------------------------\n", "yellow");
    for (const auto& jsonTask : jsonFile["tasks"]) {
        Task task = Task::fromJson(jsonTask);

        cout << "\033[31mID: \033[37m" << task.getId() << '\n';
        cout << "\033[35mDescription: \033[37m" << task.getDescription() << "\n";
        cout << "\033[35mDue date: \033[37m" << task.getDueDate() << "\n";
        cout << "\033[36mPriority: \033[37m" << task.getPriority() << "\n";
        cout << "\033[92mTags: ";
        for (const auto& tag : task.getTags()) {
            Color(tag, "white");
            Color(" | ", "red");
        }
        Color("\n------------------------\n", "yellow");
    }
}

int TaskMNGR::editTask(int id) {
    bool found = false;
    int temp = 0, temp2;
    string tempStr, tag, confirm, folderPath, fileName;
    vector<string> tags;

    auto [tasks, fullPath, jsonFile] = loadFile();
    if (tasks.empty() || fullPath.empty()) {
        return 1;
    }

    for (auto& task : tasks) {
        if (task.getId() == id) {
            Color("Task with ID ", "green");
            Color(id, "bright_green");
            Color(" found!\n", "green");
            found = true;

            while (temp < 1 || temp > 4) {
                Color("------------------------\n", "yellow");
                Color("What do you want to change?\n", "red");
                Color("[1] Description\n", "magenta");
                Color("[2] Due Date\n", "magenta");
                Color("[3] Priority\n", "cyan");
                Color("[4] Tags\n> ", "bright_green");
                cin >> temp;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch (temp) {
            case 1:
                Color("Enter new description:\n> ", "magenta");
                cin >> tempStr;
                task.setDescription(tempStr);
                break;
            case 2:
                Color("Enter new due date:\n> ", "magenta");
                getline(cin, tempStr);
                task.setDueDate(tempStr);
                break;
            case 3:
                Color("Enter new priority:\n> ", "cyan");
                cin >> temp2;
                task.setPriority(temp2);
                break;
            case 4:
                Color("Enter new tags:\n> ", "bright_green");
                getline(cin, tempStr);
                istringstream iss(tempStr);
                while (getline(iss, tag, ',')) {
                    if (!tag.empty()) tags.push_back(tag);
                    if (tags.size() == 3) break;
                }
                task.setTags(tags);
                break;
            }
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    jsonFile["tasks"] = json::array();
    for (const auto& task : tasks) {
        jsonFile["tasks"].push_back(task.toJson());
    }

    ofstream fileOut(fullPath);
    if (fileOut) {
        fileOut << setw(4) << jsonFile << "\n";
        Color("Task updated successfully.\n", "green");
        return 0;
    }
    else {
        Color("Failed to write changes to file.\n", "red");
        return 1;
    }
    
}

int TaskMNGR::deleteTask(int id) {
    auto [tasks, fullPath, jsonFile] = loadFile();
    if (tasks.empty() || fullPath.empty() || jsonFile.empty()) {
        return 1;
    }

    if (!jsonFile.contains("tasks") || !jsonFile["tasks"].is_array()) {
        Color("No tasks found in JSON.\n", "red");
        return 1;
    }

    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.getId() == id;
        });

    if (it == tasks.end()) {
        Color("Task with ID ", "red");
        Color(id, "bright_red");
        Color(" not found.\n", "red");
        return 1;
    }

    tasks.erase(it, tasks.end());
    Color("Task deleted successfully.\n", "green");
    
    jsonFile["tasks"].clear();
    for (const auto& task : tasks) {
        jsonFile["tasks"].push_back(task.toJson());
    }

    // Write the updated JSON back to the file
    std::ofstream fileOut(fullPath);
    if (fileOut) {
        fileOut << std::setw(4) << jsonFile << "\n";
        Color("File updated successfully.\n", "green");
    }
    else {
        Color("Failed to write changes to file.\n", "red");
        return 1;
    }

    return 0;
}

std::tuple<std::vector<Task>, std::filesystem::path, json> TaskMNGR::loadFile() {
    string confirm, folderPath, fileName;
    json jsonFile;
    vector<Task> tasks;

    Color("Is the file in the same folder as this .exe file? (Y/N):\n> ", "red");
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        Color("Proceeding...\n", "white");
        folderPath = fs::current_path().string();
    }
    else {
        Color("Specify the path:\n> ", "yellow");
        getline(cin, folderPath);
    }

    Color("Enter the file name:\n> ", "blue");
    getline(cin, fileName);
    if (!endsWith(fileName, ".json")) {
        fileName += ".json";
    }

    fs::path fullPath = fs::path(folderPath) / fileName;
    string path_string = fullPath.string();

    Color("Is this the right file path?\n", "bright_cyan");
    Color(path_string, "bright_blue");
    Color(" (Y/N):\n> ", "bright_cyan");
    getline(cin, confirm);

    if (confirm == "N" || confirm == "n") {
        Color("Cancelling...\n", "red");
        return {};
    }

    if (!fs::exists(fullPath)) {
        Color("File does not exist.\n", "red");
    }

    ifstream fileIn(fullPath);
    if (fileIn) {
        try {
            fileIn >> jsonFile;
        }
        catch (const json::parse_error& e) {
            Color("JSON parse error: ", "red", true);
            Color(e.what(), "red", true);
            Color("\n", "red", true);
        }
    }
    else {
        Color("Failed to open file.\n", "red", true);
        return {};
    }

    if (jsonFile.contains("tasks") && jsonFile["tasks"].is_array()) {
        for (const auto& jsonTask : jsonFile["tasks"]) {
            Task task = Task::fromJson(jsonTask);
            tasks.push_back(task);
        }
        
    }
    return {tasks, fullPath, jsonFile};
}

bool endsWith(const string& fullString, const string& ending){ //https://www.geeksforgeeks.org/cpp/check-if-string-ends-substring-in-cpp/
    if (ending.size() > fullString.size())
        return false;

    return fullString.compare(fullString.size()
        - ending.size(),
        ending.size(), ending)
        == 0;
}
