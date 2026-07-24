#include "kkamakGhost.h"

KkamakGhost::KkamakGhost(float startX, float startY, const wchar_t* path)
	:x(startX),
	y(startY),
	moveSpeed(250.0f),
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

void KkamakGhost::Update(float deltaTime, const Character& character)
{

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
    return false;
}

bool KkamakGhost::IsCollidingWithPlayer(const Character& character) const
{
    return false;
}