#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>

class Character;
class Dialogue;

class QuizGhost
{
private:
    // 문제 하나의 정보
    struct QuizQuestion
    {
        std::wstring question;
        std::vector<std::wstring> choices;

        // 정답 번호는 0부터 시작
        int correctIndex;
    };

    // 퀴즈 진행 상태
    enum class QuizState
    {
        Idle,           // 아직 상호작용하지 않은 상태
        Intro,          // 퀴즈 시작 전 대화
        Selecting,      // W/S로 선택지를 고르는 상태
        Result,         // 정답 또는 오답 메시지 출력
        Ending,         // 3문제 완료 후 마지막 대화
        Cleared         // 퀴즈 완료, 괴물 제거
    };

private:
    float x;
    float y;

    Gdiplus::Image* image;

    // 퀴즈 문제 목록
    std::vector<QuizQuestion> questions;

    // 현재 문제 번호
    int currentQuestionIndex;

    // 현재 선택 중인 선택지 번호
    int selectedChoiceIndex;

    // 방금 선택한 답이 정답인지
    bool lastAnswerCorrect;

    // 괴물이 화면에 보이는지
    bool isVisible;

    QuizState quizState;

private:
    // 현재 문제를 대화창에 표시
    void ShowCurrentQuestion(Dialogue& dialogue);

    // 현재 선택한 답을 검사
    void CheckAnswer(Dialogue& dialogue);

    // 다음 문제로 이동
    void MoveToNextQuestion(Dialogue& dialogue);

public:
    QuizGhost(
        float startX,
        float startY,
        const wchar_t* path
    );

    ~QuizGhost();

    bool IsQuizActive() const;

    void Draw(Gdiplus::Graphics& graphics);
    void Update(float deltaTime, Character& character);

    void SetVisible(bool visible);
    bool IsVisible() const;

    // K키로 상호작용하거나 선택 확정
    void HandleInteraction(
        Character& character,
        Dialogue& dialogue
    );

    // W키로 위쪽 선택지
    void MoveSelectionUp();

    // S키로 아래쪽 선택지
    void MoveSelectionDown();

    bool IsPlayerNear(const Character& character) const;
    bool IsSelecting() const;

    RECT GetCollisionRect() const;

    void Reset();
};