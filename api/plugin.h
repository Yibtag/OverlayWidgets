#pragma once

#include <Windows.h>

#include <vector>

namespace Plugin {
	typedef struct Rect {
		int id;
		int x;
		int y;
		int width;
		int height;
		int r;
		int g;
		int b;
		int a;
	} Rect;

	typedef struct Text {
		int id;
		const char* content;
		int x;
		int y;
		int r;
		int g;
		int b;
		int a;
	} Text;

	std::vector<Rect> rects;

	int getRectIndex(int id) {
		auto it = std::find_if(rects.begin(), rects.end(), [&id](const Rect tmp) { return tmp.id == id; });

		if (it != rects.end()) {
			return std::distance(rects.begin(), it);
		}

		return -1;
	}

	void addRect(int id, int x, int y, int width, int height, int r, int g, int b, int a) {
		rects.push_back({ id, x, y, width, height, r, g, b, a });
	}

	bool removeRect(int id) {
		int index = getRectIndex(id);
		if (index == -1) return false;

		rects.erase(rects.begin() + index);
		return true;
	}

	std::vector<Text> texts;

	int getTextIndex(int id) {
		auto it = std::find_if(texts.begin(), texts.end(), [&id](const Text tmp) { return tmp.id == id; });

		if (it != texts.end()) {
			return std::distance(texts.begin(), it);
		}

		return -1;
	}

	void addText(int id, char* content, int x, int y, int r, int g, int b, int a) {
		texts.push_back({ id, content, x, y, r, g, b, a });
	}

	bool removeText(int id) {
		int index = getTextIndex(id);
		if (index == -1) return false;

		texts.erase(texts.begin() + index);
		return true;
	}

	extern "C" {
		__declspec(dllexport) const char* getName();
		// width and height of the screen
		__declspec(dllexport) void onLoad(int width, int height);
		__declspec(dllexport) void onUpdate();

		__declspec(dllexport) std::vector<Rect> getRects() {
			return rects;
		}

		__declspec(dllexport) std::vector<Text> getTexts() {
			return texts;
		}
	}
}
