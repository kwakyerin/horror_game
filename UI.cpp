#include "UI.h"
#include "Character.h"

UI::UI() {
	heartImage = nullptr;
}

UI::~UI() {
	delete heartImage;
}

bool UI::LoadImages() {
	heartImage = new Gdiplus::Image(L"Image\\Hp\\hp_heart.png");

	if (heartImage->GetLastStatus() != Gdiplus::Ok)
	{
		delete heartImage;
		heartImage = nullptr;
		return false;
	}

	return true;
}

void UI::Draw(Gdiplus::Graphics& graphics, Character* character) {
    if (heartImage == nullptr || character == nullptr)
        return;

    int heartCount = (character->GetHP() + 2) / 3;

    for (int i = 0; i < heartCount; i++)
    {
        graphics.DrawImage(
            heartImage,
            Gdiplus::Rect(
                20 + i * 38,
                20,
                32,
                32
            )
        );
    }
}