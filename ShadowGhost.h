#pragma once
#include <Windows.h>
#include <gdiplus.h>

class Character;

enum class ShadowState {
	Waiting,
	Warning,
	Attack
};

enum class ShadowDirection
{
    Down,
    Left,
    Right,
    Up
};

class ShadowGhost
{
private:
    float x;
    float y;

    // 현재 행동 상태
    ShadowState state;

    // 플레이어 기준 방향
    ShadowDirection direction;

    // 스프라이트 이미지
    Gdiplus::Image* warningImage;
    Gdiplus::Image* attackImage;

    // 애니메이션
    int currentFrame;
    float animationTimer;

    int warningFrameCount;
    int attackFrameCount;

    float waitTimer;
    // 상태 지속 시간
    float waitDuration;
    

    // 한 번의 공격에서 중복 피해 방지
    bool hasAttacked;

    bool LoadImages(const wchar_t* warningPath,const wchar_t* attackPath);

    void UpdateWaiting(float deltaTime,Character& character);

    void UpdateWarning(float deltaTime);

    void UpdateAttack(float deltaTime,Character& character);

    void TeleportNearCharacter(Character& character);

public:
    ShadowGhost(const wchar_t* warningPath,const wchar_t* attackPath,float startX,float startY);

    ~ShadowGhost();

    void Update(float deltaTime,Character& character);

    void Draw(Gdiplus::Graphics& graphics);

    RECT GetCollisionRect() const;

    float GetX() const;
    float GetY() const;
};