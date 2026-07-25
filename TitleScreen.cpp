#include "TitleScreen.h"

using namespace Gdiplus;

TitleScreen::TitleScreen() {
    backgroundImage = nullptr;
    startButtonImage = nullptr;
    exitButtonImage = nullptr;

    startHover = false;
    exitHover = false;

    startButtonRect =
    {
        314,
        359,
        314 + 180,      
        359 + 50        
    };

    exitButtonRect =
    {
        314,
        424,
        314 + 180,
       424 + 50
    };

}

TitleScreen::~TitleScreen()
{
    delete backgroundImage;
    delete startButtonImage;
    delete exitButtonImage;
}

bool TitleScreen::LoadImages()
{
    backgroundImage =
        new Image(L"Image\\Startscreen\\start_screen.png");

    startButtonImage =
        new Image(L"Image\\Startscreen\\start_button.png");

    exitButtonImage =
       new Image(L"Image\\Startscreen\\title_exit_button.png");

    return true;
}

void TitleScreen::Draw(Graphics& graphics)
{
    graphics.DrawImage(backgroundImage, 0, 0, 810, 600);

    float scale = 1.5f;
    int sx = startButtonRect.left;
    int sy = startButtonRect.top;
    int sw = startButtonRect.right - startButtonRect.left;
    int sh = startButtonRect.bottom - startButtonRect.top;
    int drawW = static_cast<int>(sw * scale);
    int drawH = static_cast<int>(sh * scale);

    // 가운데를 기준으로 확대
    int drawX = sx - (drawW - sw) / 2;
    int drawY = sy - (drawH - sh) / 2;
    if (startHover)
    {
        graphics.DrawImage(
            startButtonImage,
            drawX - 5,
            drawY - 3,
            drawW + 10,
            drawH + 6
        );
    }
    else
    {
        graphics.DrawImage(
            startButtonImage,
            drawX,
            drawY,
            drawW,
            drawH
        );
    }

    int ex = exitButtonRect.left;
    int ey = exitButtonRect.top;
    int ew = exitButtonRect.right - exitButtonRect.left;
    int eh = exitButtonRect.bottom - exitButtonRect.top;
    int drawW_e = static_cast<int>(ew * scale);
    int drawH_e = static_cast<int>(eh * scale);

    // 가운데를 기준으로 확대
    int drawX_e = ex - (drawW_e - ew) / 2;
    int drawY_e = ey - (drawH_e - eh) / 2;
    if (exitHover)
    {
        graphics.DrawImage(
            exitButtonImage,
            drawX_e - 5,
            drawY_e - 3,
            drawW_e + 10,
            drawH_e + 6
        );
    }
    else
    {
        graphics.DrawImage(
            exitButtonImage,
            drawX_e,
            drawY_e,
            drawW_e,
            drawH_e
        );
    }
}

bool TitleScreen::UpdateHover(int mouseX, int mouseY)
{
    POINT pt = { mouseX,mouseY };

    bool oldStart = startHover;
    bool oldExit = exitHover;

    startHover = PtInRect(&startButtonRect, pt);
    exitHover = PtInRect(&exitButtonRect, pt);

    return oldStart != startHover ||
        oldExit != exitHover;
}

bool TitleScreen::IsStartClicked(int mouseX, int mouseY)
{
    POINT pt = { mouseX,mouseY };
    return PtInRect(&startButtonRect, pt);
}

bool TitleScreen::IsExitClicked(int mouseX, int mouseY)
{
    POINT pt = { mouseX,mouseY };
    return PtInRect(&exitButtonRect, pt);
}

void TitleScreen::ResetHover()
{
    startHover = false;
    exitHover = false;
}