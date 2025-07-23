#ifndef TASKMNGR_H
#define TASKMNGR_H

#include <vector>
#include "Task.h"

class TaskMNGR {
	public:
		TaskMNGR();

		void addTask();
		void editTask(int id);
		void deleteTask(int id);
		void listTasks();

	private:
		std::vector<Task> tasks;
};

#endif