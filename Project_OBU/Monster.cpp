#include "Monster.h"

#include <cmath>

Monster::Monster(const wchar_t* walkPath,const wchar_t* attackPath,float startX,float startY)
{
    x = startX;
    y = startY;

    moveSpeed = 80.0f;

    facingLeft = false;

    walkImage = nullptr;
    attackImage = nullptr;

    state = MonsterState::Wander;

    currentFrame = 0;
    animationTimer = 0.0f;

    detectRange = 250.0f;
    attackRange = 80.0f;

    LoadImages(walkPath, attackPath);
}

Monster::~Monster()
{
    delete walkImage;
    walkImage = nullptr;

    delete attackImage;
    attackImage = nullptr;
}

bool Monster::LoadImages(
    const wchar_t* walkPath,
    const wchar_t* attackPath)
{
    walkImage = new Gdiplus::Image(walkPath);

    if (walkImage->GetLastStatus() != Gdiplus::Ok)
    {
        delete walkImage;
        walkImage = nullptr;
        return false;
    }

    attackImage = new Gdiplus::Image(attackPath);

    if (attackImage->GetLastStatus() != Gdiplus::Ok)
    {
        delete attackImage;
        attackImage = nullptr;
        return false;
    }

    return true;
}

void Monster::Update(
    float deltaTime,
    float playerX,
    float playerY)
{
    CheckState(playerX, playerY);

    switch (state)
    {
    case MonsterState::Wander:
        UpdateWander(deltaTime);
        break;

    case MonsterState::Chase:
        UpdateChase(deltaTime, playerX, playerY);
        break;

    case MonsterState::Attack:
        UpdateAttack(deltaTime);
        break;
    }

    UpdateAnimation(deltaTime);
}

void Monster::CheckState(
    float playerX,
    float playerY)
{
    float dx = playerX - x;
    float dy = playerY - y;

    float distance =
        sqrt(dx * dx + dy * dy);

    if (distance <= attackRange)
    {
        state = MonsterState::Attack;
    }
    else if (distance <= detectRange)
    {
        state = MonsterState::Chase;
    }
    else
    {
        state = MonsterState::Wander;
    }
}

void Monster::UpdateWander(float deltaTime)
{
}

void Monster::UpdateChase(float deltaTime, float playerX, float playerY)
{
    float dx = playerX - x;
    float dy = playerY - y;

    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 0.0f)
    {
        dx /= distance;
        dy /= distance;
        if (dx < 0.0f)
        {
            facingLeft = true;
        }
        // 오른쪽으로 이동하면 오른쪽을 바라봄
        else if (dx > 0.0f)
        {
            facingLeft = false;
        }

        x += dx * moveSpeed * deltaTime;
        y += dy * moveSpeed * deltaTime;
    }
}

void Monster::UpdateAttack(float deltaTime)
{
}

void Monster::UpdateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.1f)
    {
        animationTimer = 0.0f;

        currentFrame++;

        if (currentFrame >= 8)
        {
            currentFrame = 0;
        }
    }
}

void Monster::Draw(Gdiplus::Graphics& graphics)
{
    if (walkImage == nullptr)
        return;

    int sourceX = currentFrame * 128;
    
    if (facingLeft)
    {
        graphics.DrawImage(
            walkImage,
            Gdiplus::Rect(
                static_cast<int>(x) + 128,
                static_cast<int>(y),
                -128,
                128),
            sourceX,
            0,
            128,
            128,
            Gdiplus::UnitPixel);
    }
    else
    {
        graphics.DrawImage(
            walkImage,
            Gdiplus::Rect(
                static_cast<int>(x),
                static_cast<int>(y),
                128,
                128),
            sourceX,
            0,
            128,
            128,
            Gdiplus::UnitPixel);
    }
    // 충돌 박스(테스트용)
    Gdiplus::Pen pen(
        Gdiplus::Color(255, 255, 0, 0),
        1.0f
    );

    RECT rc = GetCollisionRect();

    graphics.DrawRectangle(
        &pen,
        static_cast<int>(rc.left),
        static_cast<int>(rc.top),
        static_cast<int>(rc.right - rc.left),
        static_cast<int>(rc.bottom - rc.top)
        
    );

 
}

float Monster::GetX() const
{
    return x;
}

float Monster::GetY() const
{
    return y;
}

RECT Monster::GetCollisionRect() const
{
    RECT rect =
    {
        (LONG)x+22,
        (LONG)y+20,
        (LONG)(x + 100),
        (LONG)(y + 128)
    };

    return rect;
}