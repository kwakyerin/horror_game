#pragma once

#include <windows.h>
#include <gdiplus.h>

class TitleScreen {
private:
    Gdiplus::Image* backgroundImage;
    Gdiplus::Image* startButtonImage;
    Gdiplus::Image* exitButtonImage;

    RECT startButtonRect;
    RECT exitButtonRect;

    bool startHover;
    bool exitHover;

public:
public:
    TitleScreen();
    ~TitleScreen();

    bool LoadImages();

    void Draw(Gdiplus::Graphics& graphics);

    bool UpdateHover(int mouseX, int mouseY);

    bool IsStartClicked(int mouseX, int mouseY);
    bool IsExitClicked(int mouseX, int mouseY);

    void ResetHover();
};