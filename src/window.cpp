#include "window.h"

void Window::getScreenResolution() {
	const HWND desktop = GetDesktopWindow();
	RECT rect;

	GetWindowRect(desktop, &rect);

	width = rect.right;
	height = rect.bottom;
}

bool Window::init(HINSTANCE instance, WNDPROC window_process, const char* window_name) {
	window_class.cbSize = sizeof(WNDCLASSEXW);

	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = window_process;
	window_class.cbClsExtra = NULL;
	window_class.cbWndExtra = NULL;
	window_class.hInstance = instance;
	window_class.hIcon = NULL;
	window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	window_class.hbrBackground = CreateSolidBrush(RGB(245, 222, 179));
	window_class.lpszMenuName = (LPCWSTR)window_name;
	window_class.lpszClassName = (LPCWSTR)window_name;
	window_class.hIcon = NULL;

	if (!RegisterClassExW(&window_class)) {
		return false;
	}

	getScreenResolution();

	window = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
		(LPCWSTR)window_name,
		(LPCWSTR)window_name,
		WS_POPUP,
		0,
		0,
		width,
		height,
		nullptr,
		nullptr,
		instance,
		nullptr
	);


	if (!window) {
		return false;
	}

	SetLayeredWindowAttributes(
		window,
		RGB(245, 222, 179),
		0,
		LWA_COLORKEY
	);

	ShowWindow(window, SW_SHOW);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object))) {
		return false;
	}

	ZeroMemory(&params, sizeof(params));

	params.BackBufferWidth = width;
	params.BackBufferHeight = height;
	params.Windowed = true;
	params.hDeviceWindow = window;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	params.BackBufferFormat = D3DFMT_A8R8G8B8;
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(object->CreateDeviceEx(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&params,
		0,
		&device
	))) {
		return false;
	}

	D3DXCreateFontA(
		device,
		12,
		0,
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEVICE_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH,
		"Colibri",
		&font
	);

	return true;
}

void Window::draw_rect(int x, int y, int width, int height, int r, int g, int b, int a) {
	D3DRECT rect = {x, y, x + width, y + height};

	device->Clear(
		1,
		&rect,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(a, r, g, b),
		0,
		0
	);
}

void Window::draw_text(const char* content, int x, int y, int r, int g, int b, int a) {
	RECT rect;
	rect.top = y;
	rect.left = x;

	font->DrawTextA(
		0,
		content,
		strlen(content),
		&rect,
		DT_NOCLIP,
		D3DCOLOR_ARGB(a, r, g, b)
	);
}

void Window::render(std::vector<Plugin> plugins) {
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(0x58)) {
		if (taskbar) {
			ShowWindow(window, SW_HIDE);
			SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) & ~WS_EX_APPWINDOW);
			ShowWindow(window, SW_SHOW);
		} else {
			ShowWindow(window, SW_HIDE);
			SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_APPWINDOW);
			ShowWindow(window, SW_SHOW);
		}
		
		taskbar = !taskbar;
	}

	if (device == nullptr) return;

	device->Clear(
		0,
		0,
		D3DCLEAR_TARGET,
		D3DCOLOR_RGBA(245, 222, 179, 255),
		1.0f,
		0
	);

	device->BeginScene();

	for (Plugin plugin : plugins) {
		plugin.onUpdate();

		for (Rect rect : plugin.getRects()) {
			draw_rect(rect.x, rect.y, rect.width, rect.height, rect.r, rect.g, rect.b, rect.a);
		}

		for (Text text : plugin.getTexts()) {
			draw_text(text.content, text.x, text.y, text.r, text.g, text.b, text.a);
		}
	}

	device->EndScene();

	device->PresentEx(
		0,
		0,
		0,
		0,
		0
	);
}