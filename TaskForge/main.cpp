#include <iostream>
#include "./include/TaskManager.h"

int main() {

    TaskMNGR TaskManager;
    
    TaskManager.listTasks();
    TaskManager.editTask(1);
    TaskManager.addTask();
    TaskManager.deleteTask(2);

    return 0;
}