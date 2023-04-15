#pragma once

#include <Windows.h>
#include <vector>

#include "plugin.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Window {
private:
	bool taskbar = true;

	WNDCLASSEXW window_class;
	void getScreenResolution();

	IDirect3D9Ex* object = NULL;
	IDirect3DDevice9Ex* device = NULL;
	D3DPRESENT_PARAMETERS params;
	ID3DXFont* font = 0;

	void draw_rect(int x, int y, int width, int height, int r, int g, int b, int a);
	void draw_text(const char* content, int x, int y, int r, int g, int b, int a);
public:
	HWND window;
	int width, height;
	bool init(HINSTANCE instance, WNDPROC window_process, const char* window_name);
	void render(std::vector<Plugin> plugins);
};