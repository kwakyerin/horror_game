#include "QuizGhost.h"
#include "Character.h"
#include "Dialogue.h"

#include <gdiplus.h>
#include <string>
#include <vector>

QuizGhost::QuizGhost(
    float startX,
    float startY,
    const wchar_t* path)
    : x(startX),
    y(startY),
    image(nullptr),
    currentQuestionIndex(0),
    selectedChoiceIndex(0),
    lastAnswerCorrect(false),
    isVisible(true),
    quizState(QuizState::Idle)
{
    image = new Gdiplus::Image(path);

    if (image->GetLastStatus() != Gdiplus::Ok)
    {
        delete image;
        image = nullptr;
    }

    // 첫 번째 문제
    questions.push_back(
        {
            L"오징어 다리는 몇 개지?",
            {
                L"10개",
                L"8개",
                L"12개"
            },
            0 //정답
        }
    );

    // 두 번째 문제
    questions.push_back(
        {
            L"제일 안씻고 더러운 사람은?",
            {
                L"나",
                L"너",
                L"게임공학과 학생들"
            },
            0 // 첫 번째 선택지인 부적이 정답
        }
    );

    // 세 번째 문제
    questions.push_back(
        {
            L"이 세상에서 가장 착한 사람은 누구일까?",
            {
                L"나",
                L"너",
                L"우리"
            },
            1
        }
    );
}

QuizGhost::~QuizGhost()
{
    delete image;
    image = nullptr;
}

void QuizGhost::Update(
    float deltaTime,
    Character& character)
{
}

void QuizGhost::Draw(Gdiplus::Graphics& graphics)
{
    if (!isVisible || image == nullptr)
    {
        return;
    }

    // 퀴즈 괴물 이미지
    graphics.DrawImage(
        image,
        static_cast<int>(x),
        static_cast<int>(y),
        350,
        239
    );

    // 퀴즈 선택 중일 때 문제와 선택지 출력
    if (quizState == QuizState::Selecting &&
        currentQuestionIndex >= 0 &&
        currentQuestionIndex <
        static_cast<int>(questions.size()))
    {
        const QuizQuestion& currentQuestion =
            questions[currentQuestionIndex];

        const float boxX = 20.0f;
        const float boxY = 380.0f;
        const float boxWidth = 760.0f;
        const float boxHeight = 200.0f;

        Gdiplus::RectF quizBox(
            boxX,
            boxY,
            boxWidth,
            boxHeight
        );

        // 배경
        Gdiplus::SolidBrush backgroundBrush(
            Gdiplus::Color(230, 15, 15, 15)
        );

        graphics.FillRectangle(
            &backgroundBrush,
            quizBox
        );

        // 테두리
        Gdiplus::Pen borderPen(
            Gdiplus::Color(255, 230, 230, 230),
            2.0f
        );

        graphics.DrawRectangle(
            &borderPen,
            quizBox
        );

        Gdiplus::FontFamily fontFamily(L"맑은 고딕");

        Gdiplus::Font questionFont(
            &fontFamily,
            18.0f,
            Gdiplus::FontStyleBold,
            Gdiplus::UnitPixel
        );

        Gdiplus::Font choiceFont(
            &fontFamily,
            17.0f,
            Gdiplus::FontStyleRegular,
            Gdiplus::UnitPixel
        );

        Gdiplus::SolidBrush questionBrush(
            Gdiplus::Color(255, 255, 220, 120)
        );

        Gdiplus::SolidBrush normalBrush(
            Gdiplus::Color(255, 230, 230, 230)
        );

        Gdiplus::SolidBrush selectedBrush(
            Gdiplus::Color(255, 255, 210, 80)
        );

        // 문제 출력
        graphics.DrawString(
            currentQuestion.question.c_str(),
            static_cast<INT>(
                currentQuestion.question.length()),
            &questionFont,
            Gdiplus::PointF(
                boxX + 20.0f,
                boxY + 18.0f),
            &questionBrush
        );

        // 선택지 출력
        for (int i = 0;
            i < static_cast<int>(
                currentQuestion.choices.size());
            i++)
        {
            std::wstring choiceText;

            if (i == selectedChoiceIndex)
            {
                choiceText = L"> ";
            }
            else
            {
                choiceText = L"   ";
            }

            choiceText += currentQuestion.choices[i];

            Gdiplus::SolidBrush* currentBrush =
                (i == selectedChoiceIndex)
                ? &selectedBrush
                : &normalBrush;

            graphics.DrawString(
                choiceText.c_str(),
                static_cast<INT>(choiceText.length()),
                &choiceFont,
                Gdiplus::PointF(
                    boxX + 30.0f,
                    boxY + 60.0f + i * 32.0f),
                currentBrush
            );
        }

        const wchar_t* controlText =
            L"W / S : 선택    K : 결정";

        graphics.DrawString(
            controlText,
            -1,
            &choiceFont,
            Gdiplus::PointF(
                boxX + 480.0f,
                boxY + 160.0f),
            &normalBrush
        );
    }

    // 충돌 범위 확인용
    Gdiplus::Pen collisionPen(
        Gdiplus::Color(255, 255, 0, 0),
        1.0f
    );

    RECT collisionRect = GetCollisionRect();

    graphics.DrawRectangle(
        &collisionPen,
        static_cast<INT>(collisionRect.left),
        static_cast<INT>(collisionRect.top),
        static_cast<INT>(
            collisionRect.right -
            collisionRect.left),
        static_cast<INT>(
            collisionRect.bottom -
            collisionRect.top)
    );
}

