#include "UI.h"
#include "Character.h"


UI::UI()
:heartImage(nullptr)
{
    for (int i = 0; i < 5; i++)
    {
        amuletImages[i] = nullptr;
    }
}

UI::~UI() {
    delete heartImage;
    heartImage = nullptr;

    for (int i = 0; i < 5; i++)
    {
        delete amuletImages[i];
        amuletImages[i] = nullptr;
    }
}

bool UI::LoadImages() {
	heartImage = new Gdiplus::Image(L"Image\\Hp\\hp_heart.png");

	if (heartImage->GetLastStatus() != Gdiplus::Ok)
	{
		delete heartImage;
		heartImage = nullptr;
		return false;
	}

    amuletImages[0] = new Gdiplus::Image(L"Image\\Amulet\\y_1.png");
    amuletImages[1] = new Gdiplus::Image(L"Image\\Amulet\\r_1.png");
    amuletImages[2] = new Gdiplus::Image(L"Image\\Amulet\\b_1.png");
    amuletImages[3] = new Gdiplus::Image(L"Image\\Amulet\\w_1.png");
    amuletImages[4] = new Gdiplus::Image(L"Image\\Amulet\\black_1.png");
    
    for (int i = 0; i < 5; i++)
    {
        if (amuletImages[i] == nullptr ||
            amuletImages[i]->GetLastStatus() != Gdiplus::Ok)
        {
            for (int j = 0; j <= i; j++)
            {
                delete amuletImages[j];
                amuletImages[j] = nullptr;
            }

            delete heartImage;
            heartImage = nullptr;

            return false;
        }
    }
	return true;
}

void UI::Draw(Gdiplus::Graphics& graphics, Character* character, const std::vector<Amulet>& amulets,MapType currentMap) {
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
    // È®ÀÎ¿ë: ¾ÆÁ÷ È¹µæÇÏÁö ¾ÊÀº ºÎÀûÀ» ¸Ê ÁÂÇ¥¿¡ Ç¥½Ã
    for (const Amulet& amulet : amulets)
    {
        if (amulet.IsCollected())
        {
            continue;
        }

        if (amulet.GetMapType() != currentMap)
        {
            continue;
        }

        int imageIndex =
            static_cast<int>(amulet.GetType());

        graphics.DrawImage(
            amuletImages[imageIndex],
            Gdiplus::Rect(
                static_cast<int>(amulet.GetX()),
                static_cast<int>(amulet.GetY()),
                20,
                40
            )
        );
    }

    int index = 0;

    for (const Amulet& amulet : amulets)
    {
        if (!amulet.IsCollected()|| amulet.IsUsed())
        {
            continue;
        }


        int imageIndex =
            static_cast<int>(amulet.GetType());

        graphics.DrawImage(
            amuletImages[imageIndex],
            775 - 20 - 20 - index * 40,
            20,
            20,
            40
        );

        index++;
    }
}