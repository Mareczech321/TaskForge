#include <iostream>
#include "./include/TaskManager.h"

int main() {

    TaskMNGR TaskManager;
    
    TaskManager.listTasks();
    TaskManager.editTask(10);
    TaskManager.addTask();

    return 0;
}