#include <iostream>
#include <string>
#include "InputHelper.h"

// メニュー入力
int InputHelper::inputMenu() {
	// 有効なindex値を返す
	return inputNumber(MENU_MAX, MENU_MAX);
}


// タスク名入力
std::string InputHelper::inputTitle() {
	std::string inputTitle;

	while (true) {
		// タスク名を入力から読み取る
		std::getline(std::cin, inputTitle);

		// 空であるか
		if (inputTitle.empty()) {
			std::cout << "空はNGです。再入力> ";

			// 入力やり直しへ
			continue;
		}

		// スペース以外をfalseとする
		bool hasNonSpace = false;

		// カンマではない場合をfalseとする
		bool hasComma = false;

		// 文字列を一文字ずつチェック
		for (char c : inputTitle) {
			if (c != ' ' && c != '\t') {
				// スペース以外を検出
				hasNonSpace = true;
			}

			if (c == ',') {
				// カンマを検出
				hasComma = true;
			}
		}

		// スペースのみの場合、再入力へ
		if (!hasNonSpace) {
			std::cout << "空白のみはNGです。再入力> ";

			// 入力やり直しへ
			continue;
		}

		// カンマを含む場合、再入力へ
		if (hasComma) {
			std::cout << "カンマを含む文字列はNGです。再入力> ";

			// 入力やり直しへ
			continue;
		}

		break;
	}

	// タスク名文字列を返す
	return inputTitle;
}


// index入力
size_t InputHelper::inputIndex(size_t maxIndex) {

	if (maxIndex == 0) {
		return 0;
	}

	// 有効なindex値を返す
	return static_cast<size_t>(inputNumber(0, static_cast<int>(maxIndex - 1)));
}


int InputHelper::inputNumber(int min, int max) {
	int input;

	while (true) {

		// 数値判定
		if (!(std::cin >> input)) {

			std::cin.clear();
			std::cin.ignore(IGNORE_MAX, '\n');

			std::cout
				<< "数値を入力してください。再入力> ";

			continue;
		}

		// バッファ破棄
		std::cin.ignore(IGNORE_MAX, '\n');

		// 範囲チェック
		if (input < min || input > max) {

			std::cout
				<< min
				<< "~"
				<< max
				<< "の数値を入力してください。再入力> ";

			continue;
		}

		// 有効なindex値を返す
		return input;
	}
}