#include "Image.h"

GameImage::GameImage()
    : bitmap(nullptr), width(0), height(0)
{
}

GameImage::~GameImage()
{
    delete bitmap;
}

bool GameImage::Load(const wchar_t* filename)
{
    delete bitmap;
    bitmap = nullptr;

    bitmap = Bitmap::FromFile(filename);

    if (bitmap == nullptr)
    {
        MessageBox( nullptr,L"이미지 객체 생성 실패",L"오류",MB_OK );

        return false;
    }

    if (bitmap->GetLastStatus() != Ok)
    {
       // MessageBox( nullptr,L"이미지 로드 실패",L"오류",MB_OK );

        delete bitmap;
        bitmap = nullptr;

        return false;
    }

    width = static_cast<int>(bitmap->GetWidth());
    height = static_cast<int>(bitmap->GetHeight());

    return true;
}

// graphics.DrawImage(bitmap, x, y, width, height);Graphics graphics(hdc);

void GameImage::Draw(HDC hdc, int x, int y)
{
    if (bitmap == nullptr)
    {
        return;
    }

    Graphics graphics(hdc);

    graphics.DrawImage( bitmap,x,y,width,height );

}