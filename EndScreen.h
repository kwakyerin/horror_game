#pragma once
#include <windows.h>
#include <gdiplus.h>

class EndScreen {
private:
    Gdiplus::Image* backgroundImage;
    Gdiplus::Image* retryButtonImage;
    Gdiplus::Image* exitButtonImage;

    RECT retryButtonRect;
    RECT exitButtonRect;

    bool retryHover;
    bool exitHover;

public:
    EndScreen();
    ~EndScreen();

    bool LoadImages();

    void Draw(Gdiplus::Graphics& graphics);

    bool UpdateHover(int mouseX, int mouseY);

    bool IsRetryClicked(int mouseX, int mouseY);
    bool IsExitClicked(int mouseX, int mouseY);

    void ResetHover();
};