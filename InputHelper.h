#pragma once

class InputHelper {
private:
	// メニュー番号　最小値
	static constexpr int MENU_MIN = 0;

	// メニュー番号　最大値
	static constexpr int MENU_MAX = 6;

	// cin.ignore() で破棄する最大文字数
	static constexpr int IGNORE_MAX = 10000;
public:
	// メニュー入力
	int inputMenu();

	// タスク名入力
	std::string inputTitle();

	// index入力
	size_t inputIndex(size_t maxIndex);

	// min~max内の有効なindexを入力から得る
	int inputNumber(int min, int max);
};