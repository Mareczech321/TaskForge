#pragma once

#ifndef TASKMNGR_H
#define TASKMNGR_H

#include <iostream>
#include <vector>
#include "Task.h"
#include <tuple>
#include "../src/json.hpp"
#include <filesystem>
#include <fstream>;

extern std::fstream gConfig;

class TaskMNGR {
	public:
		TaskMNGR();

		void addTask();
		int editTask(int id);
		int deleteTask(int id);
		void listTasks();
		std::tuple<std::vector<Task>, std::filesystem::path, nlohmann::json> loadFile(std::filesystem::path folderPath2 = std::filesystem::current_path());
		std::fstream saveFile(std::filesystem::path folderPath = std::filesystem::current_path());
		std::string getFolderPathFromConfig();
		bool isFileEmpty(const std::string& filename);
		std::fstream resetFilePath();

	private:
		std::vector<Task> tasks;
};

#endif