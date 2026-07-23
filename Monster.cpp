#include "Monster.h"
#include "Character.h"

#include <cmath>

Monster::Monster(const wchar_t* walkPath,const wchar_t* attackPath,float startX,float startY,float detect,float attack)
{
    x = startX;
    y = startY;
    walkFrameCount = 8;      
    attackFrameCount = 3;

    moveSpeed = 80.0f;

    facingLeft = false;

    walkImage = nullptr;
    attackImage = nullptr;

    state = MonsterState::Wander;

    currentFrame = 0;
    animationTimer = 0.0f;

    detectRange = detect;
    attackRange = attack;

    hasAttacked = false;
    LoadImages(walkPath, attackPath);
}

Monster::~Monster()
{
    delete walkImage;
    walkImage = nullptr;

    delete attackImage;
    attackImage = nullptr;
}

bool Monster::LoadImages(const wchar_t* walkPath,const wchar_t* attackPath)
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

void Monster::Update(float deltaTime,Character& character)
{
    float characterX = character.GetX();
    float characterY = character.GetY();
    CheckState(characterX, characterY);


    switch (state)
    {
    case MonsterState::Wander:
        UpdateWander(deltaTime);
        break;

    case MonsterState::Chase:
        UpdateChase(deltaTime, characterX, characterY);
        break;

    case MonsterState::Attack:
        UpdateAttack(deltaTime,character);
        break;
    }

    UpdateAnimation(deltaTime);
}

void Monster::CheckState(float characterX,float characterY)
{
    float dx = characterX - x;
    float dy = characterY - y;

    MonsterState newState=state;

    float distance =
        sqrt(dx * dx + dy * dy);

    if (distance <= attackRange)
    {
        newState = MonsterState::Attack;
    }
    else if (distance <= detectRange)
    {
        newState = MonsterState::Chase;
    }
    else
    {
        newState = MonsterState::Wander;
    }

    if (state != newState)
    {
        state = newState;
        currentFrame = 0;
        animationTimer = 0.0f;
        hasAttacked = false;
    }
}

void Monster::UpdateWander(float deltaTime)
{
    //맵 완성 후 작성 예정
}

void Monster::UpdateChase(float deltaTime, float characterX, float characterY)
{
    float dx = characterX - x;
    float dy = characterY - y;

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

void Monster::UpdateAttack(float deltaTime,Character& character)
{
    if (currentFrame == 1 && !hasAttacked)
    {
        character.Damage(1);
        hasAttacked = true;
    }
}

void Monster::UpdateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.1f)
    {
        animationTimer = 0.0f;
        currentFrame++;

        int maxFrame;

        if (state == MonsterState::Attack)
            maxFrame = attackFrameCount;
        else
            maxFrame = walkFrameCount;

        if (currentFrame >= maxFrame)
        {
            currentFrame = 0;

            if (state == MonsterState::Attack)
                hasAttacked = false;
        }
    }
}

void Monster::Draw(Gdiplus::Graphics& graphics)
{
    Gdiplus::Image* currentImage = nullptr;

    if (state == MonsterState::Attack)
        currentImage = attackImage;
    else
        currentImage = walkImage;

    if (currentImage == nullptr)
        return;

    int sourceX = currentFrame * 128;
    
    if (facingLeft)
    {
        graphics.DrawImage(
            currentImage,
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
            currentImage,
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
        (LONG)x,
        (LONG)y+20,
        (LONG)(x + 128),
        (LONG)(y + 128)
    };

    return rect;
}

void Monster::SetMoveSpeed(float speed)
{
    moveSpeed = speed;
}

int Monster::GetCurrentFrame() const
{
    return currentFrame;
}

bool Monster::HasAttacked() const
{
    return hasAttacked;
}

void Monster::SetHasAttacked(bool attacked)
{
    hasAttacked = attacked;
}

void Monster::UpdateSpecial(float deltaTime,Character&)
{
}

void Monster::DrawSpecial(Gdiplus::Graphics& graphics)
{
}

void Monster::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}