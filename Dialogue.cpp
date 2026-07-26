#include "Dialogue.h"

using namespace Gdiplus;

Dialogue::Dialogue()
    : isOpen(false),
    currentIndex(0)
{
}

Dialogue::~Dialogue()
{
}

// 기존 NPC처럼 한 문장만 열 때 사용
void Dialogue::Open(
    const std::wstring& speakerName,
    const std::wstring& dialogueText)
{
    speaker = speakerName;

    dialogueList.clear();
    dialogueList.push_back(dialogueText);

    currentIndex = 0;
    isOpen = true;
}

// 같은 화자가 여러 문장을 말할 때 사용
void Dialogue::Open(
    const std::wstring& speakerName,
    const std::vector<std::wstring>& texts)
{
    if (texts.empty())
    {
        Close();
        return;
    }

    speaker = speakerName;
    dialogueList = texts;

    currentIndex = 0;
    isOpen = true;
}

// 이름 없이 독백이나 프롤로그를 출력할 때 사용
void Dialogue::Open(const std::vector<std::wstring>& texts)
{
    Open(L"", texts);
}

// K키를 누를 때 다음 문장으로 이동
void Dialogue::Next()
{
    if (!isOpen)
    {
        return;
    }

    currentIndex++;

    // 마지막 문장 이후에는 대화창 닫기
    if (currentIndex >= dialogueList.size())
    {
        Close();
    }
}

// 대화창 닫기
void Dialogue::Close()
{
    isOpen = false;

    speaker.clear();
    dialogueList.clear();

    currentIndex = 0;
}

// 현재 대화창이 열렸는지 확인
bool Dialogue::IsOpen() const
{
    return isOpen;
}

// 현재 출력 중인 문장 반환
const std::wstring& Dialogue::GetCurrentText() const
{
    static const std::wstring emptyText = L"";

    if (!isOpen ||
        dialogueList.empty() ||
        currentIndex >= dialogueList.size())
    {
        return emptyText;
    }

    return dialogueList[currentIndex];
}

// 대화창 출력
void Dialogue::Draw(
    Gdiplus::Graphics& graphics,
    int screenWidth,
    int screenHeight)
{
    if (!isOpen ||
        dialogueList.empty() ||
        currentIndex >= dialogueList.size())
    {
        return;
    }

    // 대화창 크기와 위치
    const float margin = 20.0f;
    const float boxHeight = 130.0f;

    const float boxX = margin;
    const float boxY = static_cast<float>(screenHeight) - boxHeight - margin;
    const float boxWidth =
        static_cast<float>(screenWidth) - margin * 2.0f;

    RectF dialogueBox(
        boxX,
        boxY,
        boxWidth,
        boxHeight
    );

    // 반투명 검은색 대화창
    SolidBrush backgroundBrush(
        Color(220, 15, 15, 15)
    );

    graphics.FillRectangle(
        &backgroundBrush,
        dialogueBox
    );

    // 흰색 테두리
    Pen borderPen(
        Color(255, 230, 230, 230),
        2.0f
    );

    graphics.DrawRectangle(
        &borderPen,
        dialogueBox
    );

    FontFamily fontFamily(L"맑은 고딕");

    Font speakerFont(
        &fontFamily,
        18.0f,
        FontStyleBold,
        UnitPixel
    );

    Font textFont(
        &fontFamily,
        17.0f,
        FontStyleRegular,
        UnitPixel
    );

    SolidBrush speakerBrush(
        Color(255, 255, 220, 120)
    );

    SolidBrush textBrush(
        Color(255, 255, 255, 255)
    );

    StringFormat textFormat;

    textFormat.SetAlignment(StringAlignmentNear);
    textFormat.SetLineAlignment(StringAlignmentNear);
    textFormat.SetTrimming(StringTrimmingWord);

    float textStartY = boxY + 20.0f;

    // 화자 이름이 있을 때만 출력
    if (!speaker.empty())
    {
        RectF speakerArea(
            boxX + 20.0f,
            boxY + 14.0f,
            boxWidth - 40.0f,
            28.0f
        );

        graphics.DrawString(
            speaker.c_str(),
            static_cast<INT>(speaker.length()),
            &speakerFont,
            speakerArea,
            &textFormat,
            &speakerBrush
        );

        textStartY = boxY + 48.0f;
    }

    RectF textArea(
        boxX + 20.0f,
        textStartY,
        boxWidth - 40.0f,
        boxHeight - (textStartY - boxY) - 15.0f
    );

    const std::wstring& currentText =
        dialogueList[currentIndex];

    graphics.DrawString(
        currentText.c_str(),
        static_cast<INT>(currentText.length()),
        &textFont,
        textArea,
        &textFormat,
        &textBrush
    );
}