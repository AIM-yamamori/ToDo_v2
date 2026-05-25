#include "CsvManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// CSVへタスクを書き込み
// 成功 true
// 失敗 false を返す
bool CsvManager::saveTasks(const std::vector<Task>& tasks) {
	// 書き込みモードでcsvファイルを開く
	std::ofstream file("tasks.csv");

	// 正常に開けなかった場合
	if (!file.is_open()) {
        // 失敗時
		return false;
	}

	// タスクすべてを一行ずつcsvに書き込む
	for (size_t i = 0; i < tasks.size(); ++i) {
		file << (tasks[i].isDone() ? 1 : 0) << "," << tasks[i].getTitle() << "\n";
	}

	// ファイルを閉じる
	file.close();

    // 成功時
	return true;
}

// CSVからタスクを読み込み
// 成功 true
// 失敗 false を返す
bool CsvManager::loadTasks(std::vector<Task>& tasks) {
    // 読み込みモードでcsvファイルを開く
    std::ifstream file("tasks.csv");

    // 正常に開けなかった場合
    if (!file.is_open()) {
        // 失敗時
        return false;
    }

    // 読み込み前にクリア
    tasks.clear();

    std::string line;

    // 1行ずつ読み込む
    while (std::getline(file, line)) {

        std::stringstream ss(line);

        std::string doneStr;
        std::string title;

        // カンマ区切りで取得
        if (!std::getline(ss, doneStr, ',')) {
            std::getline(ss, doneStr, ',');
            continue;
        }

        if (!std::getline(ss, title)) {
            std::getline(ss, title);
            continue;
        }

        // done 0,1 以外をエラーとする
        if (doneStr != "0" && doneStr != "1") {
            continue;
        }

        // titleの空をエラーとする
        if (title.empty()) {
            continue;
        }

        // Task生成
        Task task;

        // タスク名設定
        task.setTitle(title);

        // 完了状態設定
        if (doneStr == "1") {
            task.toggleDone();
        }

        // tasksへ追加
        tasks.push_back(task);
    }

    // ファイルを閉じる
    file.close();

    // 成功時
    return true;
}