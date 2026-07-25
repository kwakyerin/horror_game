#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <string>

class Dialogue
{
public:
    Dialogue();
    ~Dialogue();

    void Open(
        const std::wstring& speaker,
        const std::wstring& text
    );

    void Close();

    bool IsOpen() const;

    void Draw(
        Gdiplus::Graphics& graphics,
        int screenWidth,
        int screenHeight
    );

private:
    bool isOpen;

    std::wstring speaker;
    std::wstring text;
};