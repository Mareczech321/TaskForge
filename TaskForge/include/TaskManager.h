#ifndef TASKMNGR_H
#define TASKMNGR_H

#include <vector>
#include "Task.h"
#include <tuple>
#include "../src/json.hpp"

class TaskMNGR {
	public:
		TaskMNGR();

		void addTask();
		int editTask(int id);
		int deleteTask(int id);
		void listTasks();
		std::tuple<std::vector<Task>, std::filesystem::path, nlohmann::json> loadFile();
    
	private:
		std::vector<Task> tasks;
};

#endif