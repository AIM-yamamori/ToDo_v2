#pragma once

#include "Task.h"
#include <vector>

class CsvManager {
public:
	bool saveTasks(const std::vector<Task>& tasks);

	bool loadTasks(std::vector<Task>& tasks);
};