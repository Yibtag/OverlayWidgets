#pragma once

#include <Windows.h>
#include <vector>

#include "defines.h"

class Plugin {
private:
	HINSTANCE dll;

	typedef const char* (*getNameType)();
	typedef void (*onLoadType)(int, int);
	typedef void (*onUpdateType)();

	typedef std::vector<Rect> (*getRectsType)();
	typedef std::vector<Text> (*getTextsType)();
public:
	Plugin(std::string file, int width, int height);

	getNameType getName;
	onLoadType onLoad;
	onUpdateType onUpdate;
	getRectsType getRects;
	getTextsType getTexts;
};