RECT QuizGhost::GetCollisionRect() const
{
    if (!isVisible)
    {
        return RECT{ 0, 0, 0, 0 };
    }

    RECT rect;

    rect.left = static_cast<LONG>(x);
    rect.top = static_cast<LONG>(y);
    rect.right = static_cast<LONG>(x + 340.0f);
    rect.bottom = static_cast<LONG>(y + 239.0f);

    return rect;
}

bool QuizGhost::IsPlayerNear(
    const Character& character) const
{
    if (!isVisible)
    {
        return false;
    }

    RECT playerRect = character.GetCollisionRect();
    RECT ghostRect = GetCollisionRect();

    RECT interactRect = ghostRect;

    interactRect.left -= 60;
    interactRect.top -= 60;
    interactRect.right += 60;
    interactRect.bottom += 60;

    RECT result;

    return IntersectRect(
        &result,
        &playerRect,
        &interactRect
    );
}

void QuizGhost::HandleInteraction(
    Character& character,
    Dialogue& dialogue)
{
    if (!isVisible)
    {
        return;
    }

    switch (quizState)
    {
        // 처음 괴물에게 말을 걸었을 때
    case QuizState::Idle:
    {
        if (!IsPlayerNear(character))
        {
            return;
        }

        dialogue.Open(
            L"퀴즈 괴물",
            {
                L"?",
                L"누가 날 깨운 거지.",
                L"뭐? 여길 지나가야 한다고?",
                L"지나가려면 퀴즈 세 문제를 풀어야 하는데.",
                L"엄청 쉬우니까 걱정 마.",
                L"대신 못 풀면 죽어야 돼. 알겠지?"
            }
        );

        quizState = QuizState::Intro;
        break;
    }

    // 소개 대화를 넘기는 상태
    case QuizState::Intro:
    {
        dialogue.Next();

        // 소개 대화를 모두 읽은 후 문제 시작
        if (!dialogue.IsOpen())
        {
            currentQuestionIndex = 0;
            selectedChoiceIndex = 0;
            quizState = QuizState::Selecting;
        }

        break;
    }

    // 문제 선택 중 K키를 누르면 답 확정
    case QuizState::Selecting:
    {
        CheckAnswer(dialogue);
        break;
    }

    // 정답 또는 오답 대사 진행
    case QuizState::Result:
    {
        dialogue.Next();

        // 결과 대사가 닫혔을 때
        if (!dialogue.IsOpen())
        {
            if (lastAnswerCorrect)
            {
                MoveToNextQuestion(dialogue);
            }
            else
            {
                // 오답이면 같은 문제 다시 선택
                selectedChoiceIndex = 0;
                quizState = QuizState::Selecting;
            }
        }

        break;
    }

    // 세 문제를 모두 맞힌 후 마지막 대사
    case QuizState::Ending:
    {
        dialogue.Next();

        if (!dialogue.IsOpen())
        {
            isVisible = false;
            quizState = QuizState::Cleared;
        }

        break;
    }

    case QuizState::Cleared:
        break;
    }
}

