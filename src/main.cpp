#include <iostream>
#include <filesystem>

#include "defines.h"
#include "plugin.h"
#include "window.h"

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wide_param, LPARAM long_param);

Window window = Window();
std::vector<Plugin> plugins;

bool hasSubfix(std::string file, const char* subfix) {
	if (file.substr(file.find_last_of(".") + 1) == subfix) return true;

	return false;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR args, int show_cmd) {
	window.init(instance, WinProc, "OberlayWidgets");

	std::filesystem::create_directory("plugins/");
	
	for (auto& file : std::filesystem::directory_iterator("plugins/")) {
		if (!hasSubfix(file.path().string(), "dll")) continue;

		plugins.push_back(Plugin(file.path().string(), window.width, window.height));
	}

	MSG msg;
	while (GetMessage(&msg, window.window, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND p_window, UINT message, WPARAM wide_param, LPARAM long_param) {
	switch (message) {
	case WM_PAINT:
		window.render(plugins);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(0);
		break;
	default:
		return DefWindowProc(p_window, message, wide_param, long_param);
	}
	return 0;
}