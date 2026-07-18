#pragma once

#include <Windows.h>
#include <gdiplus.h>


class Character;

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

    bool facingLeft;

    bool hasAttacked;

    MonsterState state;

    int currentFrame;
    float animationTimer;

    float detectRange;//캐릭터 감지 범위
    float attackRange;//몬스터 공격 범위

    void CheckState(float characterX, float characterY);

    // 상태별 행동
    void UpdateWander(float deltaTime);
    void UpdateChase(float deltaTime, float characterX, float characterY);
    void UpdateAttack(float deltaTime, Character& character);

    // 애니메이션
    void UpdateAnimation(float deltaTime);

public:

    Monster(const wchar_t* walkPath,const wchar_t* attackPath,float startX,float startY,float detect,float attack);
    ~Monster();

    bool LoadImages(const wchar_t* walkPath, const wchar_t* attackPath);

    void Update(float deltaTime,Character& character);

    void Draw(Gdiplus::Graphics& graphics);

    float GetX() const;
    float GetY() const;


    RECT GetCollisionRect() const;
};