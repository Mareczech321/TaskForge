#include "../include/TaskManager.h"
#include "../include/Task.h"
#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <limits>

using json = nlohmann::json;
namespace fs = std::filesystem;

TaskMNGR::TaskMNGR() {
    
}

void TaskMNGR::addTask() {
    std::string fileName, folderPath, confirm, input, description, dueDate, tag;
    std::vector<std::string> tags;
    json jsonFile;
    int priority = 0;

    std::cout << "Is the file in the same folder as this .exe file? (Y/N):\n> ";
    std::getline(std::cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        std::cout << "Proceeding...\n";
        folderPath = fs::current_path().string();
    }
    else {
        std::cout << "Specify the path:\n> ";
        std::getline(std::cin, folderPath);
    }

    std::cout << "Enter the file name:\n> ";
    std::getline(std::cin, fileName);

    fs::path fullPath = fs::path(folderPath) / fileName;

    std::cout << "Is this the right file path?\n" << fullPath << " (Y/N):\n> ";
    std::getline(std::cin, confirm);
    if (confirm == "N" || confirm == "n") {
        std::cout << "Cancelling...\n";
        return;
    }

    if (!fs::exists(fullPath)) {
        std::cout << "File does not exist.\nCreating a new one!\n";
        std::fstream newFile(fileName, std::ios::out);
    }

    std::ifstream fileIn(fullPath);
    if (fileIn) {
        try {
            fileIn >> jsonFile;
        }
        catch (const json::parse_error& e) {
            std::cerr << "JSON parse error: " << e.what() << "\n";
            std::cerr << "Creating new empty JSON structure.\n";
            jsonFile["tasks"] = json::array();
        }
    }
    else {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }

    std::cout << "Enter description of new task:\n> ";
    std::getline(std::cin, description);

    std::cout << "Enter up to 3 tags (comma-separated):\n> ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    while (std::getline(iss, tag, ',')) {
        if (!tag.empty()) tags.push_back(tag);
        if (tags.size() == 3) break;
    }

    std::cout << "Enter due date of new task:\n> ";
    std::getline(std::cin, dueDate);

    std::cout << "Enter priority of new task (number):\n> ";
    while (!(std::cin >> priority)) {
        std::cout << "Invalid input. Enter a number:\n> ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

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
        std::cout << "Task added successfully.\n";
    }
    else {
        std::cerr << "Failed to write to file.\n";
    }
}

void TaskMNGR::listTasks() {
    json jsonFile;
    std::string folderPath, fileName, confirm;

    std::cout << "Is the file in the same folder as this .exe file? (Y/N):\n> ";
    std::getline(std::cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        std::cout << "Proceeding...\n";
        folderPath = fs::current_path().string();
    }
    else {
        std::cout << "Specify the path:\n> ";
        std::getline(std::cin, folderPath);
    }

    std::cout << "Enter the file name:\n> ";
    std::getline(std::cin, fileName);

    fs::path fullPath = fs::path(folderPath) / fileName;

    std::cout << "Is this the right file path?\n" << fullPath << " (Y/N):\n> ";
    std::getline(std::cin, confirm);
    if (confirm == "N" || confirm == "n") {
        std::cout << "Cancelling...\n";
        return;
    }
    
    std::ifstream fileIn(fullPath);

    if (fileIn) {
        try {
            fileIn >> jsonFile;
        }
        catch (const json::parse_error& e) {
            std::cerr << "Error parsing JSON: " << e.what() << "\n";
            return;
        }
    }
    else {
        std::cerr << "Could not open the file.\n";
        return;
    }

    if (!jsonFile.contains("tasks") || !jsonFile["tasks"].is_array()) {
        std::cout << "No tasks found.";
        return;
    }

    for (const auto& jsonTask : jsonFile["tasks"]) {
        Task task = Task::fromJson(jsonTask);

        std::cout << "ID: " << task.getId() << '\n';
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Due date: " << task.getDueDate() << "\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Tags: ";
        for (const auto& tag : task.getTags()) {
            std::cout << tag << " | ";
        }
        std::cout << "\n------------------------\n";
    }
}
