#include "QuizGhost.h"
#include <gdiplus.h>
#include "Character.h"
#include "Dialogue.h"

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
bool QuizGhost::IsPlayerNear(const Character& character)const {
    RECT playerRect = character.GetCollisionRect();
    RECT ghostRect = GetCollisionRect();

    RECT interactRect = ghostRect;

    interactRect.left -= 60;
    interactRect.top -= 60;
    interactRect.right += 60;
    interactRect.bottom += 60;

    RECT result;

    return IntersectRect(&result, &playerRect, &interactRect);
}

void QuizGhost::HandleInteraction(Character& character,Dialogue& dialogue)
{
    if (!IsPlayerNear(character))
    {
        return;
    }

    dialogue.Open(
        L"퀴즈 괴물",
        {
            L"거기 인간...",
            L"이곳을 지나가려면 내 문제를 풀어야 한다.",
            L"범인을 찾아오너라..."
        }
    );
}