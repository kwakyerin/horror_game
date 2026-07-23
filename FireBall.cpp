#include "FireBall.h"
#include <cmath>

FireBall::FireBall(float startX,float startY,float directionX,float directionY)
    : x(startX),
    y(startY),
    dirX(directionX),
    dirY(directionY),
    speed(150.0f),
    image(nullptr),
    active(true),
    currentFrame(0),
    animationTimer(0.0f)
{
    // 방향 벡터의 길이
    float length = std::sqrt(
        dirX * dirX +
        dirY * dirY);

    // 방향을 일정한 길이로 맞춤
    if (length > 0.0f)
    {
        dirX /= length;
        dirY /= length;
    }
    else
    {
        // 구미호와 플레이어의 위치가 완전히 같을 경우
        dirX = 0.0f;
        dirY = 1.0f;
    }

    // 불꽃 이미지 로드
    if (!LoadImage(L"Image\\monster_gumiho\\Fire.png"))
    {
        active = false;
    }
}

FireBall::~FireBall()
{
    delete image;
    image = nullptr;
}

bool FireBall::LoadImage(const wchar_t* path)
{
    image = new Gdiplus::Image(path);

    if (image->GetLastStatus() != Gdiplus::Ok)
    {
        delete image;
        image = nullptr;

        return false;
    }

    return true;
}

void FireBall::Update(float deltaTime)
{
    if (!active)
    {
        return;
    }

    // 불꽃 이동
    x += dirX * speed * deltaTime;
    y += dirY * speed * deltaTime;

    // 애니메이션 시간 누적
    animationTimer += deltaTime;

    // 0.08초마다 다음 프레임으로 변경
    if (animationTimer >= 0.08f)
    {
        animationTimer -= 0.08f;

        currentFrame++;

        // 총 14프레임: 0부터 13까지
        if (currentFrame >= 14)
        {
            currentFrame = 0;
        }
    }

    // 화면 밖으로 나가면 비활성화
    if (x < -64.0f ||
        x > 775.0f ||
        y < -64.0f ||
        y > 600.0f)
    {
        active = false;
    }
}

void FireBall::Draw(Gdiplus::Graphics& graphics)
{
    if (!active || image == nullptr)
    {
        return;
    }

    const int frameWidth = 64;
    const int frameHeight = 64;

    // 현재 프레임이 시작되는 원본 이미지의 x 좌표
    int sourceX = currentFrame * frameWidth;

    graphics.DrawImage(
        image,

        // 화면에 출력할 위치와 크기
        Gdiplus::Rect(
            static_cast<int>(x),
            static_cast<int>(y),
            frameWidth,
            frameHeight),

        // 스프라이트 시트에서 잘라올 영역
        sourceX,
        0,
        frameWidth,
        frameHeight,

        Gdiplus::UnitPixel);
}

RECT FireBall::GetCollisionRect() const
{
    RECT collisionRect =
    {
        static_cast<LONG>(x + 16.0f),
        static_cast<LONG>(y + 16.0f),
        static_cast<LONG>(x + 48.0f),
        static_cast<LONG>(y + 48.0f)
    };

    return collisionRect;
}

bool FireBall::IsActive() const
{
    return active;
}

void FireBall::Deactivate()
{
    active = false;
}