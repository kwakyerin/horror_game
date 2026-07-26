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

    // 애니메이션
    void UpdateAnimation(float deltaTime);

public:

    Monster(const wchar_t* walkPath,const wchar_t* attackPath,float startX,float startY,float detect,float attack);
    virtual ~Monster();

    bool LoadImages(const wchar_t* walkPath, const wchar_t* attackPath);

    virtual void Update(float deltaTime,Character& character);

    void Draw(Gdiplus::Graphics& graphics);

    virtual void UpdateSpecial(float deltaTime,Character& character);
    virtual void DrawSpecial(Gdiplus::Graphics& graphics);

    float GetX() const;
    float GetY() const;


    virtual RECT GetCollisionRect() const;

protected:
    virtual void UpdateAttack(float deltaTime, Character& character);
    void SetMoveSpeed(float speed);
    void SetDrawSize(int width, int height);//구미호에서 쓸 함수
    void SetPosition(float newX, float newY);//shadowghost 에서 사용할 함수임

    int GetCurrentFrame() const;
    bool HasAttacked() const;
    void SetHasAttacked(bool attacked);

    bool IsFacingLeft()const;
    int walkFrameCount;
    int attackFrameCount;
    int drawWidth;//구미호 크기 변경할 때
    int drawHeight;//구미호 크기 변경할 때 쓸거
};