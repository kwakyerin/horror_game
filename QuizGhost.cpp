#include "QuizGhost.h"
#include <gdiplus.h>
#include "Character.h"

QuizGhost::QuizGhost(float startX, float startY, const wchar_t* path)
:x(startX),
y(startY),
image(nullptr),
Dialogue_box(nullptr),
isTalking(false)
{
	image = new Gdiplus::Image(path);
    if (image->GetLastStatus() != Gdiplus::Ok)
    {
        delete image;
        image = nullptr;
    }
    Dialogue_box = new Gdiplus::Image(L"Image\\monster_quiz\\Dialogue_box.png");

    if (Dialogue_box->GetLastStatus() != Gdiplus::Ok)
    {
        delete Dialogue_box;
        Dialogue_box = nullptr;
    }

   
}

void QuizGhost::Update(float deltaTime,Character& character) {

}

QuizGhost::~QuizGhost() {
	delete image;
    image = nullptr;

    delete Dialogue_box;
    Dialogue_box = nullptr;

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

    if (isTalking && Dialogue_box != nullptr)
    {
       

        Gdiplus::Font font(
            L"궁서",
            20,
            Gdiplus::FontStyleBold,
            Gdiplus::UnitPixel
        );

        Gdiplus::SolidBrush shadowBrush(
            Gdiplus::Color(255, 0, 0, 0)
        );

        Gdiplus::SolidBrush textBrush(
            Gdiplus::Color(255, 255, 255, 255)
        );

        const wchar_t* text = L"범인을 찾아오너라...";

        // 글자 그림자
        graphics.DrawString(
            text,
            -1,
            &font,
            Gdiplus::PointF(52.0f, 472.0f),
            &shadowBrush
        );

        // 실제 글자
        graphics.DrawString(
            text,
            -1,
            &font,
            Gdiplus::PointF(50.0f, 470.0f),
            &textBrush
        );
    }

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
void QuizGhost::HandleInteraction(Character& character) {
    if (!IsPlayerNear(character))
        return;

    isTalking = !isTalking;
}