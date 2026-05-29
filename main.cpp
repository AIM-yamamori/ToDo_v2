#include <iostream>
#include <windows.h>
#include <vector>
#include "Task.h"
#include "TaskManager.h"
#include "InputHelper.h"
#include "CsvManager.h"
#include "ConsoleView.h"
#include "TaskHandlers.h"
#include "Menu.h"

// メニュー
void runMenuLoop(
	TaskManager& manager,
	InputHelper& inputHelper,
	CsvManager& csvManager,
	ConsoleView& view
);

// UTF-8入出力 初期化
void initializeConsole();

// メイン
int main()
{
	// UTF-8入出力 初期化
	initializeConsole();

	// オブジェクト生成
	TaskManager manager;
	InputHelper inputHelper;
	CsvManager csvManager;
	ConsoleView view;

	// csvからタスクの読み込み
	handleLoadTasks(manager, csvManager, view);

	// メニューループ
	runMenuLoop(manager, inputHelper, csvManager, view);

	return 0;
}

// メニュー
void runMenuLoop(
	TaskManager& manager,
	InputHelper& inputHelper,
	CsvManager& csvManager,
	ConsoleView& view
) {
	while (true) {
		// メニュー表示
		view.showMenu();

		// メニュー番号を入力
		const Menu menuIndex = inputHelper.inputMenu();

		switch (menuIndex) {
		case Menu::EXIT: {
			// 保存して終了
			handleSaveTasks(manager, csvManager, view);

			view.showSuccess("終了します...");

			return;
		}
		case Menu::ADD_TASK: {
			// タスク追加
			handleAddTask(manager, inputHelper, view);

			break;
		}
		case Menu::SHOW_TASKS: {
			// 一覧表示
			showTaskList(manager.getTasks(), view);

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
		case Menu::SEARCH_TASK: {
			// タスク検索
			handleSearchTask(manager, inputHelper, view);

			break;
		}
		case Menu::SORT_TASKS: {
			// タスクソート

			break;
		}
		}
	}
}

// UTF-8入出力 初期化
void initializeConsole() {
	// 出力をUTF-8
	SetConsoleOutputCP(65001);
	// 入力もUTF-8
	SetConsoleCP(65001);
}