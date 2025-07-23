#ifndef TASKMNGR_H
#define TASKMNGR_H

#include <vector>
#include "Task.h"

class TaskMNGR {
	public:
		TaskMNGR();

		void addTask();
		int editTask(int id);
		int deleteTask(int id);
		void listTasks();
		void loadTasksFromFile(const std::string& fullPath);

	private:
		std::vector<Task> tasks;
};

#endif