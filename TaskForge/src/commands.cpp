#define NOMINMAX

#include <iostream>
#include <sstream>
#include <vector>
#include "../include/colors.h"
#include "../include/TaskManager.h"

using namespace std;

string folderPath;

enum Controls {
	quit,
	add,
	ls,
	edit,
	del,
	locate,
	help,
	path,
	unknown
};

vector<string> splitInput(const string& input) {
	istringstream iss(input);
	vector<string> tokens;
	string token;

	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

Controls getCommand(const string& cmd) {
	if (cmd == "exit") return quit;
	if (cmd == "add") return add;
	if (cmd == "list") return ls;
	if (cmd == "edit") return edit;
	if (cmd == "del") return del;
	if (cmd == "search") return locate;
	if (cmd == "help") return help;
	if (cmd == "path") return path;
	return unknown;
}

void Commands() {
	string input;
	TaskMNGR TaskManager;

	do {
		cout << "TaskForge >> ";
		getline(cin, input);
		auto tokens = splitInput(input);

		if (tokens.empty()) {
			Color("No command entered.\n", "red");
			continue;
		}

		Controls command = getCommand(tokens[0]);

		switch (command) {
		case quit:
			Color("Exiting TaskForge...\n", "red");
			return;

		case help:
			Color("Available commands:\n", "bright_yellow");
			Color("  add    - Add a new task\n", "green");
			Color("  list   - List all tasks\n", "yellow");
			Color("  edit <id> - Edit a task by ID\n", "magenta");
			Color("  del <id>  - Delete a task by ID\n", "red");
			Color("  path <folder path / reset>   - Sets / resets the default file path for tasks\n", "blue");
			Color("  search <term | type (id, desc, due, priority, tag)> - Search for tasks\n", "cyan");
			Color("  exit   - Exit TaskForge\n", "bright_red");
			break;

		case add:
			Color("Adding a new task...\n", "green");
			TaskManager.addTask();
			break;

		case ls:
			Color("Listing all tasks...\n", "yellow");
			TaskManager.listTasks();
			break;

		case edit:
			if (tokens.size() < 2 || tokens.size() > 2) {
				Color("Usage: edit <id>\n", "red");
				break;
			}
			try {
				int id = stoi(tokens[1]);
				Color("Editing task ID: " + to_string(id) + "\n", "magenta");
				TaskManager.editTask(id);
			}
			catch (...) {
				Color("Invalid ID format.\n", "red");
			}
			break;	

		case del:
			if (tokens.size() < 2 || tokens.size() > 2) {
				Color("Please provide a task ID to delete.\n", "red");
				break;
			}
			try {
				TaskManager.deleteTask(stoi(tokens[1]));
			}
			catch (...) {
				Color("Invalid task ID format.\n", "red");
			}
			break;

		case locate:
			if (tokens.size() < 3 || tokens.size() > 3) {
				Color("Please provide a search term and type.\n", "red");
				break;
			}
			{
				Color("Searching for tasks matching: ", "cyan");
				cout << tokens[1] << endl;
				TaskManager.searchTasks(tokens[1], tokens[2]);
			}
			break;

		case path:
			if (tokens.size() > 2) {
				Color("Please provide a folder path.\n", "red");
				break;
			}
			else if (tokens.size() == 1) {
				ifstream configFile("config.cfg");
				if (configFile.is_open()) {
					getline(configFile, folderPath);
					configFile.close();
				}
				Color("Current folder path: ", "green");
				Color(folderPath, "bright_green");
				Color("\n", "green");
			}else if (tokens[1] == "reset") {
				TaskManager.resetFilePath();
			}
			else{
				Color("Setting folder path to: ", "green");
				Color(tokens[1], "bright_green");
				Color("\n", "green");
				TaskManager.saveFile(tokens[1]);
			}
			break;

		case unknown:
			Color("Invalid command. Type 'help' for a list of commands.\n", "red", true);
			break;
		}

	} while (getCommand(splitInput(input)[0]) != quit);
}