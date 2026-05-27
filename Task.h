#pragma once

#include <string>

class Task {
private:
    // タスク名
    std::string title;

    // 完了状態
    bool done;

public:
    // コンストラクタ
    Task();

    // タスク名変更
    void setTitle(const std::string& newTitle);

    // タスク名取得
    const std::string getTitle() const;

    // 完了状態切替
    void toggleDone();

    // 完了状態確認
    bool isDone() const;
};