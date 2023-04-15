#include "plugin.h"

#include <format>

Plugin::Plugin(std::string file, int width, int height) {
	dll = LoadLibrary((LPCSTR)file.c_str());

	if (dll == NULL) throw std::format("Failed to load {}!", file);

	getName = (getNameType)GetProcAddress(dll, "getName");
	onLoad = (onLoadType)GetProcAddress(dll, "onLoad");
	onUpdate = (onUpdateType)GetProcAddress(dll, "onUpdate");

	getRects = (getRectsType)GetProcAddress(dll, "getRects");
	getTexts = (getTextsType)GetProcAddress(dll, "getTexts");

	if (getName == NULL) throw std::format("Unable to get getName for {}!", file);
	if (onLoad == NULL) throw std::format("Unable to get onLoad for {}!", file);
	if (onUpdate == NULL) throw std::format("Unable to get onUpdate for {}!", file);

	if (getRects == NULL) throw std::format("Unable to get getRects for {}!", file);
	if (getTexts == NULL) throw std::format("Unable to get getTexts for {}!", file);
	
	onLoad(width, height);
}