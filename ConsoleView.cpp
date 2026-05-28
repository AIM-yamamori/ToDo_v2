#include "ConsoleView.h"
#include "PriorityUtils.h"
#include <iostream>
#include <vector>

// メニュー表示
void ConsoleView::showMenu() {
	std::cout << "メニューを以下から選択" << std::endl;
	std::cout << "0: 保存して終了" << std::endl;
	std::cout << "1: タスク追加" << std::endl;
	std::cout << "2: 一覧表示" << std::endl;
	std::cout << "3: タスク削除" << std::endl;
	std::cout << "4: 完了状態切り替え" << std::endl;
	std::cout << "5: タスク名編集" << std::endl;
	std::cout << "6: csvに保存" << std::endl;
	std::cout << ">";
}

// タスク一覧表示
void ConsoleView::showTasks(const std::vector<Task>& tasks) {
	// tasksが空である場合
	if (tasks.empty()) {
		std::cout << "タスクが空です" << std::endl;
		return;
	}

	std::cout << "--- タスク一覧 (" << tasks.size() << "件) ---" << std::endl;

	// 全タスクを表示
	for (size_t i = 0; i < tasks.size(); i++) {
		showTask(i, tasks[i]);
	}

	std::cout << "------------------------" << std::endl;
}

// エラー表示
void ConsoleView::showError( const std::string& message) {
	std::cout << "[ERROR] " << message << std::endl;
}

// 成功時表示
void ConsoleView::showSuccess(const std::string& message) {
	std::cout << "[SUCCESS] " << message << std::endl;
}

// タスク1件表示
void ConsoleView::showTask(size_t index, const Task& task) {
	// 優先度を取得しテキスト形式に
	const std::string priorityText =
		PriorityUtils::toString(task.getPriority());

	std::cout 
		<< index 
		<< ":"
		<< " "
		<< (task.isDone() ? "[x]" : "[ ]")
		<< " "
		<< "["
		<< priorityText 
		<< "]" 
		<< " "
		<< task.getTitle() 
		<< std::endl;
}
