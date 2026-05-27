#pragma once

#include "TaskManager.h"
#include "InputHelper.h"
#include "CsvManager.h"
#include "ConsoleView.h"

// csv 読み込み
void handleLoadTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
);

// csv 保存
void handleSaveTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
);

// タスク追加
void handleAddTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

// タスク削除
void handleRemoveTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

// 完了切り替え
void handleToggleTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

// タスク名変更
void handleEditTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

// タスク空チェック と 一覧表示
bool showTasksAndValidateNotEmpty(
	const TaskManager& manager,
	ConsoleView& view
);

// index入力 有効なindex値を返す
//size_t promptTaskIndex(
//	InputHelper& inputHelper,
//	size_t taskCount,
//	const std::string& message
//);

// タスク一覧表示
void showTaskList(
	const std::vector<Task>& tasks,
	ConsoleView& view
);

// タスク1件表示
void showSingleTask(
	ConsoleView& view,
	size_t index,
	const Task& task
);