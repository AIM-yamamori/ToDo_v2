#include "TaskManager.h"
#include "Task.h"
#include <iostream>

// タスク追加
void TaskManager::addTask(const std::string& title, Priority priority) {
	// title と priority を指定した Task を tasks に追加
	tasks.push_back(Task(title, priority));
}

// タスク削除
// 成功 true
// エラー false を返す
bool TaskManager::removeTask(size_t index) {
	// index範囲チェック
	if (!isValidIndex(index)) {
		// tasks空またはindex範囲外
		return false;
	}

	// 指定indexのタスクを削除
	tasks.erase(tasks.begin() + index);

	// 成功
	return true;
}

// タスク名変更
// 成功 true
// エラー false を返す
bool TaskManager::editTask(size_t index, const std::string& title) {
	// index範囲チェック
	if (!isValidIndex(index)) {
		// tasks空またはindex範囲外
		return false;
	}

	tasks[index].setTitle(title);

	// 成功
	return true;
}

// 完了状態変更
// 成功 true
// エラー false を返す
bool TaskManager::toggleTask(size_t index) {
	// index範囲チェック
	if (!isValidIndex(index)) {
		// tasks空またはindex範囲外
		return false;
	}

	// 完了状態を反転
	tasks[index].toggleDone();

	// 成功
	return true;
}

// tasks空判定
bool TaskManager::isEmpty() const {
	if (tasks.empty()) {
		// 空
		return true;
	}
	else {
		// 空ではない
		return false;
	}
}

// tasksサイズ確認
size_t TaskManager::getTaskCount() const {
	// サイズを返す
	return tasks.size();
}

// tasksを外部へ渡す 読み込み専用
const std::vector<Task>& TaskManager::getTasks() const {
	return tasks;
}

// tasksを外部へ渡す 変更可能
std::vector<Task>& TaskManager::getTasks() {
	return tasks;
}

// index範囲チェック
bool TaskManager::isValidIndex(size_t index) const {
	// 空またはindex範囲外か
	if (tasks.size() <= index) {
		return false;
	}

	return true;
}