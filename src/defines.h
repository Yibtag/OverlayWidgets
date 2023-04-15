#pragma once

#include <string>

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

