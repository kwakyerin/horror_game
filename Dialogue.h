#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>

class Dialogue
{
public:
    Dialogue();
    ~Dialogue();

    // 한 문장 대화
    void Open(
        const std::wstring& speakerName,
        const std::wstring& dialogueText
    );

    // 여러 문장 대화
    void Open(
        const std::wstring& speakerName,
        const std::vector<std::wstring>& texts
    );

    // 화자 없는 프롤로그·독백
    void Open(
        const std::vector<std::wstring>& texts
    );

    void Next();
    void Close();

    bool IsOpen() const;

    const std::wstring& GetCurrentText() const;

    void Draw(
        Gdiplus::Graphics& graphics,
        int screenWidth,
        int screenHeight
    );

private:
    bool isOpen;

    std::wstring speaker;
    std::vector<std::wstring> dialogueList;

    size_t currentIndex;
};