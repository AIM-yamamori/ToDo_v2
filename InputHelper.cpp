#include <iostream>
#include <string>
#include "InputHelper.h"
#include "Menu.h"
#include "Task.h"

// メニュー入力
Menu InputHelper::inputMenu() {
	// 有効なindex値を返す
	return static_cast<Menu>(inputNumber(MENU_MIN, MENU_MAX));
}

// タスク名入力
std::string InputHelper::inputTitle() {
	std::string title;

	while (true) {
		// タスク名を入力から読み取る
		std::getline(std::cin, title);

		// 空であるか
		if (title.empty()) {
			std::cout << "空はNGです。再入力> ";

			continue;
		}

		// スペースのみであるかチェック
		if (isBlankOnly(title)) {
			std::cout << "空白のみはNGです。再入力> ";

			continue;
		}

		// カンマを含むかチェック
		if (containsComma(title)) {
			std::cout << "カンマを含む文字列はNGです。再入力> ";

			continue;
		}

		// タスク名文字列を返す
		return title;
	}
}

// stringからカンマがあるかチェック
bool InputHelper::containsComma(const std::string& text) {
	// 文字列を一文字ずつチェック
	for (const char c : text) {
		if (c == ',') {
			// カンマを検出
			return true;
		}
	}

	return false;
}

// stringから空白・タブのみであるかチェック
bool InputHelper::isBlankOnly(const std::string& text) {
	// 文字列を一文字ずつチェック
	for (const char c : text) {
		if (c != ' ' && c != '\t') {
			// スペース以外がある
			return false;
		}
	}

	return true;
}

// index入力
size_t InputHelper::inputIndex(const size_t maxIndex) {
	// 最大値が0はNG
	if (maxIndex == 0) {
		return 0;
	}

	// 有効なindex値を返す
	return static_cast<size_t>(inputNumber(0, static_cast<int>(maxIndex - 1)));
}

// min～max の範囲内の整数が入力されるまで繰り返す
int InputHelper::inputNumber(
	const int min,
	const int max
) {
	int input;

	while (true) {
		// 数値として入力できたかチェック
		if (!(std::cin >> input)) {

			// エラー状態を解除
			std::cin.clear();

			// 不正入力をバッファから破棄
			std::cin.ignore(IGNORE_MAX, '\n');

			std::cout
				<< "数値を入力してください。再入力> ";

			continue;
		}

		// 入力後の余分な文字を破棄
		std::cin.ignore(IGNORE_MAX, '\n');

		// 指定範囲内かチェック
		if (input < min || input > max) {

			std::cout
				<< min
				<< "~"
				<< max
				<< "の数値を入力してください。再入力> ";

			continue;
		}

		// 条件を満たした数値を返す
		return input;
	}
}

// メッセージ表示後に有効なindexを入力
size_t InputHelper::promptIndex(
	size_t taskCount,
	const std::string& message
) {
	std::cout << message;

	return inputIndex(taskCount);
}

// 優先度入力
Priority InputHelper::inputPriority() {

	std::cout << "優先度を選択" << std::endl;
	std::cout << "0: LOW" << std::endl;
	std::cout << "1: MEDIUM" << std::endl;
	std::cout << "2: HIGH" << std::endl;
	std::cout << "> " << std::endl;

	// 0~2の間で入力
	const int input = inputNumber(0, 2);

	switch (input) {
	case 0:
		// 低
		return Priority::LOW;
	case 1:
		// 中
		return Priority::MEDIUM;
	case 2:
		// 高
		return Priority::HIGH;
	default:
		return Priority::MEDIUM;
	}
}