void QuizGhost::MoveSelectionUp()
{
    if (quizState != QuizState::Selecting)
    {
        return;
    }

    if (currentQuestionIndex < 0 ||
        currentQuestionIndex >=
        static_cast<int>(questions.size()))
    {
        return;
    }

    int choiceCount = static_cast<int>(
        questions[currentQuestionIndex].choices.size()
        );

    if (choiceCount <= 0)
    {
        return;
    }

    selectedChoiceIndex--;

    // 첫 번째에서 위로 가면 마지막 선택지로 이동
    if (selectedChoiceIndex < 0)
    {
        selectedChoiceIndex = choiceCount - 1;
    }
}

void QuizGhost::MoveSelectionDown()
{
    if (quizState != QuizState::Selecting)
    {
        return;
    }

    if (currentQuestionIndex < 0 ||
        currentQuestionIndex >=
        static_cast<int>(questions.size()))
    {
        return;
    }

    int choiceCount = static_cast<int>(
        questions[currentQuestionIndex].choices.size()
        );

    if (choiceCount <= 0)
    {
        return;
    }

    selectedChoiceIndex++;

    // 마지막에서 아래로 가면 첫 번째 선택지로 이동
    if (selectedChoiceIndex >= choiceCount)
    {
        selectedChoiceIndex = 0;
    }
}

void QuizGhost::CheckAnswer(Dialogue& dialogue)
{
    if (quizState != QuizState::Selecting)
    {
        return;
    }

    if (currentQuestionIndex < 0 ||
        currentQuestionIndex >=
        static_cast<int>(questions.size()))
    {
        return;
    }

    const QuizQuestion& currentQuestion =
        questions[currentQuestionIndex];

    if (selectedChoiceIndex ==
        currentQuestion.correctIndex)
    {
        lastAnswerCorrect = true;

        dialogue.Open(
            L"퀴즈 괴물",
            L"정답이다. 제법이군."
        );
    }
    else
    {
        lastAnswerCorrect = false;

        dialogue.Open(
            L"퀴즈 괴물",
            L"멍청하군. 그냥 죽어"
        );
    }

    quizState = QuizState::Result;
}

void QuizGhost::MoveToNextQuestion(Dialogue& dialogue)
{
    currentQuestionIndex++;
    selectedChoiceIndex = 0;

    // 세 문제를 모두 맞힌 경우
    if (currentQuestionIndex >=
        static_cast<int>(questions.size()))
    {
        dialogue.Open(
            L"퀴즈 괴물",
            {
                L"설마 세 문제를 모두 맞힐 줄이야.",
                L"약속은 약속이지.",
                L"맞혔으니 없어져 주지."
            }
        );

        quizState = QuizState::Ending;
    }
    else
    {
        // 다음 문제 선택 상태
        quizState = QuizState::Selecting;
    }
}

bool QuizGhost::IsQuizActive() const
{
    return quizState != QuizState::Idle &&
        quizState != QuizState::Cleared;
}

bool QuizGhost::IsSelecting() const
{
    return quizState == QuizState::Selecting;
}

bool QuizGhost::IsVisible() const
{
    return isVisible;
}

void QuizGhost::SetVisible(bool visible)
{
    isVisible = visible;

}
