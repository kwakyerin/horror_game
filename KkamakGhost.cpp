#include "kkamakGhost.h"
#include "Character.h"
#include <cmath>

KkamakGhost::KkamakGhost(float startX, float startY, const wchar_t* path)
	:x(startX),
	y(startY),
	moveSpeed(100.0f),
	image(nullptr)
{
	LoadImage(path);
}

KkamakGhost::~KkamakGhost() {
	delete image;
}

bool KkamakGhost::LoadImage(const wchar_t* path)
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

void KkamakGhost::Draw(Gdiplus::Graphics& graphics)
{
    if (image == nullptr)
        return;

    graphics.DrawImage(
        image,
        static_cast<int>(x),
        static_cast<int>(y),
        60,
        80
    );

    RECT rc = GetCollisionRect();

    Gdiplus::Pen collisionPen(
        Gdiplus::Color(255, 255, 0, 0),
        2.0f);

    graphics.DrawRectangle(
        &collisionPen,
        static_cast<INT>(rc.left),
        static_cast<INT>(rc.top),
        static_cast<INT>(rc.right - rc.left),
        static_cast<INT>(rc.bottom - rc.top)
    );
}

bool KkamakGhost::Update(float deltaTime, const Character& character)
{
    // 플레이어가 보고 있으면 멈춤
    if (IsPlayerLooking(character))
    {
        return false;
    }

    // 플레이어 방향으로 이동
    float dx = character.GetX() - x;
    float dy = character.GetY() - y;

    if (std::abs(dx) > std::abs(dy))
    {
        if (dx > 0.0f)
        {
            x += moveSpeed * deltaTime;
        }
        else if (dx < 0.0f)
        {
            x -= moveSpeed * deltaTime;
        }
    }
    // 세로 거리가 더 멀면 y축으로만 이동
    else
    {
        if (dy > 0.0f)
        {
            y += moveSpeed * deltaTime;
        }
        else if (dy < 0.0f)
        {
            y -= moveSpeed * deltaTime;
        }
    }

    // 플레이어와 닿았는지 검사
    if (IsCollidingWithPlayer(character))
    {
        // 게임 오버 처리
        return true;
    }

    return false;
}

RECT KkamakGhost::GetCollisionRect() const
{
    RECT rc;

    rc.left = static_cast<LONG>(x);
    rc.top = static_cast<LONG>(y);
    rc.right = static_cast<LONG>(x + 60);
    rc.bottom = static_cast<LONG>(y + 80);

    return rc;
}

bool KkamakGhost::IsPlayerLooking(const Character& character) const
{
    switch (character.GetDirection())
    {
    case Direction::Up:
        return y < character.GetY();

    case Direction::Down:
        return y > character.GetY();

    case Direction::Left:
        return x < character.GetX();

    case Direction::Right:
        return x > character.GetX();
    }
    return false;
}

bool KkamakGhost::IsCollidingWithPlayer(const Character& character) const
{
    RECT ghostRect = GetCollisionRect();
    RECT playerRect = character.GetCollisionRect();
    RECT result;

    if (IntersectRect(&result, &ghostRect, &playerRect))
    {
        return true;
    }
    return false;
}

void KkamakGhost::Reset()
{
    x = startX;
    y = startY;
}