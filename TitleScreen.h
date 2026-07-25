#pragma once

#include <windows.h>
#include <gdiplus.h>

class TitleScreen {
private:
    Gdiplus::Image* backgroundImage;
    Gdiplus::Image* startButtonImage;
    Gdiplus::Image* exitButtonImage;
    Gdiplus::Image* wispImage;

    RECT startButtonRect;
    RECT exitButtonRect;

    bool startHover;
    bool exitHover;

    int wispCurrentFrame;
    int wispFrameCount;

    float wispAnimationTimer;
    float wispFrameDelay;
    float wispFloatTime;
public:
public:
    TitleScreen();
    ~TitleScreen();

    bool LoadImages();

    void Update(float deltaTime);
    void Draw(Gdiplus::Graphics& graphics);

    bool UpdateHover(int mouseX, int mouseY);

    bool IsStartClicked(int mouseX, int mouseY);
    bool IsExitClicked(int mouseX, int mouseY);

    void ResetHover();
};