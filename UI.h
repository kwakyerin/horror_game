#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include "Amulet.h"
class Character;

class UI {
private:
	Gdiplus::Image* heartImage;
	Gdiplus::Image* amuletImages[5];
	
public:
	UI();
	~UI();

	bool LoadImages();

	void Draw(Gdiplus::Graphics& graphics, Character* character, const std::vector<Amulet>& amulets, MapType currentMap);
};
