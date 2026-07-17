#pragma once
#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class  GameImage
{
public:
    GameImage();
    ~GameImage();

    bool Load(const wchar_t* filename);

    void Draw(HDC hdc, int x, int y);

private:
    Bitmap* bitmap;
    int width;
    int height;
};