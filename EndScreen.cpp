#include "EndScreen.h"

using namespace Gdiplus;

EndScreen::EndScreen()
{
    backgroundImage = nullptr;
    retryButtonImage = nullptr;
    exitButtonImage = nullptr;

    retryHover = false;
    exitHover = false;

    // 버튼 원본 크기
    const int originalButtonWidth = 180;
    const int originalButtonHeight = 50;

    // 버튼 확대 배율
    const float buttonScale = 1.2f;

    int buttonWidth =
        static_cast<int>(originalButtonWidth * buttonScale);

    int buttonHeight =
        static_cast<int>(originalButtonHeight * buttonScale);

    // 810 화면 기준 가운데 정렬
    int buttonX = (810 - buttonWidth) / 2;

    // 다시 시도 버튼 위치
    int retryButtonY = 310;

    retryButtonRect =
    {
        buttonX,
        retryButtonY,
        buttonX + buttonWidth,
        retryButtonY + buttonHeight
    };

    // 다시 시도 버튼 아래 10픽셀
    int exitButtonY = retryButtonRect.bottom + 10;

    exitButtonRect =
    {
        buttonX,
        exitButtonY,
        buttonX + buttonWidth,
        exitButtonY + buttonHeight
    };
}

EndScreen::~EndScreen()
{
    delete backgroundImage;
    delete retryButtonImage;
    delete exitButtonImage;
}

bool EndScreen::LoadImages()
{
    backgroundImage =
        new Image(L"Image\\Endscreen\\end.png");

    retryButtonImage =
        new Image(L"Image\\Endscreen\\retry_button_v2.png");

    exitButtonImage =
        new Image(L"Image\\Endscreen\\exit_button_v2.png");

    if (backgroundImage->GetLastStatus() != Ok ||
        retryButtonImage->GetLastStatus() != Ok ||
        exitButtonImage->GetLastStatus() != Ok)
    {
        return false;
    }

    return true;
}

void EndScreen::Draw(Graphics& graphics)
{
    // 엔딩 화면 배경
    graphics.DrawImage(
        backgroundImage,
        0,
        0,
        810,
        600
    );
    int rx = retryButtonRect.left;
    int ry = retryButtonRect.top;

    int rw =retryButtonRect.right -retryButtonRect.left;

    int rh =retryButtonRect.bottom -retryButtonRect.top;

    if (retryHover)
    {
        graphics.DrawImage(
            retryButtonImage,
            rx - 5,
            ry - 3,
            rw + 10,
            rh + 6
        );
    }
    else
    {
        graphics.DrawImage(
            retryButtonImage,
            rx,
            ry,
            rw,
            rh
        );
    }

    // 나가기 버튼
    int ex = exitButtonRect.left;
    int ey = exitButtonRect.top;

    int ew =exitButtonRect.right -exitButtonRect.left;

    int eh =exitButtonRect.bottom -exitButtonRect.top;

    if (exitHover)
    {
        graphics.DrawImage(
            exitButtonImage,
            ex - 5,
            ey - 3,
            ew + 10,
            eh + 6
        );
    }
    else
    {
        graphics.DrawImage(
            exitButtonImage,
            ex,
            ey,
            ew,
            eh
        );
    }
}

bool EndScreen::UpdateHover(int mouseX, int mouseY)
{
    POINT pt = { mouseX, mouseY };

    bool oldRetryHover = retryHover;
    bool oldExitHover = exitHover;

    retryHover =PtInRect(&retryButtonRect, pt);

    exitHover =PtInRect(&exitButtonRect, pt);

    return oldRetryHover != retryHover || oldExitHover != exitHover;
}

bool EndScreen::IsRetryClicked(int mouseX,int mouseY)
{
    POINT pt = { mouseX, mouseY };

    return PtInRect(&retryButtonRect,pt );
}

bool EndScreen::IsExitClicked(int mouseX,int mouseY)
{
    POINT pt = { mouseX, mouseY };

    return PtInRect(&exitButtonRect,pt);
}

void EndScreen::ResetHover()
{
    retryHover = false;
    exitHover = false;
}