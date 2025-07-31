#pragma once

#include <iostream>
#include <vector>
#include "Task.h"
#include <tuple>
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <string>

extern std::fstream gConfig;

class TaskMNGR {
	public:
		TaskMNGR();

		void addTask();
		int editTask(int id);
		int deleteTask(int id);
		void listTasks(std::string sort = "id", std::string order = "asc");
		std::tuple<std::vector<Task>, std::filesystem::path, nlohmann::json> loadFile(std::filesystem::path folderPath2 = std::filesystem::current_path());
		std::fstream saveFile(std::filesystem::path folderPath = std::filesystem::current_path());
		std::string getFolderPathFromConfig();
		bool isFileEmpty(const std::string& filename);
		std::fstream resetFilePath();
		void searchTasks(const std::string& searchTerm, std::string& type);

	private:
		std::vector<Task> tasks;
};