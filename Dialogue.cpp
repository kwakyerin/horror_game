#include "Dialogue.h"

using namespace Gdiplus;

Dialogue::Dialogue()
{
    isOpen = false;
    speaker = L"";
    text = L"";
}

Dialogue::~Dialogue()
{
}

void Dialogue::Open(
    const std::wstring& newSpeaker,
    const std::wstring& newText)
{
    speaker = newSpeaker;
    text = newText;
    isOpen = true;
}

void Dialogue::Close()
{
    isOpen = false;
}

bool Dialogue::IsOpen() const
{
    return isOpen;
}

void Dialogue::Draw(
    Graphics& graphics,
    int screenWidth,
    int screenHeight)
{
    if (!isOpen)
    {
        return;
    }

    const int margin = 20;

    const int boxWidth = screenWidth - (margin * 2);
    const int boxHeight = 160;

    const int boxX = margin;
    const int boxY = screenHeight - boxHeight - margin;

    SolidBrush backgroundBrush( Color(180, 0, 0, 0) );

    graphics.FillRectangle(
        &backgroundBrush,
        boxX,
        boxY,
        boxWidth,
        boxHeight
    );

    Pen outerBorder( Color(255, 255, 255, 255),3.0f );

    graphics.DrawRectangle( &outerBorder,boxX, boxY,boxWidth,boxHeight );

    Pen innerBorder( Color(230, 140, 140, 140),1.0f );

    graphics.DrawRectangle(&innerBorder,boxX + 5,boxY + 5, boxWidth - 10,boxHeight - 10);

    // 이름과 대사 사이 구분선
    Pen separatorPen( Color(160, 255, 255, 255), 1.0f );

    graphics.DrawLine(
        &separatorPen,
        boxX + 20,
        boxY + 47,
        boxX + boxWidth - 20,
        boxY + 47
    );

    FontFamily fontFamily(L"맑은 고딕");

    Font nameFont(
        &fontFamily,
        18,
        FontStyleBold,
        UnitPixel
    );

    Font textFont(
        &fontFamily,
        20,
        FontStyleRegular,
        UnitPixel
    );

    SolidBrush nameBrush(
        Color(255, 255, 255, 255)
    );

    SolidBrush textBrush(
        Color(255, 240, 240, 240)
    );

    // NPC 이름
    graphics.DrawString(
        speaker.c_str(),
        -1,
        &nameFont,
        PointF(
            static_cast<REAL>(boxX + 20),
            static_cast<REAL>(boxY + 15)
        ),
        &nameBrush
    );

    // 대사 출력 영역
    RectF textArea(
        static_cast<REAL>(boxX + 20),
        static_cast<REAL>(boxY + 60),
        static_cast<REAL>(boxWidth - 40),
        static_cast<REAL>(boxHeight - 80)
    );

    StringFormat textFormat;

    textFormat.SetAlignment(
        StringAlignmentNear
    );

    textFormat.SetLineAlignment(
        StringAlignmentNear
    );

    textFormat.SetTrimming(
        StringTrimmingWord
    );

    graphics.DrawString(
        text.c_str(),
        -1,
        &textFont,
        textArea,
        &textFormat,
        &textBrush
    );

    // 오른쪽 아래 대화 진행 표시
    SolidBrush arrowBrush(
        Color(230, 255, 255, 255)
    );

    PointF arrowPoints[3] =
    {
        PointF(
            static_cast<REAL>(boxX + boxWidth - 30),
            static_cast<REAL>(boxY + boxHeight - 25)
        ),

        PointF(
            static_cast<REAL>(boxX + boxWidth - 14),
            static_cast<REAL>(boxY + boxHeight - 25)
        ),

        PointF(
            static_cast<REAL>(boxX + boxWidth - 22),
            static_cast<REAL>(boxY + boxHeight - 13)
        )
    };

    graphics.FillPolygon(
        &arrowBrush,
        arrowPoints,
        3
    );
}