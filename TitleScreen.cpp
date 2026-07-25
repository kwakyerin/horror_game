#include "TitleScreen.h"
#include <cmath>

using namespace Gdiplus;

TitleScreen::TitleScreen() {
    backgroundImage = nullptr;
    startButtonImage = nullptr;
    exitButtonImage = nullptr;
    wispImage = nullptr;

    startHover = false;
    exitHover = false;

    wispCurrentFrame = 0;
    wispFrameCount = 4;
    wispAnimationTimer = 0.0f;
    wispFrameDelay = 0.12f;
    wispFloatTime = 0.0f;

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

    wispImage =
        new Image(L"Image\\Startscreen\\wisp.png");

    return true;
}

void TitleScreen::Update(float deltaTime)
{
    wispAnimationTimer += deltaTime;
    wispFloatTime += deltaTime;

    if (wispAnimationTimer >= wispFrameDelay)
    {
        wispAnimationTimer -= wispFrameDelay;

        wispCurrentFrame++;

        if (wispCurrentFrame >= wispFrameCount)
        {
            wispCurrentFrame = 0;
        }
    }
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

    if (wispImage != nullptr)
    {
        int frameWidth = 260 / wispFrameCount;
        int frameHeight = 100;

        int srcX = wispCurrentFrame * frameWidth;
        int srcY = 0;

        // 도깨비불이 화면에 그려질 기본 위치 
        int destX = 150;
        int destY = 200;

        // wispFloatTime을 활용해 위아래로 부드럽게 둥둥 떠다니는 오프셋 값 계산
        // 3.0f는 떠다니는 속도, 10.0f는 떠다니는 범위(픽셀)를 의미
        int floatOffsetY = static_cast<int>(sin(wispFloatTime * 3.0f) * 10.0f);

        graphics.DrawImage(
            wispImage,
            Rect(destX, destY + floatOffsetY, frameWidth, frameHeight), // 화면에 그려질 영역
            srcX,                                                       // 원본 이미지의 X
            srcY,                                                       // 원본 이미지의 Y
            frameWidth,                                                 // 가져올 너비
            frameHeight,                                                // 가져올 높이
            UnitPixel                                                   // 단위
        );

        int destX2 = 650; // 오른쪽 도깨비불 X 좌표 
        int destY2 = 300; // 오른쪽 도깨비불 Y 좌표 

        int floatOffsetY2 = static_cast<int>(sin((wispFloatTime + 2.0f) * 2.0f) * 10.0f);

        graphics.DrawImage(
            wispImage,
            Rect(destX2, destY2 + floatOffsetY2, frameWidth, frameHeight),
            srcX, srcY, frameWidth, frameHeight, UnitPixel
        );

        int destX3 = 500; // 타이틀 옆 도깨비불 X 좌표 
        int destY3 = 100; // 타이틀 옆 도깨비불 Y 좌표 

        int floatOffsetY3 = static_cast<int>(sin((wispFloatTime + 2.0f) * 1.0f) * 10.0f);

        graphics.DrawImage(
            wispImage,
            Rect(destX3, destY3 + floatOffsetY3, frameWidth, frameHeight),
            srcX, srcY, frameWidth, frameHeight, UnitPixel
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