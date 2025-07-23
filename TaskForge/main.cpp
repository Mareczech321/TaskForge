#include <iostream>
#include "./include/TaskManager.h"

int main() {

    TaskMNGR TaskManager;
    
    TaskManager.listTasks();
    std::cout << TaskManager.editTask(2);
    TaskManager.addTask();

    return 0;
}