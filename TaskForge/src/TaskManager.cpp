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

using json = nlohmann::json;
namespace fs = filesystem;

bool endsWith(const string& fullString, const string& ending);

TaskMNGR::TaskMNGR() {
    
}

void TaskMNGR::addTask() {
    string fileName, folderPath, confirm, input, description, dueDate, tag;
    vector<string> tags;
    json jsonFile;
    int priority = 0;

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
    Color(" (Y/N):\n> ","bright_cyan");
    getline(cin, confirm);

    if (confirm == "N" || confirm == "n") {
        Color("Cancelling...\n", "red");
        return;
    }

    if (!fs::exists(fullPath)) {
        Color("File does not exist.\nCreating a new one!\n", "red");
        fstream newFile(fileName, ios::out);
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
            Color("Creating new empty JSON structure.\n", "red", true);
            jsonFile["tasks"] = json::array();
        }
    }
    else {
        Color("Failed to open file for reading.\n", "red", true);
        return;
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
    json jsonFile;
    string folderPath, fileName, confirm;

    Color("Is the file in the same folder as this .exe file? (Y/N):\n> ", "magenta");
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        Color("Proceeding...\n", "cyan");
        folderPath = fs::current_path().string();
    }
    else {
        Color("Specify the path:\n> ", "red");
        getline(cin, folderPath);
    }

    Color("Enter the file name:\n> ", "bright_green");
    getline(cin, fileName);
    if (!endsWith(fileName, ".json")) {
        fileName += ".json";
    }

    fs::path fullPath = fs::path(folderPath) / fileName;
    string path_string = fullPath.string();

    Color("Is this the right file path?\n", "yellow");
    Color(path_string, "bright_yellow"); 
    Color("\n(Y/N):\n> ", "yellow");
    getline(cin, confirm);
    if (confirm == "N" || confirm == "n") {
        Color("Cancelling...\n", "red");
        return;
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
            return;
        }
    }
    else {
        Color("Could not open the file.\n", "red", true);
        return;
    }

    if (!jsonFile.contains("tasks") || !jsonFile["tasks"].is_array()) {
        Color("No tasks found.", "red");
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
    json jsonFile;
    vector<string> tags;

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
        return 1;
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
        Color("Failed to open file for writing.\n", "red", true);
        return 1;
    }

    if (jsonFile.contains("tasks") && jsonFile["tasks"].is_array()) {
        for (const auto& jsonTask : jsonFile["tasks"]) {
            Task task = Task::fromJson(jsonTask);
            tasks.push_back(task);
        }
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

bool endsWith(const string& fullString, const string& ending){ //https://www.geeksforgeeks.org/cpp/check-if-string-ends-substring-in-cpp/
    if (ending.size() > fullString.size())
        return false;

    return fullString.compare(fullString.size()
        - ending.size(),
        ending.size(), ending)
        == 0;
}
