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

void QuizGhost::Update(float deltaTime) {

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
}