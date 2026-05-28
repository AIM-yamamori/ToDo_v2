#pragma once

#include <string>

enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

class Task {
private:
    // タスク名
    std::string title;

    // 完了状態
    bool done;

    // 優先度
    Priority priority;
    
public:
    // コンストラクタ
    Task(
        const std::string& title,
        Priority priority
    );

    // タスク名変更
    void setTitle(const std::string& newTitle);

    // タスク名取得
    const std::string getTitle() const;

    // 完了状態切替
    void toggleDone();

    // 完了状態確認
    bool isDone() const;

    // 優先度取得
    Priority getPriority() const;

    // 優先度を変更
    void setPriority(Priority priority);
};