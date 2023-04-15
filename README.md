# OverlayWidgets v1.0.4
![banner](/assets/OverlayWidgets.png)

 ![GitHub all releases](https://img.shields.io/github/downloads/Yibtag/OverlayWidgets/total) ![GitHub issues](https://img.shields.io/github/issues/Yibtag/OverlayWidgets) ![GitHub last commit](https://img.shields.io/github/last-commit/Yibtag/OverlayWidgets) ![GitHub repo size](https://img.shields.io/github/repo-size/Yibtag/OverlayWidgets)

Overlay widgets is a program that allows you to draw over other programs with its plugin api.

### How do i install it?

If you are to lazy to do it yourself then we have an [installer](https://github.com/Yibtag/OverlayWidgetsInstaller).

### How do i install a plugin?

Just move the ```plugin.dll``` to the ```/plugins/``` and restart you're program.

### How do i create a plugin?

Here is some example code. Make sure you iclude the ```plugin.h``` from ```/api/``` and compile it as a dll.

```cpp
#include "../include/plugin.h"

const char* Plugin::getName() {
	return "Example plugin";
}

void Plugin::onLoad(int width, int height) {
	addRect(1, 50, 50, 50, 50, 255, 255, 255, 255);
	addText(1, "Hello world", 100, 100, 255, 255, 255, 255);
}

void Plugin::onUpdate() {

}
```
