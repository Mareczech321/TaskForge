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
namespace fs = std::filesystem;

bool endsWith(const std::string& fullString, const std::string& ending);

TaskMNGR::TaskMNGR() {
    
}

void TaskMNGR::addTask() {
    std::string fileName, folderPath, confirm, input, description, dueDate, tag;
    std::vector<std::string> tags;
    json jsonFile;
    int priority = 0;

    Color("Is the file in the same folder as this .exe file? (Y/N):\n> ", "red");
    std::getline(std::cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        Color("Proceeding...\n", "white");
        folderPath = fs::current_path().string();
    }
    else {
        Color("Specify the path:\n> ", "yellow");
        std::getline(std::cin, folderPath);
    }

    Color("Enter the file name:\n> ", "blue");
    std::getline(std::cin, fileName);
    if (!endsWith(fileName, ".json")) {
        fileName += ".json";
    }

    fs::path fullPath = fs::path(folderPath) / fileName;
    std::string path_string = fullPath.string();

    Color("Is this the right file path?\n", "bright_cyan");
    Color(path_string, "bright_blue");
    Color(" (Y/N):\n> ","bright_cyan");
    std::getline(std::cin, confirm);

    if (confirm == "N" || confirm == "n") {
        Color("Cancelling...\n", "red");
        return;
    }

    if (!fs::exists(fullPath)) {
        Color("File does not exist.\nCreating a new one!\n", "red");
        std::fstream newFile(fileName, std::ios::out);
    }

    std::ifstream fileIn(fullPath);
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
    std::getline(std::cin, description);

    Color("Enter due date of new task:\n> ", "bright_green");
    std::getline(std::cin, dueDate);

    Color("Enter priority of new task (number):\n> ", "bright_green");
    while (!(std::cin >> priority)) {
        Color("Invalid input. Enter a number:\n> ", "red");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

    Color("Enter up to 3 tags (comma-separated):\n> ", "bright_green");
    std::getline(std::cin, input);
    std::istringstream iss(input);
    while (std::getline(iss, tag, ',')) {
        if (!tag.empty()) tags.push_back(tag);
        if (tags.size() == 3) break;
    }

    int newId = 1;
    if (jsonFile.contains("tasks")) {
        for (const auto& item : jsonFile["tasks"]) {
            if (item.contains("id") && item["id"].is_number_integer()) {
                newId = std::max(newId, static_cast<int>(item["id"]) + 1);
            }
        }
    }

    Task task(newId, description);
    task.setTags(tags);
    task.setDueDate(dueDate);
    task.setPriority(priority);

    jsonFile["tasks"].push_back(task.toJson());

    std::ofstream fileOut(fullPath);
    if (fileOut) {
        fileOut << std::setw(4) << jsonFile << "\n";
        Color("Task added successfully.\n", "green");
    }
    else {
        Color("Failed to write to file.\n", "red", true);
    }
}

void TaskMNGR::listTasks() {
    json jsonFile;
    std::string folderPath, fileName, confirm;

    Color("Is the file in the same folder as this .exe file? (Y/N):\n> ", "magenta");
    std::getline(std::cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        Color("Proceeding...\n", "cyan");
        folderPath = fs::current_path().string();
    }
    else {
        Color("Specify the path:\n> ", "red");
        std::getline(std::cin, folderPath);
    }

    Color("Enter the file name:\n> ", "bright_green");
    std::getline(std::cin, fileName);
    if (!endsWith(fileName, ".json")) {
        fileName += ".json";
    }

    fs::path fullPath = fs::path(folderPath) / fileName;
    std::string path_string = fullPath.string();

    Color("Is this the right file path?\n", "yellow");
    Color(path_string, "bright_yellow"); 
    Color("\n(Y/N):\n> ", "yellow");
    std::getline(std::cin, confirm);
    if (confirm == "N" || confirm == "n") {
        Color("Cancelling...\n", "red");
        return;
    }
    
    std::ifstream fileIn(fullPath);

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

        std::cout << "\033[31mID: \033[37m" << task.getId() << '\n';
        std::cout << "\033[35mDescription: \033[37m" << task.getDescription() << "\n";
        std::cout << "\033[35mDue date: \033[37m" << task.getDueDate() << "\n";
        std::cout << "\033[36mPriority: \033[37m" << task.getPriority() << "\n";
        std::cout << "\033[92mTags: ";
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
    string tempStr, tag;
    std::vector<std::string> tags;

    for (auto task : tasks) {
        cout << task.getId();
        if (task.getId() == id && !found) {
            Color("Task with ID ", "green");
            Color(id, "bright_green");
            Color(" found!\n", "green");
            found = true;

            while (temp < 1 || temp > 5) {
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
                Color("Enter new description:\n>", "magenta");
                getline(cin, tempStr);
                task.setDescription(tempStr);
                break;
            case 2:
                Color("Enter new due date:\n>", "magenta");
                getline(cin, tempStr);
                task.setDueDate(tempStr);
                break;
            case 3:
                Color("Enter new priority:\n>", "cyan");
                cin >> temp2;
                task.setPriority(temp2);
                break;
            case 4:
                getline(cin, tempStr);
                istringstream iss(tempStr);
                while (getline(iss, tag, ',')) {
                    if (!tag.empty()) tags.push_back(tag);
                    if (tags.size() == 3) break;
                }
                task.setTags(tags);
                return 0;
            }
        }
        else if (found) {
            return 1;
        }
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