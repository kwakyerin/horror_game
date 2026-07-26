#pragma once
#include <Windows.h>
#include <gdiplus.h>

class Character;

class UI {
private:
	Gdiplus::Image* heartImage;
public:
	UI();
	~UI();

	bool LoadImages();

	void Draw(Gdiplus::Graphics& graphics, Character* character);
};
