#pragma once

#include "Task.h"
#include <vector>

class ConsoleView {
public:
	// メニュー表示
	void showMenu();

	// タスク一覧表示
	void showTasks(const std::vector<Task>& tasks);

	// エラー表示
	void showError(const std::string& message);

	// 成功時表示
	void showSuccess(const std::string& message);

	// タスク1件表示
	void showTask(size_t index, const Task& task);

	// 並び変え方法メニュー表示
	void showSortMenu();
};