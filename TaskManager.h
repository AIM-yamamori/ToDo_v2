#pragma once

#include "Task.h"
#include <vector>

// タスクの並び変え方法
enum class SortType {
	PRIORITY, // 優先度順
	TITLE, // タスク名順
	DONE // 完了状態順
};

class TaskManager {
private:
	// タスク管理配列
	std::vector<Task> tasks;

public:
	// タスク追加
	void addTask(const std::string& title, Priority priority);

	// タスク削除
	bool removeTask(size_t index);

	// タスク名変更
	bool editTask(size_t index, const std::string& title);

	// 完了状態変更
	bool toggleTask(size_t index);

	// tasks空判定
	bool isEmpty() const;

	// tasksサイズ確認
	size_t getTaskCount() const;

	// tasksを外部へ渡す 読み取り専用
	const std::vector<Task>& getTasks() const;

	// tasksを外部へ渡す 変更可能
	std::vector<Task>& getTasks();

	// index範囲チェック
	bool isValidIndex(size_t index) const;

	// タスク名にキーワードを含むタスクを検索
	std::vector<Task> searchTasks(const std::string& keyword) const;

	// 指定された条件でタスクを並び替え
	void sortTasks(SortType type);
};
