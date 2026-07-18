#pragma once

#include <Windows.h>
#include <gdiplus.h>

enum class MonsterState
{
    Wander,
    Chase,
    Attack
};
class Monster {
private:
	float x;
	float y;
	float moveSpeed;
	Gdiplus::Image* walkImage;
    Gdiplus::Image* attackImage;

    MonsterState state;

    int currentFrame;
    float animationTimer;

    float detectRange;//캐릭터 감지 범위
    float attackRange;//몬스터 공격 범위

    void CheckState(float playerX, float playerY);

    // 상태별 행동
    void UpdateWander(float deltaTime);
    void UpdateChase(float deltaTime, float playerX, float playerY);
    void UpdateAttack(float deltaTime);

    // 애니메이션
    void UpdateAnimation(float deltaTime);

public:

    bool facingLeft;

    Monster(const wchar_t* walkPath,const wchar_t* attackPath,float startX,float startY);
    ~Monster();

    bool LoadImages(const wchar_t* walkPath, const wchar_t* attackPath);

    void Update(float deltaTime,float playerX,float playerY);

    void Draw(Gdiplus::Graphics& graphics);

    float GetX() const;
    float GetY() const;


    RECT GetCollisionRect() const;
};