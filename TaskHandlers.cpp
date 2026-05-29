#include "TaskHandlers.h"
#include <iostream>

// csv 読み込み
void handleLoadTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
) {
	if (csvManager.loadTasks(manager.getTasks())) {
		// 成功時
		view.showSuccess("csvからタスクを読み込みました");

		// タスク一覧表示
		showTaskList(manager.getTasks(), view);
	}
	else {
		// 失敗時
		view.showError("csvからタスクを読み込めませんでした");
	}
}

// csv 保存
void handleSaveTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
) {
	// csv保存実行
	if (csvManager.saveTasks(manager.getTasks())) {
		// 成功時
		view.showSuccess("csvにタスクを保存しました");
	}
	else {
		// 失敗時
		view.showError("csvにタスクを保存できませんでした");
	}


}

// タスク追加
void handleAddTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	std::cout << "追加するタスク名を入力> ";

	// タスク追加実行
	const std::string title =
		inputHelper.inputTitle();

	const Priority priority =
		inputHelper.inputPriority();

	manager.addTask(title, priority);

	// 成功メッセージ
	view.showSuccess("以下のタスクを追加しました");

	// 追加したタスクのインデックス取得
	const size_t index = manager.getTaskCount() - 1;

	// 追加したタスク1件表示
	showSingleTask(view, index, manager.getTasks()[index]);
}

// タスク削除
void handleRemoveTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!showTasksAndValidateNotEmpty(manager, view)) {
		return;
	}

	// index入力
	const size_t index = 
		inputHelper.promptIndex(
			manager.getTaskCount(), 
			"削除するindexを入力> "
		);

	// 削除前にタスク保持
	const Task removedTask = manager.getTasks()[index];

	// タスク削除
	manager.removeTask(index);

	// 成功表示
	view.showSuccess("削除しました");

	// 削除したタスク表示
	view.showTask(index, removedTask);

	// 一覧再表示
	showTaskList(manager.getTasks(), view);
}

// 完了切り替え
void handleToggleTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!showTasksAndValidateNotEmpty(manager, view)) {
		return;
	}

	// index入力
	const size_t index =
		inputHelper.promptIndex(
			manager.getTaskCount(),
			"完了切り替えするタスクのindex番号を入力> "
		);

	// 完了切り替え実行
	manager.toggleTask(index);

	// 成功メッセージ
	view.showSuccess("完了状態を以下に変更しました");

	// 完了切り替えしたタスク1件表示
	showSingleTask(view, index, manager.getTasks()[index]);

	// 一覧再表示
	showTaskList(manager.getTasks(), view);
}

// タスク名変更
void handleEditTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!showTasksAndValidateNotEmpty(manager, view)) {
		return;
	}

	// index入力
	const size_t index =
		inputHelper.promptIndex(
			manager.getTaskCount(),
			"編集するタスクのindex番号を入力> "
		);

	std::cout << "新しいタスク名を入力> ";

	// 新しいタスク名入力
	const std::string newTitle =
		inputHelper.inputTitle();

	// タスク名変更
	manager.editTask(index, newTitle);

	// 成功メッセージ
	view.showSuccess("以下のタスク名に変更しました");

	// 変更後タスク表示
	showSingleTask(view, index, manager.getTasks()[index]);

	// 一覧再表示
	showTaskList(manager.getTasks(), view);
}

// タスク空チェック と 一覧表示
bool showTasksAndValidateNotEmpty(
	const TaskManager& manager,
	ConsoleView& view
) {
	// 一覧表示
	showTaskList(manager.getTasks(), view);

	// タスク空チェック
	if (manager.isEmpty()) {
		view.showError("タスクがありません");
		return false;
	}

	return true;
}

// index入力 有効なindex値を返す
//size_t promptTaskIndex(
//	InputHelper& inputHelper,
//	size_t taskCount,
//	const std::string& message
//) {
//	std::cout << message;
//
//	return inputHelper.inputIndex(taskCount);
//}

// タスク一覧表示
void showTaskList(
	const std::vector<Task>& tasks,
	ConsoleView& view
) {
	// 一覧表示
	view.showTasks(tasks);
}

// タスク1件表示
void showSingleTask(
	ConsoleView& view,
	size_t index,
	const Task& task
) {
	view.showTask(index, task);
}

// タスク検索
void handleSearchTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	std::cout << "検索文字列を入力> ";

	// 検索キーワード入力
	const std::string keyword =
		inputHelper.inputTitle();

	// 検索を実行
	const std::vector<Task> results = manager.searchTasks(keyword);

	// 検索結果が0件の場合
	if (results.empty()) {
		view.showError("該当タスクなし");
		return;
	}

	// 成功メッセージ
	view.showSuccess("検索結果は以下の通りです");

	// 検索結果表示
	view.showTasks(results);
}

// 優先度順でソート
void handleSortTasks(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// 並び変え方法メニュー表示
	view.showSortMenu();

	// 並び変え方法を選択
	const int sortNumber =
		inputHelper.inputNumber(1, 3);

	SortType sortType;

	switch (sortNumber) {
		case 1:
			// 優先度順
			sortType = SortType::PRIORITY;

			break;
		case 2:
			// タスク名順
			sortType = SortType::TITLE;

			break;
		case 3:
			// 完了状態順
			sortType = SortType::DONE;

			break;
	}

	// sortTypeに応じて並び変え実行
	manager.sortTasks(sortType);

	view.showSuccess("タスクを並び替えました");
	
	// ソート結果一覧表示
	view.showTasks(manager.getTasks());
}