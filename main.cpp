#include <iostream>
#include <windows.h>
#include "TaskManager.h"
#include "InputHelper.h"
#include "CsvManager.h"
#include "ConsoleView.h"

// メニュー番号
enum class Menu {
	EXIT = 0,
	ADD_TASK,
	SHOW_TASKS,
	REMOVE_TASK,
	TOGGLE_TASK,
	EDIT_TASK,
	SAVE_TASKS
};

void handleLoadTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
);

void handleSaveTasks(
	TaskManager& manager,
	CsvManager& csvManager,
	ConsoleView& view
);

void handleAddTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

void handleRemoveTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

void handleToggleTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

void handleEditTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
);

bool prepareTaskOperation(
	TaskManager& manager,
	ConsoleView& view
);

size_t promptTaskIndex(
	InputHelper& inputHelper,
	size_t taskCount,
	const std::string& message
);

int main()
{
	// 出力をUTF-8
	SetConsoleOutputCP(65001);
	// 入力もUTF-8
	SetConsoleCP(65001);

	// オブジェクト生成
	TaskManager manager;
	InputHelper inputHelper;
	CsvManager csvManager;
	ConsoleView view;

	// csvからタスクの読み込み
	

	// メニューループ
	while (true) {
		// メニュー表示
		view.showMenu();
		
		// メニュー番号を入力
		Menu menuIndex = static_cast<Menu>(inputHelper.inputMenu());

		switch (menuIndex) {
			case Menu::EXIT: {
				// 保存して終了
				handleSaveTasks(manager, csvManager, view);

				view.showSuccess("終了します...");

				return 0;
			}
			case Menu::ADD_TASK: {
				// タスク追加
				handleAddTask(manager, inputHelper, view);

				break;
			}
			case Menu::SHOW_TASKS: {
				// 一覧表示
				view.showTasks(manager.getTasks());

				break;
			}
			case Menu::REMOVE_TASK: {
				// タスク削除
				handleRemoveTask(manager, inputHelper, view);

				break;
			}
			case Menu::TOGGLE_TASK: {
				// 完了状態切り替え
				handleToggleTask(manager, inputHelper, view);

				break;
			}
			case Menu::EDIT_TASK: {
				// タスク名変更
				handleEditTask(manager, inputHelper, view);

				break;
			}
			case Menu::SAVE_TASKS: { // csv保存のみ
				// csv保存実行
				handleSaveTasks(manager, csvManager, view);

				break;
			}
			default: {
				// 範囲外
				view.showError("範囲内の数値を入力");

				break;
			}
		}
	}

	return 0;
}

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
		view.showTasks(manager.getTasks());
	}
	else {
		// 失敗時
		view.showError("csvからタスクを読み込めませんでした");
	}
}

// 0: 保存
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

// 1: タスク追加
void handleAddTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	std::cout << "追加するタスク名を入力> ";

	// タスク追加実行
	manager.addTask(inputHelper.inputTitle());

	// 成功メッセージ
	view.showSuccess("以下のタスクを追加しました");

	// 追加したタスクのインデックス取得
	size_t index = manager.getTaskCount() - 1;

	// 追加したタスク1件表示
	view.showTask(index, manager.getTasks()[index]);
}

// 3: タスク削除
void handleRemoveTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!prepareTaskOperation(manager, view)) {
		return;
	}

	while (true) {
		// index入力
		size_t index =
			promptTaskIndex(
				inputHelper,
				manager.getTaskCount(),
				"削除するindexを入力> "
			);

		// 削除前にタスク保持
		Task removedTask = manager.getTasks()[index];

		if (manager.removeTask(index)) {
			// 成功
			view.showSuccess("削除しました");

			// 削除したタスク1件表示
			view.showTask(index, removedTask);

			break;
		}
		else {
			// 失敗
			view.showError("削除失敗");
		}
	}

	// 一覧再表示
	view.showTasks(manager.getTasks());
}

// 4: 完了切り替え
void handleToggleTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!prepareTaskOperation(manager, view)) {
		return;
	}

	while (true) {
		// index入力
		size_t index =
			promptTaskIndex(
				inputHelper,
				manager.getTaskCount(),
				"完了切り替えするタスクのindex番号を入力> "
			);

		// 完了切り替え実行
		if (manager.toggleTask(index)) {
			// 成功メッセージ
			view.showSuccess("完了状態を以下に変更しました");

			// 完了切り替えしたタスク1件表示
			view.showTask(index, manager.getTasks()[index]);

			break;
		}
		else {
			// 失敗
			view.showError("完了状態の変更失敗");
		}
	}

	// 一覧再表示
	view.showTasks(manager.getTasks());
}

// 5: タスク名変更
void handleEditTask(
	TaskManager& manager,
	InputHelper& inputHelper,
	ConsoleView& view
) {
	// タスク空チェック と 一覧表示
	if (!prepareTaskOperation(manager, view)) {
		return;
	}

	while (true) {
		// index入力
		size_t index =
			promptTaskIndex(
				inputHelper,
				manager.getTaskCount(),
				"編集するタスクのindex番号を入力> "
			);

		std::cout << "新しいタスク名を入力> ";

		// 新しいタスク名入力
		std::string newTitle =
			inputHelper.inputTitle();

		// タスク名変更
		if (manager.editTask(index, newTitle)) {
			// 成功メッセージ
			view.showSuccess("以下のタスク名に変更しました");

			// 変更後タスク表示
			view.showTask(index, manager.getTasks()[index]);

			break;
		}
		else {
			// 失敗時
			view.showError("タスク名変更失敗");
		}
	}

	// 一覧再表示
	view.showTasks(manager.getTasks());
}

// タスク空チェック と 一覧表示
bool prepareTaskOperation(
	TaskManager& manager,
	ConsoleView& view
) {
	// 一覧表示
	view.showTasks(manager.getTasks());

	// タスク空チェック
	if (manager.isEmpty()) {
		view.showError("タスクがありません");
		return false;
	}

	return true;
}

size_t promptTaskIndex(
	InputHelper& inputHelper,
	size_t taskCount,
	const std::string& message
) {
	std::cout << message;

	return inputHelper.inputIndex(taskCount);
}