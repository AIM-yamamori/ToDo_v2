#pragma once

#include "Menu.h"
#include "Task.h"

class InputHelper {
private:
	// メニュー番号　最小値
	static constexpr int MENU_MIN = 0;

	// メニュー番号　最大値
	static constexpr int MENU_MAX = 8;

	// cin.ignore() で破棄する最大文字数
	static constexpr int IGNORE_MAX = 10000;
public:
	// メニュー入力
	Menu inputMenu();

	// stringからカンマがあるかチェック
	bool containsComma(const std::string& text);

	// stringから空白・タブのみであるかチェック
	bool isBlankOnly(const std::string& text);

	// タスク名入力
	std::string inputTitle();

	// index入力
	size_t inputIndex(size_t maxIndex);

	// min~max内の有効なindexを入力から得る
	int inputNumber(const int min, const int max);

	// メッセージ表示後に有効なindexを入力
	size_t promptIndex(
		size_t taskCount,
		const std::string& message
	);

	// 優先度入力
	Priority inputPriority();
};