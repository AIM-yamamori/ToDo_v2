#include "Task.h"

/*
* タスク1件を管理する。
*/


// コンストラクタ
Task::Task() {
    done = false;
}


// タスク名変更
void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}


// タスク名取得
const std::string Task::getTitle() const {
    // タスク名を返す
    return title;
}


// 完了状態切替
void Task::toggleDone() {
    // 完了状態を反転
    done = !done;
}


// 完了状態確認
bool Task::isDone() const {
    // 完了状態を返す
    return done;
}