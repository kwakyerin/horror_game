#include "QuizGhost.h"
#include <gdiplus.h>

QuizGhost::QuizGhost(float startX, float startY, const wchar_t* path)
:x(startX),
y(startY),
image(nullptr)
{
	image = new Gdiplus::Image(path);
    if (image->GetLastStatus() != Gdiplus::Ok)
    {
        delete image;
        image = nullptr;
    }
}

void QuizGhost::Update(float deltaTime,Character& character) {

}

QuizGhost::~QuizGhost() {
	delete image;
    image = nullptr;
}

void QuizGhost:: Draw(Gdiplus::Graphics& graphics) {
    if (image == nullptr)
    {
        return;
    }

    graphics.DrawImage(
        image,
        static_cast<int>(x),
        static_cast<int>(y),
        350,
        239
    );

    Gdiplus::Pen pen(
        Gdiplus::Color(255, 255, 0, 0),
        1.0f
    );

    RECT collisionRect = GetCollisionRect();

    graphics.DrawRectangle(
        &pen,
        static_cast<INT>(collisionRect.left),
        static_cast<INT>(collisionRect.top),
        static_cast<INT>(collisionRect.right - collisionRect.left),
        static_cast<INT>(collisionRect.bottom - collisionRect.top)
    );
}

RECT QuizGhost::GetCollisionRect() const
{
    RECT rect;

    rect.left = static_cast<LONG>(x);
    rect.top = static_cast<LONG>(y);

    rect.right = static_cast<LONG>(x + 340.0f);
    rect.bottom = static_cast<LONG>(y + 239.0f);

    return rect;
}

void QuizGhost::HandleInteraction(Character& character) {

}